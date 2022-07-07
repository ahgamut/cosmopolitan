#ifndef THIRDPARTY_DABBAJSON_TEST_HELPER_H
#define THIRDPARTY_DABBAJSON_TEST_HELPER_H

#include "libc/assert.h"
#include "libc/str/str.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"

void CheckBufferConversion(DJValue *);
void CheckFileReadSuccess(const char *);
void CheckFileReadFailure(const char *);

#define CHECKFILEREADSUCCESS(x) {\
    STATIC_YOINK(x);\
    CheckFileReadSuccess(x);\
}

#define CHECKFILEREADFAILURE(x) {\
    STATIC_YOINK(x);\
    CheckFileReadFailure(x);\
}

#endif
