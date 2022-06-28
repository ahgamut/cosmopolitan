#include "libc/assert.h"
#include "libc/calls/calls.h"
#include "libc/fmt/conv.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
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

struct __DJArrayElement {
  DJValue *value;
  struct __DJArrayElement *next;
};

typedef struct __DJArrayElement DJArrayElement;

DJArrayElement *DJA_New() {
  DJArrayElement *x = malloc(sizeof(DJArrayElement));
  x->value = NULL;
  x->next = NULL;
  return x;
}

void DJA_FreeLinked(DJArrayElement *elem) {
  if (!elem) return;
  if (elem->next) DJA_FreeLinked(elem->next);
  if (elem->value) FreeDJValue(elem->value);
  free(elem);
}

size_t DJA_CountLinked(DJArrayElement *elem) {
  if (!elem || !elem->value) return 0;
  return 1 + DJA_CountLinked(elem->next);
}

struct __DJObjectElement {
  char *key;
  DJValue *value;
  size_t keylen;
  struct __DJObjectElement *next;
};

typedef struct __DJObjectElement DJObjectElement;

DJObjectElement *DJO_New() {
  DJObjectElement *x = malloc(sizeof(DJObjectElement));
  x->key = NULL;
  x->keylen = 0;
  x->value = NULL;
  x->next = NULL;
  return x;
}

void DJO_FreeLinked(DJObjectElement *elem) {
  if (!elem) return;
  if (elem->next) DJO_FreeLinked(elem->next);
  if (elem->value) FreeDJValue(elem->value);
  if (elem->key) free(elem->key);
  free(elem);
}

size_t DJO_CountLinked(DJObjectElement *elem) {
  if (!elem || !elem->value || !elem->key || !elem->keylen) return 0;
  return 1 + DJO_CountLinked(elem->next);
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
  if (!strchr(buf, '.') || !strchr(valid, 'e') || !strchr(valid, 'E')) {
    *result = IntegerToDJValue(strtoll(buf, NULL, 10));
  } else {
    *result = DoubleToDJValue(strtod(buf, NULL));
  }
  return 0;
}

int _FileReadDJInternal_String(FILE *fp, int depth, DJValue **result) {
  char startquote, stopquote;
  char prev;
  char *buf;
  size_t buflen;
  DJString *str;
  DJValue *answer;

  long count = 0;
  if ((startquote = fgetc(fp)) != '\"') return -1;
  prev = startquote;
  count = 1;

  while (!feof(fp) && ((stopquote = fgetc(fp)) != '\"') && prev != '\\') {
    count += 1;
  }
  fseek(fp, -count, SEEK_CUR);
  buflen = count;
  buf = malloc(sizeof(char) * buflen);
  fread(buf, sizeof(char), buflen, fp);
  buf[buflen - 1] = '\0';

  if (feof(fp) || ferror(fp)) {
    free(buf);
    return -1;
  }

  str = malloc(sizeof(DJString));
  str->ptr = buf;
  str->len = buflen;

  answer = malloc(sizeof(DJValue));
  BOX_StringIntoDJValue(str, *answer);
  *result = answer;
  return 0;
}

int ReadWhitespaceUntilOneOf(FILE *fp, const char *end) {
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
  char startbracket, stopbracket = '\0';
  DJArrayElement *head = DJA_New();
  DJArrayElement *tmp = head;
  size_t num_elements = 0;
  int status = 0;

  if ((startbracket = fgetc(fp)) != '[') {
    status = -1;
  }
  stopbracket = peek(fp);
  while (!feof(fp) && status == 0 && stopbracket != ']') {
    status = _ReadDJValueFromFile(fp, depth + 1, &(tmp->value));
    if(status) break;
    tmp->next = DJA_New();
    tmp = tmp->next;
    num_elements += 1;
    status = ReadWhitespaceUntilOneOf(fp, ",]");
    stopbracket = fgetc(fp);
  }

  if (status == 0) {
    /* create the DJValue from the DJArrayElement linked list */
    DJValue *answer = malloc(sizeof(DJValue));
    DJArray *arr = malloc(sizeof(DJArray));
    arr->len = num_elements;
    arr->values = malloc(sizeof(DJValue *) * arr->len);
    for (size_t i = 0; i < num_elements; i++) {
      arr->values[i] = head->value;
      tmp = head;
      head = head->next;
      /* we are not freeing the attributes of tmp because
       * they are being std::move'd into the DJArray */
      free(tmp);
    }
    BOX_ArrayIntoDJValue(arr, *answer);
    *result = answer;
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJA_FreeLinked(head);
  }
  return status;
}

int _FileReadDJInternal_Object(FILE *fp, int depth, DJValue **result) {
  char startbracket, stopbracket = '\0';
  DJObjectElement *head = DJO_New();
  DJObjectElement *tmp = head;
  DJValue *tempkey = NULL;
  DJString *tempstr = 0;

  size_t num_elements = 0;
  int status = 0;

  if ((startbracket = fgetc(fp)) != '{') {
    status = -1;
  }
  stopbracket = peek(fp);
  while (!feof(fp) && status == 0 && stopbracket != '}') {
    status = ReadWhitespaceUntilOneOf(fp, "\"");
    if (status) break;
    status = _FileReadDJInternal_String(fp, depth + 1, &tempkey);
    if (status) break;
    tempstr = UNBOX_DJValueAsString(*tempkey);
    tmp->key = tempstr->ptr;
    tmp->keylen = tempstr->len;
    status = ReadWhitespaceUntilOneOf(fp, ":");
    if (status) break;
    stopbracket = fgetc(fp);
    status = _ReadDJValueFromFile(fp, depth + 1, &(tmp->value));
    if (status) break;
    tmp->next = DJO_New();
    tmp = tmp->next;
    num_elements += 1;
    status = ReadWhitespaceUntilOneOf(fp, ",}");
    stopbracket = fgetc(fp);
  }

  if (status == 0) {
    /* create the DJValue from the DJObjectElement linked list */
    DJValue *answer = malloc(sizeof(DJValue));
    DJObject *obj = malloc(sizeof(DJObject));
    obj->len = num_elements;
    obj->keylens = malloc(sizeof(size_t) * obj->len);
    obj->keys = malloc(sizeof(char *) * obj->len);
    obj->values = malloc(sizeof(DJValue *) * obj->len);
    for (size_t i = 0; i < num_elements; i++) {
      obj->values[i] = head->value;
      obj->keys[i] = head->key;
      obj->keylens[i] = head->keylen;
      tmp = head;
      head = head->next;
      /* we are not freeing the attributes of tmp because
       * they are being std::move'd into the DJObject */
      free(tmp);
    }
    BOX_ObjectIntoDJValue(obj, *answer);
    *result = answer;
  } else {
    /* failed somewhere, so delete anything you may have allocated */
    DJO_FreeLinked(head);
  }
  return status;
}

int _ReadDJValueFromFile(FILE *fp, int depth, DJValue **result) {
  char ch;
  int stuck = 0;
  while (!feof(fp) && (depth > 0 || stuck != -1)) {
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
        stuck = -1;  // error
    }
  }
  if (depth > 0) {
    stuck = -1;
  } else if (!feof(fp)) {
    /* I read a valid JSON from the file, but it still has some stuff left */
    stuck = -1;
  }
  if (stuck != 0) {
    /* do some cleanup here if necessary */
  }
  return stuck;
}

int ReadDJValueFromFile(FILE *fp, DJValue **result) {
  if (peek(fp) == '[')
    return _FileReadDJInternal_Array(fp, 0, result);
  else if (peek(fp) == '{')
    return _FileReadDJInternal_Object(fp, 0, result);
  else
    return -1;
}

/* handle DJValue reads from an existing buffer */
int ReadDJValueFromBuffer(const char *buf, const size_t buflen,
                          DJValue **result) {
  return -1;
}
