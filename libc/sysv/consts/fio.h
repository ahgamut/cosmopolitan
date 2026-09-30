#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_FIO_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_FIO_H_
COSMOPOLITAN_C_START_

extern const uint32_t FIONREAD_; /* one of the few encouraged ioctls */
extern const uint32_t FIONBIO_;  /* use fcntl(fd, F_SETFL, O_NONBLOCK) */
extern const uint32_t FIOCLEX_;  /* use fcntl(fd, F_SETFD, FD_CLOEXEC) */
extern const uint32_t FIONCLEX_; /* use fcntl(fd, F_SETFD, 0) */
extern const uint32_t FIOASYNC_; /* todo: fcntl(fd, F_SETOWN, pid) */

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define FIONREAD 0x541b
#define FIONBIO  0x5421
#define FIOCLEX  0x5451
#define FIONCLEX 0x5450
#define FIOASYNC 0x5452

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_FIO_H_ */
