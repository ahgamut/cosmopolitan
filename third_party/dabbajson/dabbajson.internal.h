#ifndef THIRDPARTY_DABBAJSON_INTERNAL_H
#define THIRDPARTY_DABBAJSON_INTERNAL_H
#include "third_party/dabbajson/dabbajson.h"

typedef struct __DJArray DJArray;
typedef struct __DJObject DJObject;
typedef struct __DJString DJString;
typedef struct __DJArrayElement DJArrayElement;
typedef struct __DJObjectElement DJObjectElement;

struct __DJString {
  char *ptr;
  size_t len;
};

struct __DJValue {
  /* NAN-boxing!!! */
  union {
    uint64_t __raw;
    double number;
  };
};

struct __DJObjectElement {
  char *key;
  DJValue *value;
  size_t keylen;
  struct __DJObjectElement *next;
};

DJObjectElement *DJO_New();
void DJO_FreeLinked(DJObjectElement *);
size_t DJO_CountLinked(DJObjectElement *);

struct __DJObject {
  char **keys;
  DJValue **values;
  size_t *keylens;
  size_t len;
};

struct __DJArrayElement {
  DJValue *value;
  struct __DJArrayElement *next;
};

DJArrayElement *DJA_New();
void DJA_FreeLinked(DJArrayElement *);
size_t DJA_CountLinked(DJArrayElement *);

struct __DJArray {
  DJValue **values;
  size_t len;
};

#define DJValueDoubleTAG  0xfff8000000000000ULL
#define DJValueNullTAG    0xfff9000000000000ULL
#define DJValueTrueTAG    0xfffa000000000000ULL
#define DJValueFalseTAG   0xfffb000000000000ULL
#define DJValueIntegerTAG 0xfffc000000000000ULL
#define DJValueStringTAG  0xfffd000000000000ULL
#define DJValueArrayTAG   0xfffe000000000000ULL
#define DJValueObjectTAG  0xffff000000000000ULL

#define DJValueIS_Double(x) (((x).__raw & DJValueDoubleTAG) <= DJValueDoubleTAG)
#define DJValueIS_Null(x)   (((x).__raw & DJValueNullTAG) == DJValueNullTAG)
#define DJValueIS_True(x)   (((x).__raw & DJValueTrueTAG) == DJValueTrueTAG)
#define DJValueIS_False(x)  (((x).__raw & DJValueFalseTAG) == DJValueFalseTAG)
#define DJValueIS_Integer(x) \
  (((x).__raw & DJValueIntegerTAG) == DJValueIntegerTAG)
#define DJValueIS_String(x) (((x).__raw & DJValueStringTAG) == DJValueStringTAG)
#define DJValueIS_Object(x) (((x).__raw & DJValueObjectTAG) == DJValueObjectTAG)
#define DJValueIS_Array(x)  (((x).__raw & DJValueArrayTAG) == DJValueArrayTAG)

#define DJValueIS_ActuallyPTR(x) \
  (((x).__raw & DJValueIntegerTAG) >= DJValueIntegerTAG)

#define UNBOX_DJValueTypeONLY(x) \
  ((DJValueType)((x).__raw > DJValueDoubleTAG ? (0x0007 & (x).__raw >> 48) : 0))
#define UNBOX_DJValueAsPTR(x) ((x).__raw & 0x0000ffffffffffffULL)

#define UNBOX_DJValueAsDouble(x)  ((double)((x).number))
#define UNBOX_DJValueAsInteger(x) ((int64_t *)(UNBOX_DJValueAsPTR(x)))
#define UNBOX_DJValueAsString(x)  ((DJString *)(UNBOX_DJValueAsPTR(x)))
#define UNBOX_DJValueAsArray(x)   ((DJArray *)(UNBOX_DJValueAsPTR(x)))
#define UNBOX_DJValueAsObject(x)  ((DJObject *)(UNBOX_DJValueAsPTR(x)))

#define BOX_DoubleIntoDJValue(number, v) ((v).number = number)
#define BOX_IntegerIntoDJValue(ptr, v) \
  ((v).__raw = ((uint64_t)((ptr))) | DJValueIntegerTAG)
#define BOX_StringIntoDJValue(ptr, v) \
  ((v).__raw = ((uint64_t)((ptr))) | DJValueStringTAG)
#define BOX_ArrayIntoDJValue(ptr, v) \
  ((v).__raw = ((uint64_t)((ptr))) | DJValueArrayTAG)
#define BOX_ObjectIntoDJValue(ptr, v) \
  ((v).__raw = ((uint64_t)((ptr))) | DJValueObjectTAG)

#endif /* THIRDPARTY_DABBAJSON_INTERNAL_H */
