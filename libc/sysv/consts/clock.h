#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_CLOCK_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_CLOCK_H_
COSMOPOLITAN_C_START_

extern int CLOCK_REALTIME_COARSE_;
extern const int CLOCK_MONOTONIC_;
extern int CLOCK_MONOTONIC_RAW_;
extern int CLOCK_MONOTONIC_COARSE_;
extern const int CLOCK_THREAD_CPUTIME_ID_;
extern const int CLOCK_PROCESS_CPUTIME_ID_;
extern const int CLOCK_BOOTTIME_;

COSMOPOLITAN_C_END_

/* everyone agrees on these values internally */
#define CLOCK_REALTIME_ 0
/* picking linux values as default */
#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3
#define CLOCK_MONOTONIC_RAW      4
#define CLOCK_REALTIME_COARSE    5
#define CLOCK_MONOTONIC_COARSE   6
#define CLOCK_BOOTTIME           7

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_CLOCK_H_ */
