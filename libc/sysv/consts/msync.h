#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_MSYNC_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_MSYNC_H_
COSMOPOLITAN_C_START_

extern const int MS_SYNC_;
extern const int MS_ASYNC_;
extern const int MS_INVALIDATE_;

COSMOPOLITAN_C_END_

#define MS_SYNC       4 /* picking linux values as default */
#define MS_ASYNC      1
#define MS_INVALIDATE 2

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_MSYNC_H_ */
