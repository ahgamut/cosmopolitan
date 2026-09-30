#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_WAITID_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_WAITID_H_
COSMOPOLITAN_C_START_

extern const int WEXITED_;
extern const int WSTOPPED_;
extern const int WNOWAIT_;

COSMOPOLITAN_C_END_

#define WEXITED  4 /* picking linux values as default */
#define WSTOPPED 2
#define WNOWAIT  0x01000000

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_WAITID_H_ */
