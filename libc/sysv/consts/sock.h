#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SOCK_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SOCK_H_
COSMOPOLITAN_C_START_

extern const int SOCK_CLOEXEC_;
extern const int SOCK_NONBLOCK_;

COSMOPOLITAN_C_END_

/* everyone agrees on these values internally */
#define SOCK_STREAM    1
#define SOCK_DGRAM     2
#define SOCK_RAW       3
#define SOCK_RDM       4
#define SOCK_SEQPACKET 5

/* picking linux values as default */
#define SOCK_CLOEXEC  0x080000
#define SOCK_NONBLOCK 0x0800

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SOCK_H_ */
