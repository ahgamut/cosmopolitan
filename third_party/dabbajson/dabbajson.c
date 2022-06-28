#include "third_party/dabbajson/dabbajson.h"

#include "libc/assert.h"
#include "libc/log/log.h"
#include "libc/mem/mem.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.internal.h"

DJValueType GetTypeOfDJValue(const DJValue *value) {
  return UNBOX_DJValueTypeONLY(*value);
}

int DJValueToNumber(const DJValue *value, double *number) {
  if (!DJValueIS_Number(*value)) return -1;
  *number = UNBOX_DJValueAsNumber(*value);
  return 0;
}

int DJValueToString(const DJValue *value, char **ptr, size_t *len) {
  DJString *str;
  if (!DJValueIS_String(*value)) return -1;
  str = UNBOX_DJValueAsString(*value);
  // str is always non-NULL because the typecheck passed
  *ptr = str->ptr;
  *len = str->len;
  return 0;
}

int DJValueToArray(const DJValue *value, DJValue ***values, size_t *len) {
  DJArray *arr;
  if (!DJValueIS_Array(*value)) return -1;
  arr = UNBOX_DJValueAsArray(*value);
  // arr is always non-NULL because the typecheck passed
  *values = arr->values;
  *len = arr->len;
  return 0;
}

int DJValueToObject(const DJValue *value, char ***keys, size_t **keylens,
                    DJValue ***values, size_t *len) {
  DJObject *obj;
  if (!DJValueIS_Object(*value)) return -1;
  obj = UNBOX_DJValueAsObject(*value);
  // obj is always non-NULL because the typecheck passed
  *keys = obj->keys;
  *values = obj->values;
  *keylens = obj->keylens;
  *len = obj->len;
  return 0;
}

int DJValueToBool(const DJValue *value, bool *b) {
  if (DJValueIS_True(*value)) {
    *b = true;
    return 0;
  } else if (DJValueIS_False(*value)) {
    *b = false;
    return 0;
  } else {
    return -1;
  }
}

bool DJValueIsNull(const DJValue *value) {
  return DJValueIS_Null(*value);
}

bool DJValueIsTrue(const DJValue *value) {
  return DJValueIS_True(*value);
}

bool DJValueIsFalse(const DJValue *value) {
  return DJValueIS_False(*value);
}

DJValue *NumberToDJValue(const double number) {
  DJValue *answer = malloc(sizeof(DJValue));
  BOX_NumberIntoDJValue(number, *answer);
  return answer;
}

DJValue *BoolToDJValue(const bool b) {
  DJValue *answer = malloc(sizeof(DJValue));
  answer->__raw = b ? DJValueTrueTAG : DJValueFalseTAG;
  return answer;
}

DJValue *NullToDJValue() {
  DJValue *answer = malloc(sizeof(DJValue));
  answer->__raw = DJValueNullTAG;
  return answer;
}

DJValue *StringToDJValue(const char *ptr, const size_t len) {
  DJValue *answer = malloc(sizeof(DJValue));
  DJString *str = malloc(sizeof(DJString));
  str->ptr = strndup(ptr, len);
  str->len = len;
  BOX_StringIntoDJValue(str, *answer);
  return answer;
}

DJValue *ArrayToDJValue(const DJValue **values, const size_t len) {
  DJValue *answer = malloc(sizeof(DJValue));
  DJArray *arr = malloc(sizeof(DJArray));
  arr->len = len;
  arr->values = malloc(sizeof(DJValue *) * len);
  for (size_t i = 0; i < len; i++) {
    arr->values[i] = DuplicateDJValue(values[i]);
  }
  BOX_ArrayIntoDJValue(arr, *answer);
  return answer;
}

DJValue *ObjectToDJValue(const char **keys, const size_t *keylens,
                         const DJValue **values, const size_t len) {
  DJValue *answer = malloc(sizeof(DJValue));
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
  BOX_ObjectIntoDJValue(obj, *answer);
  return answer;
}

void FreeDJInternal_Dummy(DJValue *value) {
  /* doubles, bools, null, have nothing inside to be freed */
}

void FreeDJInternal_String(DJValue *value) {
  assert(DJValueIS_String(*value));
  DJString *str = UNBOX_DJValueAsString(*value);
  if (str->ptr) {
    free(str->ptr);
    str->ptr = NULL;
    str->len = 0;
  }
}

void FreeDJInternal_Array(DJValue *value) {
  assert(DJValueIS_Array(*value));
  DJArray *arr = UNBOX_DJValueAsArray(*value);
  if (arr->values) {
    for (size_t i = 0; i < arr->len; i++) {
      FreeDJValue(arr->values[i]);
    }
    free(arr->values);
    arr->values = NULL;
    arr->len = 0;
  }
}

void FreeDJInternal_Object(DJValue *value) {
  assert(DJValueIS_Object(*value));
  DJObject *obj = UNBOX_DJValueAsObject(*value);
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
}

void FreeDJInternal_Error(DJValue *value) {
  DIEF("attempted to free an invalid value");
}

static void (*_dj_internal_cleaners[])(DJValue *value) = {
    FreeDJInternal_Dummy,  /* DJV_NUMBER = 0 */
    FreeDJInternal_Dummy,  /* DJV_NULL = 1 */
    FreeDJInternal_Dummy,  /* DJV_TRUE = 2 */
    FreeDJInternal_Dummy,  /* DJV_FALSE = 3 */
    FreeDJInternal_String, /* DJV_STRING = 4 */
    FreeDJInternal_Array,  /* DJV_ARRAY = 5 */
    FreeDJInternal_Object, /* DJV_OBJECT = 6 */
    FreeDJInternal_Error,  /* DJV_CONVERSIONERROR = 7 */
};

void FreeDJValue(DJValue *value) {
  (_dj_internal_cleaners[UNBOX_DJValueTypeONLY(*value)])(value);
  free(value);
}

DJValue *DuplicateDJInternal_Bool(const DJValue *value) {
  assert(DJValueIS_True(*value) || DJValueIS_False(*value));
  return BoolToDJValue(DJValueIS_True(*value));
}

DJValue *DuplicateDJInternal_Number(const DJValue *value) {
  assert(DJValueIS_Number(*value));
  return NumberToDJValue(UNBOX_DJValueAsNumber(*value));
}

DJValue *DuplicateDJInternal_Null(const DJValue *value) {
  assert(DJValueIS_Null(*value));
  return NullToDJValue();
}

DJValue *DuplicateDJInternal_String(const DJValue *value) {
  assert(DJValueIS_String(*value));
  DJString *str = UNBOX_DJValueAsString(*value);
  return StringToDJValue(str->ptr, str->len);
}

DJValue *DuplicateDJInternal_Array(const DJValue *value) {
  assert(DJValueIS_Array(*value));
  DJArray *arr = UNBOX_DJValueAsArray(*value);
  return ArrayToDJValue((const DJValue **)arr->values, arr->len);
}

DJValue *DuplicateDJInternal_Object(const DJValue *value) {
  assert(DJValueIS_Object(*value));
  DJObject *obj = UNBOX_DJValueAsObject(*value);
  return ObjectToDJValue((const char **)obj->keys, (const size_t *)obj->keylens,
                         (const DJValue **)obj->values, obj->len);
}

DJValue *DuplicateDJInternal_Error(const DJValue *value) {
  DIEF("attempted to duplicate an invalid value");
  return NULL;
}

static DJValue* (*_dj_internal_duplicators[])(const DJValue *value) = {
    DuplicateDJInternal_Number, /* DJV_NUMBER = 0 */
    DuplicateDJInternal_Null,   /* DJV_NULL = 1 */
    DuplicateDJInternal_Bool,   /* DJV_TRUE = 2 */
    DuplicateDJInternal_Bool,   /* DJV_FALSE = 3 */
    DuplicateDJInternal_String, /* DJV_STRING = 4 */
    DuplicateDJInternal_Array,  /* DJV_ARRAY = 5 */
    DuplicateDJInternal_Object, /* DJV_OBJECT = 6 */
    DuplicateDJInternal_Error,  /* DJV_CONVERSIONERROR = 7 */
};

DJValue *DuplicateDJValue(const DJValue *value) {
  return (_dj_internal_duplicators[UNBOX_DJValueTypeONLY(*value)])(value);
}

int FileWriteDJInternal_Number(const DJValue *value, FILE *fp) {
  assert(DJValueIS_Number(*value));
  return fprintf(fp, "%lf", UNBOX_DJValueAsNumber(*value));
}

int FileWriteDJInternal_Null(const DJValue *value, FILE *fp) {
  assert(DJValueIS_Null(*value));
  return fprintf(fp, "null");
}

int FileWriteDJInternal_Bool(const DJValue *value, FILE *fp) {
  assert(DJValueIS_True(*value) || DJValueIS_False(*value));
  if (DJValueIS_True(*value)) {
    return fprintf(fp, "true");
  } else {
    return fprintf(fp, "false");
  }
}

int FileWriteDJInternal_String(const DJValue *value, FILE *fp) {
  assert(DJValueIS_String(*value));
  DJString *str = UNBOX_DJValueAsString(*value);
  return fprintf(fp, "\"%s\"", str->ptr);
}

int FileWriteDJInternal_Array(const DJValue *value, FILE *fp) {
  assert(DJValueIS_Array(*value));
  DJArray *arr = UNBOX_DJValueAsArray(*value);
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
  assert(DJValueIS_Object(*value));
  DJObject *obj = UNBOX_DJValueAsObject(*value);
  int ans = 0;
  ans += fprintf(fp, "{");
  for (size_t i = 0; i < obj->len; i++) {
    ans += fprintf(fp, "\"%s\":", obj->keys[i]);
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

static int (*_dj_internal_filewriters[])(const DJValue *value, FILE *fp) = {
    FileWriteDJInternal_Number, /* DJV_NUMBER = 0 */
    FileWriteDJInternal_Null,   /* DJV_NULL = 1 */
    FileWriteDJInternal_Bool,   /* DJV_TRUE = 2 */
    FileWriteDJInternal_Bool,   /* DJV_FALSE = 3 */
    FileWriteDJInternal_String, /* DJV_STRING = 4 */
    FileWriteDJInternal_Array,  /* DJV_ARRAY = 5 */
    FileWriteDJInternal_Object, /* DJV_OBJECT = 6 */
    FileWriteDJInternal_Error,  /* DJV_CONVERSIONERROR = 7 */
};

int WriteDJValueToFile(const DJValue *value, FILE *fp) {
  return (_dj_internal_filewriters[UNBOX_DJValueTypeONLY(*value)])(value, fp);
}
