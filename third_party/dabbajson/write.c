#include "libc/assert.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"

/* handle DJValue writes into a FILE pointer */

int FileWriteDJInternal_Double(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Double(value));
  DJValue answer = {.raw_u64 = (uint64_t)(value)};
  if (0.0 == answer.number - (int64_t)(answer.number)) {
    /* print a .0 so that it is read as double */
    return fprintf(fp, "%lg.0", answer.number);
  } else {
    return fprintf(fp, "%lg", answer.number);
  }
}

int FileWriteDJInternal_Null(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Null(value));
  return fprintf(fp, "null");
}

int FileWriteDJInternal_Bool(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_True(value) || DJPtrIS_False(value));
  if (DJPtrIS_False(value)) {
    return fprintf(fp, "false");
  } else {
    return fprintf(fp, "true");
  }
}

int FileWriteDJInternal_MiniInt(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_MiniInt(value));
  int64_t val = UNBOX_DJPtrAsMiniInt(value);
  return fprintf(fp, "%ld", val);
}

int FileWriteDJInternal_Integer(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Integer(value));
  int64_t *ptr = UNBOX_DJPtrAsInteger(value);
  return fprintf(fp, "%ld", *ptr);
}

int FileWriteDJInternal_String(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return fprintf(fp, "\"%s\"", str->len > 0 ? str->ptr : "");
}

int FileWriteDJInternal_Array(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  int ans = 0;
  ans += fprintf(fp, "[");
  for (size_t i = 0; i < arr->len; i++) {
    ans += WriteDJValueToFile(arr->values[i], fp);
    if (i != arr->len - 1) ans += fputc(',', fp);
  }
  ans += fprintf(fp, "]");
  return ans;
}

int FileWriteDJInternal_Object(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  int ans = 0;
  ans += fprintf(fp, "{");
  for (size_t i = 0; i < obj->len; i++) {
    ans += fprintf(fp, "\"%s\":", obj->keys[i] ? obj->keys[i] : "");
    ans += WriteDJValueToFile(obj->values[i], fp);
    if (i != obj->len - 1) ans += fputc(',', fp);
  }
  ans += fprintf(fp, "}");
  return ans;
}

int FileWriteDJInternal_Error(const DJValue *value, FILE *fp) {
  DIEF("attempted to write an invalid value");
  return 0;
}

static int (*_dj_filewriters[])(const DJValue *value, FILE *fp) = {
    FileWriteDJInternal_Double,  /* Double */
    FileWriteDJInternal_Null,    /* Null */
    FileWriteDJInternal_Bool,    /* Bool */
    FileWriteDJInternal_MiniInt, /* MiniInt */
    FileWriteDJInternal_Integer, /* Integer */
    FileWriteDJInternal_String,  /* DJString* */
    FileWriteDJInternal_Array,   /* DJArray* */
    FileWriteDJInternal_Object,  /* DJObject* */
};

int WriteDJValueToFile(const DJValue *value, FILE *fp) {
  return (_dj_filewriters[UNBOX_DJPtrTypeONLY(value)])(value, fp);
}
