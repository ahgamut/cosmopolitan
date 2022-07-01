#ifndef THIRDPARTY_DABBAJSON_H
#define THIRDPARTY_DABBAJSON_H
#include "libc/stdio/stdio.h"

typedef enum __DJValueType {
  DJV_DOUBLE = 0,
  DJV_NULL = 1,
  DJV_BOOL = 2,
  DJV_INTEGER = 3,
  DJV_STRING = 4,
  DJV_ARRAY = 5,
  DJV_OBJECT = 6,
  DJV_ERROR = 7,
} DJValueType;

typedef struct __DJValue DJValue;
DJValueType GetTypeOfDJValue(const DJValue *);

/* while extracting from DJValue, no allocations/copies are made */
int DJValueToDouble(const DJValue *, double *);
int DJValueToInteger(const DJValue *, int64_t *);
int DJValueToString(const DJValue *, char **, size_t *);
int DJValueToArray(const DJValue *, DJValue ***, size_t *);
int DJValueToObject(const DJValue *, char ***, size_t **, DJValue ***,
                    size_t *);
int DJValueToBool(const DJValue *, bool *);
bool DJValueIsTrue(const DJValue *);
bool DJValueIsFalse(const DJValue *);
bool DJValueIsNull(const DJValue *);

/* when creating a DJValue, allocations/copies are made */
DJValue *DoubleToDJValue(const double number);
DJValue *IntegerToDJValue(const int64_t number);
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
int WriteDJValueToBuffer(const DJValue *, char *, size_t);

/* read JSON from file into a DJValue */
int ReadDJValueFromFile(FILE *, DJValue **);

/* read JSON from buffer into a DJValue */
int ReadDJValueFromBuffer(const char *, const size_t, DJValue **);

#endif /* THIRDPARTY_DABBAJSON_H */
