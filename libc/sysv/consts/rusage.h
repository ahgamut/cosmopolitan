#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_RUSAGE_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_RUSAGE_H_
COSMOPOLITAN_C_START_

extern const int RUSAGE_BOTH_;
extern const int RUSAGE_CHILDREN_;
extern const int RUSAGE_THREAD_;

COSMOPOLITAN_C_END_

#define RUSAGE_SELF     0 /* picking linux values as default */
#define RUSAGE_CHILDREN -1
#define RUSAGE_THREAD   1
#define RUSAGE_BOTH     -2

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_RUSAGE_H_ */
