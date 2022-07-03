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

ssize_t BufferWriteDJInternal_String(const DJValue *value, char **buf) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return appendf(buf, "\"%s\"", str->ptr);
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
    if ((written = appendf(buf, "\"%s\":", obj->keys[i])) == -1) return -1;
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
