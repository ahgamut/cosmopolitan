#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_AT_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_AT_H_
COSMOPOLITAN_C_START_

/**
 * @fileoverview AT_xxx constants for fcntl(), fopenat(), etc..
 * @see libc/sysv/consts/auxv.h for getauxval() constants
 */

extern const int AT_FDCWD_;
extern const int AT_SYMLINK_FOLLOW_;
extern const int AT_SYMLINK_NOFOLLOW_;
extern const int AT_REMOVEDIR_;
extern const int AT_EACCESS_;

COSMOPOLITAN_C_END_

#define AT_FDCWD            -100 /* picking linux values as default */
#define AT_SYMLINK_FOLLOW   0x0400
#define AT_SYMLINK_NOFOLLOW 0x0100
#define AT_REMOVEDIR        0x0200
#define AT_EACCESS          0x0200

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_AT_H_ */
