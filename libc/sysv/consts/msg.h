#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_MSG_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_MSG_H_
COSMOPOLITAN_C_START_

extern const int MSG_DONTWAIT_;
extern const int MSG_WAITALL_;
extern const int MSG_NOSIGNAL_;
extern const int MSG_TRUNC_;
extern const int MSG_CTRUNC_;
extern const int MSG_FASTOPEN_;

COSMOPOLITAN_C_END_

/* everyone agrees on these values internally */
#define MSG_OOB       1
#define MSG_PEEK      2
#define MSG_DONTROUTE 4

/* picking linux values as default */
#define MSG_DONTWAIT  0x40
#define MSG_WAITALL   0x100
#define MSG_NOSIGNAL  0x4000
#define MSG_TRUNC     0x20
#define MSG_CTRUNC    8
/* polyfill: linux-only feature; unsupported systems slot -1 */
#define MSG_FASTOPEN 0x20000000

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_MSG_H_ */
