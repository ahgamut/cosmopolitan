#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_W_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_W_H_
COSMOPOLITAN_C_START_

extern const int WCONTINUED_;

COSMOPOLITAN_C_END_

#define WNOHANG   1 /* everyone agrees on these values */
#define WUNTRACED 2
#define WCONTINUED 8 /* picking linux value as default */

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_W_H_ */
