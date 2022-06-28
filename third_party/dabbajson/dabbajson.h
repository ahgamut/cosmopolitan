#ifndef THIRDPARTY_DABBAJSON_H
#define THIRDPARTY_DABBAJSON_H
#include "libc/stdio/stdio.h"

typedef enum __DJValueType {
  DJV_NUMBER = 0,
  DJV_NULL = 1,
  DJV_TRUE = 2,
  DJV_FALSE = 3,
  DJV_STRING = 4,
  DJV_ARRAY = 5,
  DJV_OBJECT = 6,
  DJV_CONVERSIONERROR = 7
} DJValueType;

typedef struct __DJValue DJValue;
DJValueType GetTypeOfDJValue(const DJValue *);

/* while extracting from DJValue, no allocations/copies are made */
int DJValueToNumber(const DJValue *, double *);
int DJValueToString(const DJValue *, char **, size_t *);
int DJValueToArray(const DJValue *, DJValue ***, size_t *);
int DJValueToObject(const DJValue *, char ***, size_t **, DJValue ***, size_t *);
int DJValueToBool(const DJValue *, bool *);
bool DJValueIsTrue(const DJValue *);
bool DJValueIsFalse(const DJValue *);
bool DJValueIsNull(const DJValue *);

/* when creating a DJValue, allocations/copies are made */
DJValue *NumberToDJValue(const double number);
DJValue *StringToDJValue(const char *, const size_t);
DJValue *ArrayToDJValue(const DJValue **, const size_t);
DJValue *ObjectToDJValue(const char **, const size_t *, const DJValue **,
                         const size_t);
DJValue *BoolToDJValue(const bool);
DJValue *NullToDJValue();

/* free DJValues allocated from above */
void FreeDJValue(DJValue *);

/* uses above creation methods to allocate a new DJValue */
DJValue *DuplicateDJValue(const DJValue *);

/* writes DJValue as JSON to file */
int WriteDJValueToFile(const DJValue *, FILE *);

/* writes DJValue as JSON into allocated buffer */
int WriteDJValueToBuffer(const DJValue *, char *buf, size_t buflen);

#endif /* THIRDPARTY_DABBAJSON_H */
