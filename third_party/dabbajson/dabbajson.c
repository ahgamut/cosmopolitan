#include "libc/assert.h"
#include "libc/log/log.h"
#include "libc/mem/mem.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"

DJValueType GetTypeOfDJValue(const DJValue *value) {
  static DJValueType actual_tags[] = {
      DJV_DOUBLE,  DJV_NULL,  DJV_BOOL,
      DJV_INTEGER, /* -2^47 to 2^47-1, no malloc */
      DJV_INTEGER, /* "big" int64_t, calls malloc */
      DJV_STRING,  DJV_ARRAY, DJV_OBJECT};
  return actual_tags[UNBOX_DJPtrTypeONLY(value)];
}

int DJValueToDouble(const DJValue *value, double *number) {
  if (!DJPtrIS_Double(value)) return -1;
  DJValue x = {.raw_u64 = (uint64_t)(value)};
  *number = x.number;
  return 0;
}

int DJValueToInteger(const DJValue *value, int64_t *number) {
  if (DJPtrIS_MiniInt(value)) {
    /* MiniInt is not via pointer */
    *number = (UNBOX_DJPtrAsMiniInt(value));
    return 0;
  } else if (DJPtrIS_Integer(value)) {
    /* Integer is via pointer */
    *number = *(UNBOX_DJPtrAsInteger(value));
    return 0;
  } else {
    return -1;
  }
}

int DJValueToString(const DJValue *value, char **ptr, size_t *len) {
  DJString *str;
  if (!DJPtrIS_String(value)) return -1;
  str = UNBOX_DJPtrAsString(value);
  // str is always non-NULL because the typecheck passed
  *ptr = str->ptr;
  *len = str->len;
  return 0;
}

int DJValueToArray(const DJValue *value, DJValue ***values, size_t *len) {
  DJArray *arr;
  if (!DJPtrIS_Array(value)) return -1;
  arr = UNBOX_DJPtrAsArray(value);
  // arr is always non-NULL because the typecheck passed
  *values = arr->values;
  *len = arr->len;
  return 0;
}

int DJValueToObject(const DJValue *value, char ***keys, size_t **keylens,
                    DJValue ***values, size_t *len) {
  DJObject *obj;
  if (!DJPtrIS_Object(value)) return -1;
  obj = UNBOX_DJPtrAsObject(value);
  // obj is always non-NULL because the typecheck passed
  *keys = obj->keys;
  *values = obj->values;
  *keylens = obj->keylens;
  *len = obj->len;
  return 0;
}

int DJValueToBool(const DJValue *value, bool *b) {
  if (DJPtrIS_True(value)) {
    *b = true;
    return 0;
  } else if (DJPtrIS_False(value)) {
    *b = false;
    return 0;
  } else {
    return -1;
  }
}

bool DJValueIsNull(const DJValue *value) {
  return DJPtrIS_Null(value);
}

bool DJValueIsTrue(const DJValue *value) {
  return DJPtrIS_True(value);
}

bool DJValueIsFalse(const DJValue *value) {
  return DJPtrIS_False(value);
}

DJValue *DoubleToDJValue(const double number) {
  DJValue answer = {.number = number};
  return (DJValue*)(answer.raw_u64);
}

DJValue *IntegerToDJValue(const int64_t number) {
  int64_t *copy;
  DJValue *answer = NULL;
  if (FITS_IN_MiniInt(number)) {
    BOX_MiniIntIntoDJPtr(number, answer);
    return answer;
  }
  copy = malloc(sizeof(int64_t));
  *copy = number;
  BOX_IntegerIntoDJPtr(copy, answer);
  return answer;
}

DJValue *BoolToDJValue(const bool b) {
  DJValue *answer;
  answer = (DJValue*)(b ? DJPtrTrueTAG : DJPtrFalseTAG);
  return answer;
}

DJValue *NullToDJValue() {
  DJValue *answer = (DJValue*)(DJPtrNullTAG);
  return answer;
}

DJValue *StringToDJValue(const char *ptr, const size_t len) {
  DJValue *answer = NULL;
  DJString *str = malloc(sizeof(DJString));
  str->ptr = strndup(ptr, len);
  str->len = len;
  BOX_StringIntoDJPtr(str, answer);
  return answer;
}

DJValue *ArrayToDJValue(const DJValue **values, const size_t len) {
  DJValue *answer = NULL;
  DJArray *arr = malloc(sizeof(DJArray));
  arr->len = len;
  arr->values = malloc(sizeof(DJValue *) * len);
  for (size_t i = 0; i < len; i++) {
    arr->values[i] = DuplicateDJValue(values[i]);
  }
  BOX_ArrayIntoDJPtr(arr, answer);
  return answer;
}

DJValue *ObjectToDJValue(const char **keys, const size_t *keylens,
                         const DJValue **values, const size_t len) {
  DJValue *answer = NULL;
  DJObject *obj = malloc(sizeof(DJObject));
  obj->len = len;
  obj->keys = malloc(sizeof(char *) * len);
  obj->keylens = malloc(sizeof(size_t) * len);
  obj->values = malloc(sizeof(DJValue *) * len);
  for (size_t i = 0; i < len; i++) {
    obj->keys[i] = strndup(keys[i], keylens[i]);
    obj->keylens[i] = keylens[i];
    obj->values[i] = DuplicateDJValue(values[i]);
  }
  BOX_ObjectIntoDJPtr(obj, answer);
  return answer;
}

void FreeDJInternal_Dummy(DJValue *value) {
  /* doubles, bools, null, mini-ints have nothing inside to be freed */
}

void FreeDJInternal_Integer(DJValue *value) {
  assert(DJPtrIS_Integer(value));
  int64_t *ptr = UNBOX_DJPtrAsInteger(value);
  if (ptr) {
    free(ptr);
  }
}

void FreeDJInternal_String(DJValue *value) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  if (str->ptr) {
    free(str->ptr);
    str->ptr = NULL;
    str->len = 0;
  }
  free(str);
}

void FreeDJInternal_Array(DJValue *value) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  if (arr->values) {
    for (size_t i = 0; i < arr->len; i++) {
      FreeDJValue(arr->values[i]);
    }
    free(arr->values);
    arr->values = NULL;
    arr->len = 0;
  }
  free(arr);
}

void FreeDJInternal_Object(DJValue *value) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  if (obj->values) {
    for (size_t i = 0; i < obj->len; i++) {
      FreeDJValue(obj->values[i]);
      free(obj->keys[i]);
    }
    free(obj->values);
    free(obj->keys);
    free(obj->keylens);
    obj->len = 0;
  }
  free(obj);
}

void FreeDJInternal_Error(DJValue *value) {
  DIEF("attempted to free an invalid value");
}

static void (*_dj_cleaners[])(DJValue *value) = {
    FreeDJInternal_Dummy,   /* Double */
    FreeDJInternal_Dummy,   /* Null */
    FreeDJInternal_Dummy,   /* Bool */
    FreeDJInternal_Dummy,   /* MiniInt */
    FreeDJInternal_Integer, /* Integer */
    FreeDJInternal_String,  /* DJString* */
    FreeDJInternal_Array,   /* DJArray* */
    FreeDJInternal_Object,  /* DJObject* */
};

void FreeDJValue(DJValue *value) {
  (_dj_cleaners[UNBOX_DJPtrTypeONLY(value)])(value);
}

DJValue *DuplicateDJInternal_Bool(const DJValue *value) {
  assert(DJPtrIS_True(value) || DJPtrIS_False(value));
  return BoolToDJValue(DJPtrIS_True(value));
}

DJValue *DuplicateDJInternal_Double(const DJValue *value) {
  assert(DJPtrIS_Double(value));
  DJValue x = {.raw_u64 = (uint64_t)(value)};
  return DoubleToDJValue(x.number);
}

DJValue *DuplicateDJInternal_Null(const DJValue *value) {
  assert(DJPtrIS_Null(value));
  return NullToDJValue();
}

DJValue *DuplicateDJInternal_MiniInt(const DJValue *value) {
  assert(DJPtrIS_MiniInt(value));
  int64_t number = UNBOX_DJPtrAsMiniInt(value);
  return IntegerToDJValue(number);
}

DJValue *DuplicateDJInternal_Integer(const DJValue *value) {
  assert(DJPtrIS_Integer(value));
  int64_t *ptr = UNBOX_DJPtrAsInteger(value);
  return IntegerToDJValue(*ptr);
}

DJValue *DuplicateDJInternal_String(const DJValue *value) {
  assert(DJPtrIS_String(value));
  DJString *str = UNBOX_DJPtrAsString(value);
  return StringToDJValue(str->ptr, str->len);
}

DJValue *DuplicateDJInternal_Array(const DJValue *value) {
  assert(DJPtrIS_Array(value));
  DJArray *arr = UNBOX_DJPtrAsArray(value);
  return ArrayToDJValue((const DJValue **)arr->values, arr->len);
}

DJValue *DuplicateDJInternal_Object(const DJValue *value) {
  assert(DJPtrIS_Object(value));
  DJObject *obj = UNBOX_DJPtrAsObject(value);
  return ObjectToDJValue((const char **)obj->keys, (const size_t *)obj->keylens,
                         (const DJValue **)obj->values, obj->len);
}

DJValue *DuplicateDJInternal_Error(const DJValue *value) {
  DIEF("attempted to duplicate an invalid value");
  return NULL;
}

static DJValue *(*_dj_duplicators[])(const DJValue *value) = {
    DuplicateDJInternal_Double,  /* Double */
    DuplicateDJInternal_Null,    /* Null */
    DuplicateDJInternal_Bool,    /* Bool */
    DuplicateDJInternal_MiniInt, /* MiniInt */
    DuplicateDJInternal_Integer, /* Integer */
    DuplicateDJInternal_String,  /* DJString* */
    DuplicateDJInternal_Array,   /* DJArray* */
    DuplicateDJInternal_Object,  /* DJObject* */
};

DJValue *DuplicateDJValue(const DJValue *value) {
  return (_dj_duplicators[UNBOX_DJPtrTypeONLY(value)])(value);
}
