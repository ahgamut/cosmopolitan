#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_ST_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_ST_H_
COSMOPOLITAN_C_START_

extern const int ST_APPEND_;
extern const int ST_IMMUTABLE_;
extern const int ST_MANDLOCK_;
extern const int ST_NOATIME_;
extern const int ST_NODEV_;
extern const int ST_NODIRATIME_;
extern const int ST_NOEXEC_;
extern const int ST_NOSUID_;
extern const int ST_RDONLY_;
extern const int ST_RELATIME_;
extern const int ST_SYNCHRONOUS_;
extern const int ST_WRITE_;

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define ST_APPEND       0x0100
#define ST_IMMUTABLE    0x0200
#define ST_MANDLOCK     0x0040
#define ST_NOATIME      0x0040
#define ST_NODEV        4
#define ST_NODIRATIME   0x0800
#define ST_NOEXEC       8
#define ST_NOSUID       2
#define ST_RDONLY       1
#define ST_RELATIME     0x1000
#define ST_SYNCHRONOUS  0x10
#define ST_WRITE        0x0080

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_ST_H_ */
