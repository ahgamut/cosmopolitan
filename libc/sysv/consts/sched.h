#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SCHED_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SCHED_H_
COSMOPOLITAN_C_START_

extern const int SCHED_BATCH_;
extern const int SCHED_DEADLINE_;
extern const int SCHED_FIFO_;
extern const int SCHED_IDLE_;
extern const int SCHED_OTHER_;
extern const int SCHED_RESET_ON_FORK_;
extern const int SCHED_RR_;

COSMOPOLITAN_C_END_

#define SCHED_BATCH          3 /* picking linux values as default */
#define SCHED_DEADLINE       6
#define SCHED_FIFO           1
#define SCHED_IDLE           5
#define SCHED_OTHER          0
#define SCHED_RESET_ON_FORK  0x40000000
#define SCHED_RR             2

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SCHED_H_ */
