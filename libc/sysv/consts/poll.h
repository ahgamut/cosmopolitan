#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_POLL_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_POLL_H_
COSMOPOLITAN_C_START_

extern const int16_t POLLERR_;
extern const int16_t POLLHUP_;
extern const int16_t POLLIN_;
extern const int16_t POLLNVAL_;
extern const int16_t POLLOUT_;
extern const int16_t POLLPRI_;
extern const int16_t POLLRDBAND_;
extern const int16_t POLLRDHUP_;
extern const int16_t POLLRDNORM_;
extern const int16_t POLLWRBAND_;
extern const int16_t POLLWRNORM_;

COSMOPOLITAN_C_END_

#define INFTIM (-1)

/* picking linux values as default */
#define POLLIN     0x0001
#define POLLPRI    0x0002
#define POLLOUT    0x0004
#define POLLERR    0x0008
#define POLLHUP    0x0010
#define POLLNVAL   0x0020
#define POLLRDNORM 0x0040
#define POLLRDBAND 0x0080
#define POLLWRNORM 0x0100
#define POLLWRBAND 0x0200
/* polyfill: linux-only extension */
#define POLLRDHUP 0x2000

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_POLL_H_ */
