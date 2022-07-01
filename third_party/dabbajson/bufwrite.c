#include "libc/assert.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"

/* handle DJValue writes into an allocated buffer */

int BufferWriteDJInternal_Double(const DJValue *value, char *buf,
                                 size_t buflen) {
  assert(DJPtrIS_Double(value));
  DJValue answer = {.raw_u64 = (uint64_t)(value)};
  if (0.0 == answer.number - (int64_t)(answer.number)) {
    /* print a .0 so that it is read as double */
    return snprintf(buf, buflen, "%lg.0", answer.number);
  } else {
    return snprintf(buf, buflen, "%lg", answer.number);
  }
}

int BufferWriteDJInternal_Null(const DJValue *value, char *buf, size_t buflen) {
  assert(DJPtrIS_Null(value));
  return snprintf(buf, buflen, "null");
}

int BufferWriteDJInternal_Bool(const DJValue *value, char *buf, size_t buflen) {
  assert(DJPtrIS_True(value) || DJPtrIS_False(value));
  if (DJPtrIS_True(value)) {
    return snprintf(buf, buflen, "true");
  } else {
    return snprintf(buf, buflen, "false");
  }
}

int BufferWriteDJInternal_MiniInt(const DJValue *value, char *buf,
                                  size_t buflen) {
  assert(DJPtrIS_MiniInt(value));
  int64_t val = UNBOX_DJPtrAsMiniInt(value);
  return snprintf(buf, buflen, "%ld", val);
}

int BufferWriteDJInternal_Integer(const DJValue *value, char *buf,
                                  size_t buflen) {
  assert(DJPtrIS_Integer(value));
  int64_t *ptr = UNBOX_DJPtrAsInteger(value);
  return snprintf(buf, buflen, "%ld", *ptr);
}

int BufferWriteDJInternal_String(const DJValue *value, char *buf,
                                 size_t buflen) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return snprintf(buf, buflen, "\"%s\"", str->ptr);
}

int BufferWriteDJInternal_Array(const DJValue *value, char *buf,
                                size_t buflen) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  int ans = 0;
  int written = 0;

  written = snprintf(buf, buflen, "[");
  if (written >= buflen) return ans + written;
  buflen -= written;
  buf += written;
  ans += written;

  for (size_t i = 0; i < arr->len; i++) {
    written = WriteDJValueToBuffer(arr->values[i], buf, buflen);
    if (written >= buflen) return ans + written;
    buflen -= written;
    buf += written;
    ans += written;
    if (i != arr->len - 1) {
      written = snprintf(buf, buflen, ",");
      if (written >= buflen) return ans + written;
      buflen -= written;
      buf += written;
      ans += written;
    }
  }
  ans += snprintf(buf, buflen, "]");
  return ans;
}

int BufferWriteDJInternal_Object(const DJValue *value, char *buf,
                                 size_t buflen) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  int ans = 0;
  int written = 0;

  written = snprintf(buf, buflen, "{");
  if (written >= buflen) return ans + written;
  buflen -= written;
  buf += written;
  ans += written;

  for (size_t i = 0; i < obj->len; i++) {
    written = snprintf(buf, buflen, "\"%s\":", obj->keys[i]);
    if (written >= buflen) return ans + written;
    buflen -= written;
    buf += written;
    ans += written;
    written = WriteDJValueToBuffer(obj->values[i], buf, buflen);
    if (written >= buflen) return ans + written;
    buflen -= written;
    buf += written;
    ans += written;
    if (i != obj->len - 1) {
      written = snprintf(buf, buflen, ",");
      if (written >= buflen) return ans + written;
      buflen -= written;
      buf += written;
      ans += written;
    }
  }
  ans += snprintf(buf, buflen, "}");
  return ans;
}

int BufferWriteDJInternal_Error(const DJValue *value, char *buf,
                                size_t buflen) {
  DIEF("attempted to write an invalid value");
  return 0;
}

static int (*_dj_bufferwriters[])(const DJValue *value, char *buf,
                                  size_t buflen) = {
    BufferWriteDJInternal_Double,  /* Double */
    BufferWriteDJInternal_Null,    /* Null */
    BufferWriteDJInternal_Bool,    /* Bool */
    BufferWriteDJInternal_MiniInt, /* MiniInt */
    BufferWriteDJInternal_Integer, /* Integer */
    BufferWriteDJInternal_String,  /* DJString* */
    BufferWriteDJInternal_Array,   /* DJArray* */
    BufferWriteDJInternal_Object,  /* DJObject* */
};

int WriteDJValueToBuffer(const DJValue *value, char *buf, size_t buflen) {
  return (_dj_bufferwriters[UNBOX_DJPtrTypeONLY(value)])(value, buf, buflen);
}
