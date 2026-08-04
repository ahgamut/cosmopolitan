#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_MAP_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_MAP_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern const int MAP_32BIT_;
extern const int MAP_ANON_;
extern const int MAP_ANONYMOUS_;
extern const int MAP_CONCEAL_;
extern const int MAP_DENYWRITE_;
extern const int MAP_EXECUTABLE_;
extern const int MAP_FILE_;
extern const int MAP_FIXED_;
extern const int MAP_FIXED_NOREPLACE_;
extern const int MAP_HASSEMAPHORE_;
extern const int MAP_HUGETLB_;
extern const int MAP_INHERIT_;
extern const int MAP_JIT_;
extern const int MAP_LOCKED_;
extern const int MAP_NOCACHE_;
extern const int MAP_NOEXTEND_;
extern const int MAP_NONBLOCK_;
extern const int MAP_NORESERVE_;
extern const int MAP_NOSYNC_;
extern const int MAP_SYNC_;
extern const int MAP_POPULATE_;
extern const int MAP_PRIVATE_;
extern const int MAP_SHARED_;
extern const int MAP_SHARED_VALIDATE_;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */

#define MAP_FILE_            0x00000000
#define MAP_SHARED_          0x00000001
#define MAP_PRIVATE_         0x00000002
#define MAP_SHARED_VALIDATE_ 0x00000003
#define MAP_TYPE_            0x0000000f
#define MAP_FIXED_           0x00000010

/* everyone agrees on these values internally */
#define MAP_FILE            0x00000000
#define MAP_SHARED          0x00000001
#define MAP_PRIVATE         0x00000002
#define MAP_SHARED_VALIDATE 0x00000003
#define MAP_TYPE            0x0000000f
#define MAP_FIXED           0x00000010
/* picking linux values as default, polyfilling gaps */
#define MAP_ANONYMOUS       0x00000020
#define MAP_32BIT           0x00000040
#define MAP_CONCEAL         0x00000080 /* polyfill */
#define MAP_HASSEMAPHORE    0x00000100 /* polyfill */
#define MAP_NOSYNC          0x00000200 /* polyfill */
#define MAP_JIT             0x00000400 /* polyfill */
#define MAP_DENYWRITE       0x00000800
#define MAP_EXECUTABLE      0x00001000
#define MAP_LOCKED          0x00002000
#define MAP_NORESERVE       0x00004000
#define MAP_POPULATE        0x00008000
#define MAP_NONBLOCK        0x00010000
#define MAP_INHERIT         0x00020000 /* polyfill */
#define MAP_HUGETLB         0x00040000
#define MAP_SYNC            0x00080000
#define MAP_FIXED_NOREPLACE 0x00100000 /* linux/freebsd weirdness */
#define MAP_NOCACHE         0x00200000 /* polyfill */
#define MAP_NOEXTEND        0x00400000 /* polyfill */

#define MAP_ANON   MAP_ANONYMOUS
#define MAP_NOCORE MAP_CONCEAL

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_MAP_H_ */
