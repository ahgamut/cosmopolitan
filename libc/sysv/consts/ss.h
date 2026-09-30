#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SS_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SS_H_
COSMOPOLITAN_C_START_

extern const int SS_DISABLE_;
extern const int _SIGSTKSZ;
extern const int _MINSIGSTKSZ;

COSMOPOLITAN_C_END_

#define SIGSTKSZ    32768 /* just itself believed to be safe */
#define MINSIGSTKSZ 32768 /* xnu defines the highest minimum */
#define SS_ONSTACK  1     /* everyone agrees on this value */
#define SS_DISABLE  2     /* picking linux value as default */

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SS_H_ */
