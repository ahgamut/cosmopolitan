#include "libc/assert.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/append.internal.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"

/* handle DJValue writes into an allocated buffer */

ssize_t BufferWriteDJInternal_Double(const DJValue *value, char **buf) {
  assert(DJPtrIS_Double(value));
  DJValue answer = {.raw_u64 = (uint64_t)(value)};
  if (0.0 == answer.number - (int64_t)(answer.number)) {
    /* print a .0 so that it is read as double */
    return appendf(buf, "%lg.0", answer.number);
  } else {
    return appendf(buf, "%lg", answer.number);
  }
}

ssize_t BufferWriteDJInternal_Null(const DJValue *value, char **buf) {
  assert(DJPtrIS_Null(value));
  return appendd(buf, "null", 4);
}

ssize_t BufferWriteDJInternal_Bool(const DJValue *value, char **buf) {
  assert(DJPtrIS_True(value) || DJPtrIS_False(value));
  if (DJPtrIS_True(value)) {
    return appendd(buf, "true", 4);
  } else {
    return appendd(buf, "false", 5);
  }
}

ssize_t BufferWriteDJInternal_MiniInt(const DJValue *value, char **buf) {
  assert(DJPtrIS_MiniInt(value));
  int64_t val = UNBOX_DJPtrAsMiniInt(value);
  return appendf(buf, "%ld", val);
}

ssize_t BufferWriteDJInternal_Integer(const DJValue *value, char **buf) {
  assert(DJPtrIS_Integer(value));
  int64_t *ptr = UNBOX_DJPtrAsInteger(value);
  return appendf(buf, "%ld", *ptr);
}

static ssize_t EscapeStringAndWrite(const char *ptr, const size_t len,
                                    char **buf) {
  ssize_t answer = 2;
  char escaped[2] = {0};
  escaped[0] = '\\';
  wchar_t utfval = 0;
  int utflen = 0;

  appendd(buf, "\"", 1);
  if (len != 0 && ptr != NULL) {
    /* TODO: why do i need both len and null check here */
    for (size_t i = 0; i < len && ptr[i] != '\0'; i++) {
      if (ptr[i] < 0) {
        utflen = mbtowc(&utfval, &(ptr[i]), len - i);
        if (utflen > 0) {
          i += utflen - 1;
          answer += appendf(buf, "\\u%04x", utfval);
        } else {
          DIEF("unable to write utf-8 value %s (%s)\n", &(ptr[i]), strerror(errno));
        }
      } else {
        switch (ptr[i]) {
          case '"':
          case '\\':
            escaped[1] = ptr[i];
            answer += appendd(buf, &escaped, 2);
            break;
          case '\n':
            escaped[1] = 'n';
            answer += appendd(buf, &escaped, 2);
            break;
          case '\r':
            escaped[1] = 'r';
            answer += appendd(buf, &escaped, 2);
            break;
          case '\f':
            escaped[1] = 'f';
            answer += appendd(buf, &escaped, 2);
            break;
          case '\t':
            escaped[1] = 't';
            answer += appendd(buf, &escaped, 2);
            break;
          case '\b':
            escaped[1] = 'b';
            answer += appendd(buf, &escaped, 2);
            break;
          default:
            answer += appendd(buf, &(ptr[i]), 1);
        }
      }
    }
  }
  appendd(buf, "\"", 1);
  return answer;
}

ssize_t BufferWriteDJInternal_String(const DJValue *value, char **buf) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return EscapeStringAndWrite(str->ptr, str->len, buf);
}

ssize_t BufferWriteDJInternal_Array(const DJValue *value, char **buf) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  ssize_t ans = 0;
  ssize_t written = 0;

  if ((written = appendd(buf, "[", 1)) == -1) return -1;
  ans += written;

  for (size_t i = 0; i < arr->len; i++) {
    if ((written = WriteDJValueToBuffer(arr->values[i], buf)) == -1) return -1;
    ans += written;
    if (i != arr->len - 1) {
      if ((written = appendd(buf, ",", 1)) == -1) return -1;
      ans += written;
    }
  }
  if ((written = appendd(buf, "]", 1)) == -1) return -1;
  ans += written;
  return ans;
}

ssize_t BufferWriteDJInternal_Object(const DJValue *value, char **buf) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  ssize_t ans = 0;
  ssize_t written = 0;

  if ((written = appendd(buf, "{", 1)) == -1) return -1;
  ans += written;

  for (size_t i = 0; i < obj->len; i++) {
    if ((written = EscapeStringAndWrite(obj->keys[i], obj->keylens[i], buf)) == -1) return -1;
    ans += written;
    if ((written = appendd(buf, ":", 1)) == -1) return -1;
    ans += written;
    if ((written = WriteDJValueToBuffer(obj->values[i], buf)) == -1) return -1;
    ans += written;
    if (i != obj->len - 1) {
      if ((written = appendd(buf, ",", 1)) == -1) return -1;
      ans += written;
    }
  }
  if ((written = appendd(buf, "}", 1)) == -1) return -1;
  ans += written;
  return ans;
}

ssize_t BufferWriteDJInternal_Error(const DJValue *value, char **buf) {
  DIEF("attempted to write an invalid value");
  return -1;
}

static ssize_t (*_dj_bufferwriters[])(const DJValue *value, char **buf) = {
    BufferWriteDJInternal_Double,  /* Double */
    BufferWriteDJInternal_Null,    /* Null */
    BufferWriteDJInternal_Bool,    /* Bool */
    BufferWriteDJInternal_MiniInt, /* MiniInt */
    BufferWriteDJInternal_Integer, /* Integer */
    BufferWriteDJInternal_String,  /* DJString* */
    BufferWriteDJInternal_Array,   /* DJArray* */
    BufferWriteDJInternal_Object,  /* DJObject* */
};

ssize_t WriteDJValueToBuffer(const DJValue *value, char **buf) {
  return (_dj_bufferwriters[UNBOX_DJPtrTypeONLY(value)])(value, buf);
}