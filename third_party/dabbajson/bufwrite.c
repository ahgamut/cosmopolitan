#include "libc/assert.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"

/* handle DJValue writes into an allocated buffer */

int BufferWriteDJInternal_Double(const DJValue *value, char *buf,
                                 size_t buflen) {
  assert(DJValueIS_Double(*value));
  return snprintf(buf, buflen, "%lg", UNBOX_DJValueAsDouble(*value));
}

int BufferWriteDJInternal_Null(const DJValue *value, char *buf, size_t buflen) {
  assert(DJValueIS_Null(*value));
  return snprintf(buf, buflen, "null");
}

int BufferWriteDJInternal_Bool(const DJValue *value, char *buf, size_t buflen) {
  assert(DJValueIS_True(*value) || DJValueIS_False(*value));
  if (DJValueIS_True(*value)) {
    return snprintf(buf, buflen, "true");
  } else {
    return snprintf(buf, buflen, "false");
  }
}

int BufferWriteDJInternal_Integer(const DJValue *value, char *buf,
                                  size_t buflen) {
  assert(DJValueIS_Integer(*value));
  int64_t *ptr = UNBOX_DJValueAsInteger(*value);
  return snprintf(buf, buflen, "%ld", *ptr);
}

int BufferWriteDJInternal_String(const DJValue *value, char *buf,
                                 size_t buflen) {
  assert(DJValueIS_String(*value));
  DJString *str = UNBOX_DJValueAsString(*value);
  return snprintf(buf, buflen, "\"%s\"", str->ptr);
}

int BufferWriteDJInternal_Array(const DJValue *value, char *buf,
                                size_t buflen) {
  assert(DJValueIS_Array(*value));
  DJArray *arr = UNBOX_DJValueAsArray(*value);
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
  assert(DJValueIS_Object(*value));
  DJObject *obj = UNBOX_DJValueAsObject(*value);
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
    BufferWriteDJInternal_Double,  /* DJV_DOUBLE = 0 */
    BufferWriteDJInternal_Null,    /* DJV_NULL = 1 */
    BufferWriteDJInternal_Bool,    /* DJV_TRUE = 2 */
    BufferWriteDJInternal_Bool,    /* DJV_FALSE = 3 */
    BufferWriteDJInternal_Integer, /* DJV_INTEGER = 4 */
    BufferWriteDJInternal_String,  /* DJV_STRING = 5 */
    BufferWriteDJInternal_Array,   /* DJV_ARRAY = 6 */
    BufferWriteDJInternal_Object,  /* DJV_OBJECT = 7 */
};

int WriteDJValueToBuffer(const DJValue *value, char *buf, size_t buflen) {
  return (_dj_bufferwriters[UNBOX_DJValueTypeONLY(*value)])(value, buf, buflen);
}
