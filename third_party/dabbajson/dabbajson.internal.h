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
    uint64_t raw_u64;
    int64_t raw_i64;
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
size_t DJO_CountLinked(const DJObjectElement *);
/* frees values */
void DJO_FreeLinked(DJObjectElement *);
DJValue *ObjectElementsToDJValue(DJObjectElement *, size_t);

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
size_t DJA_CountLinked(const DJArrayElement *);
/* frees values */
void DJA_FreeLinked(DJArrayElement *);
DJValue *ArrayElementsToDJValue(DJArrayElement *, size_t);

struct __DJArray {
  DJValue **values;
  size_t len;
};

/* we're actually going to do the NaN-boxing on a DJValue* instead of the
 * DJValue. This means randomly trying to dereference a DJValue* may boom,
 * but then again, anybody using dabbajson.h shouldn't be able to do that,
 * because the external header doesn't tell you how big a DJValue actually is. 
 * (of course you can always force a segfault by recasting to another pointer
 * and then dereferencing it, but that's why this is an internal header.) */

#define DJPtrDoubleTAG  0xfff8000000000000ULL
#define DJPtrNullTAG    0xfff9000000000000ULL
#define DJPtrFalseTAG   0xfffa000000000000ULL
#define DJPtrTrueTAG    0xfffa000000000001ULL
#define DJPtrMiniIntTAG 0xfffb000000000000ULL
#define DJPtrIntegerTAG 0xfffc000000000000ULL
#define DJPtrStringTAG  0xfffd000000000000ULL
#define DJPtrArrayTAG   0xfffe000000000000ULL
#define DJPtrObjectTAG  0xffff000000000000ULL

#define DJPtrIS_Double(x) ((((uint64_t)((x))) & DJPtrDoubleTAG) <= DJPtrDoubleTAG)
#define DJPtrIS_Null(x)   ((((uint64_t)((x))) ^ DJPtrNullTAG) == 0)
#define DJPtrIS_True(x)   ((((uint64_t)((x))) ^ DJPtrTrueTAG) == 0)
#define DJPtrIS_False(x)  ((((uint64_t)((x))) ^ DJPtrFalseTAG) == 0)
#define DJPtrIS_MiniInt(x) \
  ((((uint64_t)((x))) & DJPtrMiniIntTAG) == DJPtrMiniIntTAG)
#define DJPtrIS_Integer(x) \
  ((((uint64_t)((x))) & DJPtrIntegerTAG) == DJPtrIntegerTAG)
#define DJPtrIS_String(x) ((((uint64_t)((x))) & DJPtrStringTAG) == DJPtrStringTAG)
#define DJPtrIS_Object(x) ((((uint64_t)((x))) & DJPtrObjectTAG) == DJPtrObjectTAG)
#define DJPtrIS_Array(x)  ((((uint64_t)((x))) & DJPtrArrayTAG) == DJPtrArrayTAG)

#define DJPtrIS_ActuallyPTR(x) \
  ((((uint64_t)((x))) & DJPtrIntegerTAG) >= DJPtrIntegerTAG)

#define UNBOX_DJPtrTypeONLY(x) \
  ((DJValueType)(((uint64_t)((x))) > DJPtrDoubleTAG ? (0x0007 & (((uint64_t)((x))) >> 48)) : 0))

#define UPPER16BITS_OF_U64 0xffff000000000000ULL
#define UPPER17BITS_OF_U64 0xffff800000000000ULL
#define LOWER48BITS_OF_U64 0x0000ffffffffffffULL
#define BIT47_OF_U64       0x0000800000000000ULL
#define MiniIntSIGNBIT     BIT47_OF_U64

#define GETLOWER48_OF_U64(x) (((uint64_t)((x))) & LOWER48BITS_OF_U64)

#define SIGNEXTEND_MiniInt(x) \
  ((x)&UPPER17BITS_OF_U64 ? (x) | UPPER17BITS_OF_U64 : (x)&LOWER48BITS_OF_U64)
#define FITS_IN_MiniInt(x) \
    (((x) & UPPER17BITS_OF_U64) == 0 || ((x) & UPPER17BITS_OF_U64) == UPPER17BITS_OF_U64)
#define UNBOX_DJPtrAsMiniInt(x) \
  ((int64_t)(SIGNEXTEND_MiniInt(GETLOWER48_OF_U64(x))))
#define BOX_MiniIntIntoDJPtr(mini, v) \
  ((v) = (DJValue*)((GETLOWER48_OF_U64((mini))) | DJPtrMiniIntTAG))

#define UNBOX_DJPtrAsInteger(x) ((int64_t *)(GETLOWER48_OF_U64(x)))
#define BOX_IntegerIntoDJPtr(ptr, v) \
  ((v) = (DJValue*)(((uint64_t)((ptr))) | DJPtrIntegerTAG))

#define UNBOX_DJPtrAsString(x)  ((DJString *)(GETLOWER48_OF_U64(x)))
#define BOX_StringIntoDJPtr(ptr, v) \
  ((v) = (DJValue*)(((uint64_t)((ptr))) | DJPtrStringTAG))

#define UNBOX_DJPtrAsArray(x)   ((DJArray *)(GETLOWER48_OF_U64(x)))
#define BOX_ArrayIntoDJPtr(ptr, v) \
  ((v) = (DJValue*)(((uint64_t)((ptr))) | DJPtrArrayTAG))

#define UNBOX_DJPtrAsObject(x)  ((DJObject *)(GETLOWER48_OF_U64(x)))
#define BOX_ObjectIntoDJPtr(ptr, v) \
  ((v) = (DJValue*)(((uint64_t)((ptr))) | DJPtrObjectTAG))

#endif /* THIRDPARTY_DABBAJSON_INTERNAL_H */
