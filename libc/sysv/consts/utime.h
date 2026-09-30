#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_UTIME_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_UTIME_H_
COSMOPOLITAN_C_START_

extern const int UTIME_NOW_;
extern const int UTIME_OMIT_;

COSMOPOLITAN_C_END_

#define UTIME_NOW  0x3fffffff /* picking linux values as default */
#define UTIME_OMIT 0x3ffffffe

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_UTIME_H_ */
