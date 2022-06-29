#include "libc/assert.h"
#include "libc/calls/calls.h"
#include "libc/fmt/conv.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"
#include "third_party/gdtoa/gdtoa.h"

/* handle DJValue reads from an existing buffer */
int _ReadDJValueFromBuffer(const char *buf, const size_t buflen, size_t *index,
                           int depth, DJValue **result);

int _BufferReadDJInternal_Null(const char *buf, const size_t buflen,
                               size_t *index, int depth, DJValue **result) {
  if (*index + 4 < buflen && !strncmp(buf + *index, "null", 4)) {
    *result = NullToDJValue();
    (*index) += 4;
    return 0;
  }
  return -1;
}

int _BufferReadDJInternal_True(const char *buf, const size_t buflen,
                               size_t *index, int depth, DJValue **result) {
  if (*index + 4 < buflen && !strncmp(buf + *index, "true", 4)) {
    *result = BoolToDJValue(true);
    (*index) += 4;
    return 0;
  }
  return -1;
}

int _BufferReadDJInternal_False(const char *buf, const size_t buflen,
                                size_t *index, int depth, DJValue **result) {
  if (*index + 5 < buflen && !strncmp(buf + *index, "false", 5)) {
    *result = BoolToDJValue(false);
    (*index) += 5;
    return 0;
  }
  return -1;
}

int _BufferReadDJInternal_Number(const char *buf, const size_t buflen,
                                 size_t *index, int depth, DJValue **result) {
  char buf2[128] = {0};
  static const char valid[] = "0123456789eE+-.";
  char *p;
  double number = 0;
  for (size_t i = 0; *index < buflen && i < 127; i++, (*index)++) {
    buf2[i] = buf[*index];
    p = strchr(valid, buf2[i]);
    if (!p) {
      (*index)--;
      buf2[i] = '\0';
    }
  }
  if (*index >= buflen) return -1;
  if (!strchr(buf2, '.') || !strchr(valid, 'e') || !strchr(valid, 'E')) {
    *result = IntegerToDJValue(strtoll(buf2, NULL, 10));
  } else {
    *result = DoubleToDJValue(strtod(buf2, NULL));
  }
  return 0;
}

int _BufferReadDJInternal_String(const char *buf, const size_t buflen,
                                 size_t *index, int depth, DJValue **result) {
  char startquote, stopquote;
  char prev;
  DJString *str;
  DJValue *answer;

  size_t count = 0;
  if (*index >= buflen || (startquote = buf[*index]) != '\"') return -1;
  prev = startquote;
  count = 1;
  (*index)++;

  while (*index < buflen && ((stopquote = buf[*index]) != '\"') &&
         prev != '\\') {
    count += 1;
    (*index)++;
  }
  (*index)++;
  if (*index >= buflen) return -1;

  answer = StringToDJValue(buf + *index - count, count);
  str = UNBOX_DJValueAsString(*answer);
  if (str->len) {
    str->ptr[str->len - 1] = '\0';
  }
  *result = answer;
  return 0;
}

int ReadWhitespaceUntilOneOf(const char *buf, const size_t buflen,
                             size_t *index, const char *end) {
  char ch = 0;
  int status = 0;
  for (ch = buf[*index]; *index < buflen; (*index)++) {
    switch (ch) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
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

int _BufferReadDJInternal_Array(const char *buf, const size_t buflen,
                                size_t *index, int depth, DJValue **result) {
  char startbracket, stopbracket = '\0';
  DJArrayElement *head = DJA_New();
  DJArrayElement *tmp = head;
  size_t num_elements = 0;
  int status = 0;

  if (*index > buflen || (startbracket = buf[*index]) != '[') {
    status = -1;
  }
  (*index)++;
  stopbracket = buf[*index];
  while (*index < buflen && status == 0 && stopbracket != ']') {
    status =
        _ReadDJValueFromBuffer(buf, buflen, index, depth + 1, &(tmp->value));
    if (status) break;
    tmp->next = DJA_New();
    tmp = tmp->next;
    num_elements += 1;
    status = ReadWhitespaceUntilOneOf(buf, buflen, index, ",]");
    stopbracket = buf[*index];
    (*index)++;
  }

  if (status == 0) {
    *result = ArrayElementsToDJValue(head, num_elements);
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJA_FreeLinked(head);
  }
  return status;
}

int _BufferReadDJInternal_Object(const char *buf, const size_t buflen,
                                 size_t *index, int depth, DJValue **result) {
  char startbracket, stopbracket = '\0';
  DJObjectElement *head = DJO_New();
  DJObjectElement *tmp = head;
  DJValue *tempkey = NULL;
  DJString *tempstr = 0;

  size_t num_elements = 0;
  int status = 0;

  if (*index > buflen || (startbracket = buf[*index]) != '{') {
    status = -1;
  }
  (*index)++;
  stopbracket = buf[*index];
  while (*index < buflen && status == 0 && stopbracket != '}') {
    status = ReadWhitespaceUntilOneOf(buf, buflen, index, "\"");
    if (status) break;
    status =
        _BufferReadDJInternal_String(buf, buflen, index, depth + 1, &tempkey);
    if (status) break;
    tempstr = UNBOX_DJValueAsString(*tempkey);
    tmp->key = tempstr->ptr;
    tmp->keylen = tempstr->len;
    status = ReadWhitespaceUntilOneOf(buf, buflen, index, ":");
    if (status) break;
    stopbracket = buf[*index];
    (*index)++;
    status =
        _ReadDJValueFromBuffer(buf, buflen, index, depth + 1, &(tmp->value));
    if (status) break;
    tmp->next = DJO_New();
    tmp = tmp->next;
    num_elements += 1;
    status = ReadWhitespaceUntilOneOf(buf, buflen, index, ",}");
    stopbracket = buf[*index];
    (*index)++;
  }

  if (status == 0) {
    *result = ObjectElementsToDJValue(head, num_elements);
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJO_FreeLinked(head);
  }
  return status;
}

int _ReadDJValueFromBuffer(const char *buf, const size_t buflen, size_t *index,
                           int depth, DJValue **result) {
  char ch;
  int stuck = 0;
  while (*index < buflen && (depth > 0 || stuck != -1)) {
    ch = buf[*index];
    switch (ch) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        (*index)++;
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
        return _BufferReadDJInternal_Number(buf, buflen, index, depth, result);
      case 't':  // true
        return _BufferReadDJInternal_True(buf, buflen, index, depth, result);
      case 'f':  // false
        return _BufferReadDJInternal_False(buf, buflen, index, depth, result);
      case 'n':  // null
        return _BufferReadDJInternal_Null(buf, buflen, index, depth, result);
      case '"':  // string
        return _BufferReadDJInternal_String(buf, buflen, index, depth, result);
      case '[':  // array
        return _BufferReadDJInternal_Array(buf, buflen, index, depth, result);
      case '{':  // object
        return _BufferReadDJInternal_Object(buf, buflen, index, depth, result);
      default:
        stuck = -1;  // error
        break;
    }
  }
  if (depth > 0) {
    stuck = -1;
  } else if (*index < buflen) {
    /* I read a valid JSON from the file, but it still has some stuff left */
    stuck = -1;
  }
  if (stuck != 0) {
    /* do some cleanup here if necessary */
  }
  return stuck;
}

int ReadDJValueFromBuffer(const char *buf, const size_t buflen,
                          DJValue **result) {
  int status = 0;
  size_t index = 0;
  status = _ReadDJValueFromBuffer(buf, buflen, &index, 0, result);
  if (status == -1 || !*result ||
      (!DJValueIS_Object(**result) && !DJValueIS_Array(**result))) {
    if (*result) {
      FreeDJValue(*result);
      *result = NULL;
    }
  }
  return status;
}
