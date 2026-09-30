#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SO_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SO_H_

COSMOPOLITAN_C_START_

extern const int SO_TYPE_;
extern const int SO_ERROR_;
extern const int SO_ACCEPTCONN_;
extern const int SO_REUSEADDR_;
extern const int SO_KEEPALIVE_;
extern const int SO_DONTROUTE_;
extern const int SO_BROADCAST_;
extern const int SO_USELOOPBACK_;
extern const int SO_LINGER_;
extern const int SO_OOBINLINE_;
extern const int SO_SNDBUF_;
extern const int SO_RCVBUF_;
extern const int SO_RCVTIMEO_;
extern const int SO_SNDTIMEO_;
extern const int SO_RCVLOWAT_;
extern const int SO_SNDLOWAT_;
extern const int SO_REUSEPORT_;

COSMOPOLITAN_C_END_

/* everyone agrees on these values internally */
#define SO_DEBUG 1

/* picking linux values as default */
#define SO_TYPE        3
#define SO_ERROR       4
#define SO_ACCEPTCONN  30
#define SO_REUSEADDR   2
#define SO_KEEPALIVE   9
#define SO_DONTROUTE   5
#define SO_BROADCAST   6
#define SO_USELOOPBACK 0
#define SO_LINGER      13
#define SO_OOBINLINE   10
#define SO_SNDBUF      7
#define SO_RCVBUF      8
#define SO_RCVTIMEO    20
#define SO_SNDTIMEO    21
#define SO_RCVLOWAT    18
#define SO_SNDLOWAT    19

/*
 * this isn't available on windows, but it should be fine to use anyway,
 * setsockopt will return ENOPROTOOPT which is perfectly fine to ignore.
 */
/* polyfill: only bsd-like systems offer this */
#define SO_REUSEPORT 15

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SO_H_ */
