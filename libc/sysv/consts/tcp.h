#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_TCP_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_TCP_H_
COSMOPOLITAN_C_START_

extern const int TCP_CC_INFO_;
extern const int TCP_CONGESTION_;
extern const int TCP_COOKIE_TRANSACTIONS_;
extern const int TCP_CORK_;
extern const int TCP_DEFER_ACCEPT_;
extern const int TCP_FASTOPEN_;
extern const int TCP_FASTOPEN_CONNECT_;
extern const int TCP_INFO_;
extern const int TCP_KEEPCNT_;
extern const int TCP_KEEPIDLE_;
extern const int TCP_KEEPINTVL_;
extern const int TCP_LINGER2_;
extern const int TCP_MAXSEG_;
extern const int TCP_MD5SIG_;
extern const int TCP_MD5SIG_MAXKEYLEN_;
extern const int TCP_NOTSENT_LOWAT_;
extern const int TCP_QUEUE_SEQ_;
extern const int TCP_QUICKACK_;
extern const int TCP_REPAIR_;
extern const int TCP_REPAIR_OPTIONS_;
extern const int TCP_REPAIR_QUEUE_;
extern const int TCP_SAVED_SYN_;
extern const int TCP_SAVE_SYN_;
extern const int TCP_SYNCNT_;
extern const int TCP_THIN_DUPACK_;
extern const int TCP_THIN_LINEAR_TIMEOUTS_;
extern const int TCP_TIMESTAMP_;
extern const int TCP_ULP_;
extern const int TCP_USER_TIMEOUT_;
extern const int TCP_WINDOW_CLAMP_;

COSMOPOLITAN_C_END_

/* everyone agrees on these values internally */
#define TCP_NODELAY 1

/* picking linux values as default */
#define TCP_MAXSEG               2
#define TCP_CORK                 3
#define TCP_KEEPIDLE             4
#define TCP_KEEPINTVL            5
#define TCP_KEEPCNT              6
#define TCP_SYNCNT               7
#define TCP_LINGER2              8
#define TCP_DEFER_ACCEPT         9
#define TCP_WINDOW_CLAMP         10
#define TCP_INFO                 11
#define TCP_QUICKACK             12
#define TCP_CONGESTION           13
#define TCP_MD5SIG               14
#define TCP_COOKIE_TRANSACTIONS  15
#define TCP_THIN_LINEAR_TIMEOUTS 16
#define TCP_THIN_DUPACK          17
#define TCP_USER_TIMEOUT         18
#define TCP_REPAIR               19
#define TCP_REPAIR_QUEUE         20
#define TCP_QUEUE_SEQ            21
#define TCP_REPAIR_OPTIONS       22
#define TCP_FASTOPEN             23
#define TCP_TIMESTAMP            24
#define TCP_NOTSENT_LOWAT        25
#define TCP_CC_INFO              26
#define TCP_SAVE_SYN             27
#define TCP_SAVED_SYN            28
#define TCP_FASTOPEN_CONNECT     30
#define TCP_ULP                  31
/* polyfill: linux-only extension */
#define TCP_MD5SIG_MAXKEYLEN 80

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_TCP_H_ */
