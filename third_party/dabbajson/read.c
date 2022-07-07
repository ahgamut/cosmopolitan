#include "libc/assert.h"
#include "libc/calls/calls.h"
#include "libc/fmt/conv.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/append.internal.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"
#include "third_party/gdtoa/gdtoa.h"

/* handle DJValue reads from a valid FILE pointer */
int _ReadDJValueFromFile(FILE *fp, int depth, DJValue **result);

static inline int peek(FILE *fp) {
  int ch = fgetc(fp);
  ungetc(ch, fp);
  return ch;
}

int _FileReadDJInternal_Null(FILE *fp, int depth, DJValue **result) {
  char buf[5] = {0};
  if (fread(buf, sizeof(char), 4, fp) == 4 && !strcmp(buf, "null")) {
    *result = NullToDJValue();
    return 0;
  }
  return -1;
}

int _FileReadDJInternal_True(FILE *fp, int depth, DJValue **result) {
  char buf[5] = {0};
  if (fread(buf, sizeof(char), 4, fp) == 4 && !strcmp(buf, "true")) {
    *result = BoolToDJValue(true);
    return 0;
  }
  return -1;
}

int _FileReadDJInternal_False(FILE *fp, int depth, DJValue **result) {
  char buf[6] = {0};
  if (fread(buf, sizeof(char), 5, fp) == 5 && !strcmp(buf, "false")) {
    *result = BoolToDJValue(false);
    return 0;
  }
  return -1;
}

int _FileReadDJInternal_Number(FILE *fp, int depth, DJValue **result) {
  char buf[128] = {0};
  static const char valid[] = "0123456789eE+-.";
  char *p;
  double number = 0;
  for (size_t i = 0; !feof(fp) && i < 127; i++) {
    buf[i] = fgetc(fp);
    p = strchr(valid, buf[i]);
    if (!p) {
      ungetc(buf[i], fp);
      buf[i] = '\0';
    }
  }
  if (feof(fp) || ferror(fp)) return -1;
  if (!strchr(buf, '.') && !strchr(buf, 'e') && !strchr(buf, 'E')) {
    /* string does not contain .eE so likely int */
    *result = IntegerToDJValue(strtoll(buf, NULL, 10));
  } else {
    *result = DoubleToDJValue(strtod(buf, NULL));
  }
  return 0;
}

int _FileReadDJInternal_String(FILE *fp, int depth, DJValue **result) {
  char current, previous;
  char *buf = NULL;
  size_t buflen;
  DJString *str;
  DJValue *answer = NULL;

  long count = 0;
  if ((current = fgetc(fp)) != '\"') return -1;
  previous = current;
  count = 0;

  while (!feof(fp) && !(((current = fgetc(fp)) == '\"'))) {
    count += 1;
    previous = current;
    if (previous == '\\') {
      current = fgetc(fp);
      switch (current) {
        case 't':
          appendd(&buf, "\t", 1);
          break;
        case 'b':
          appendd(&buf, "\b", 1);
          break;
        case 'f':
          appendd(&buf, "\f", 1);
          break;
        case 'r':
          appendd(&buf, "\r", 1);
          break;
        case 'n':
          appendd(&buf, "\n", 1);
          break;
        default:
          appendd(&buf, &current, 1);
      }
    } else {
      appendd(&buf, &current, 1);
    }
  }
  buflen = count;

  if (feof(fp) || ferror(fp)) {
    free(buf);
    return -1;
  }

  str = malloc(sizeof(DJString));
  str->ptr = buf;
  str->len = buflen;

  BOX_StringIntoDJPtr(str, answer);
  *result = answer;
  return 0;
}

int FileReadWhitespaceUntilOneOf(FILE *fp, const char *end) {
  char ch = 0;
  int status = 0;
  for (ch = peek(fp); !feof(fp); ch = peek(fp)) {
    switch (ch) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        fgetc(fp);
        break;
      default:
        if (strchr(end, ch))
          status = 0;
        else
          status = -1;
        return status;
    }
  }
  return -1;
}

int _FileReadDJInternal_Array(FILE *fp, int depth, DJValue **result) {
  DJArrayElement *head = DJA_New();
  DJArrayElement *tmp = head;
  size_t num_elements = 0;
  int status = 0;
  char current = '\0';

  if ((current = fgetc(fp)) != '[') {
    status = -1;
  }
  current = peek(fp);
  while (!feof(fp) && status == 0 && current != ']') {
    status = _ReadDJValueFromFile(fp, depth + 1, &(tmp->value));
    if (status) break;
    tmp->next = DJA_New();
    tmp = tmp->next;
    num_elements += 1;
    status = FileReadWhitespaceUntilOneOf(fp, ",]");
    current = fgetc(fp);
  }
  if (num_elements == 0) {
      fgetc(fp); /* we only peeked at ']', so read it out */
  }

  if (status == 0) {
    *result = ArrayElementsToDJValue(head, num_elements);
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJA_FreeLinked(head);
  }
  return status;
}

int _FileReadDJInternal_Object(FILE *fp, int depth, DJValue **result) {
  DJObjectElement *head = DJO_New();
  DJObjectElement *tmp = head;
  DJValue *tempkey = NULL;
  DJString *tempstr = 0;

  size_t num_elements = 0;
  int status = 0;
  char current = '\0';

  if ((current = fgetc(fp)) != '{') {
    status = -1;
  }
  current = peek(fp);
  while (!feof(fp) && status == 0 && current != '}') {
    status = FileReadWhitespaceUntilOneOf(fp, "\"");
    if (status) break;
    status = _FileReadDJInternal_String(fp, depth + 1, &tempkey);
    if (status) break;
    tempstr = UNBOX_DJPtrAsString(tempkey);
    tmp->key = tempstr->ptr;
    tmp->keylen = tempstr->len;
    status = FileReadWhitespaceUntilOneOf(fp, ":");
    if (status) break;
    current = fgetc(fp);
    status = _ReadDJValueFromFile(fp, depth + 1, &(tmp->value));
    if (status) break;
    tmp->next = DJO_New();
    tmp = tmp->next;
    num_elements += 1;
    status = FileReadWhitespaceUntilOneOf(fp, ",}");
    current = fgetc(fp);
  }
  if (num_elements == 0) {
      fgetc(fp); /* we only peeked at '}', so read it out */
  }

  if (status == 0) {
    *result = ObjectElementsToDJValue(head, num_elements);
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJO_FreeLinked(head);
  }
  return status;
}

int _ReadDJValueFromFile(FILE *fp, int depth, DJValue **result) {
  char ch;
  int status = depth >= DJVALUE_MAXIMUM_RECURSION_DEPTH ? -1 : 0;
  while (!feof(fp) && status != -1) {
    ch = peek(fp);
    switch (ch) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        ch = fgetc(fp);
        break;  // whitespace
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':  // double or integer
        return _FileReadDJInternal_Number(fp, depth, result);
      case 't':  // true
        return _FileReadDJInternal_True(fp, depth, result);
      case 'f':  // false
        return _FileReadDJInternal_False(fp, depth, result);
      case 'n':  // null
        return _FileReadDJInternal_Null(fp, depth, result);
      case '"':  // string
        return _FileReadDJInternal_String(fp, depth, result);
      case '[':  // array
        return _FileReadDJInternal_Array(fp, depth, result);
      case '{':  // object
        return _FileReadDJInternal_Object(fp, depth, result);
      default:
        status = -1;  // error
    }
  }
  if (depth > 0) {
    status = -1;
  } else if (!feof(fp)) {
    /* I read a valid JSON from the file, but it still has some stuff left */
    status = -1;
  }
  if (status != 0) {
    /* do some cleanup here if necessary */
  }
  return status;
}

int ReadDJValueFromFile(FILE *fp, DJValue **result) {
  int status = 0;
  status = _ReadDJValueFromFile(fp, 0, result);
  if (status == -1 || !*result) {
    if (*result) {
      FreeDJValue(*result);
      *result = NULL;
    }
  }
  return status;
}
