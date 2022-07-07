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

static int EscapeStringAndWrite(const char *ptr, const size_t len, FILE *fp) {
  int answer = 2;
  fputc('"', fp);
  if (len != 0 && ptr != NULL) {
    /* TODO: why do i need both len and null check here */
    for (size_t i = 0; i < len && ptr[i] != '\0'; i++) {
      switch (ptr[i]) {
        case '"':
        case '\\':
          fputc('\\', fp);
          fputc(ptr[i], fp);
          answer += 2;
          break;
        case '\n':
          fputc('\\', fp);
          fputc('n', fp);
          answer += 2;
          break;
        case '\r':
          fputc('\\', fp);
          fputc('r', fp);
          answer += 2;
          break;
        case '\f':
          fputc('\\', fp);
          fputc('f', fp);
          answer += 2;
          break;
        case '\t':
          fputc('\\', fp);
          fputc('t', fp);
          answer += 2;
          break;
        case '\b':
          fputc('\\', fp);
          fputc('b', fp);
          answer += 2;
          break;
        default:
          fputc(ptr[i], fp);
          answer += 1;
      }
    }
  }
  fputc('"', fp);
  return answer;
}

int FileWriteDJInternal_String(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return EscapeStringAndWrite(str->ptr, str->len, fp);
}

int FileWriteDJInternal_Array(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  int ans = 2;
  fputc('[', fp);
  for (size_t i = 0; i < arr->len; i++) {
    ans += WriteDJValueToFile(arr->values[i], fp);
    if (i != arr->len - 1) {
      ans += 1;
      fputc(',', fp);
    }
  }
  fputc(']', fp);
  return ans;
}

int FileWriteDJInternal_Object(const DJValue *value, FILE *fp) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  int ans = 2;
  fputc('{', fp);
  for (size_t i = 0; i < obj->len; i++) {
    ans += EscapeStringAndWrite(obj->keys[i], obj->keylens[i], fp);
    fputc(':', fp);
    ans += 1;
    ans += WriteDJValueToFile(obj->values[i], fp);
    if (i != obj->len - 1) {
      ans += 1;
      fputc(',', fp);
    }
  }
  fputc('}', fp);
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
