#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_PROT_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_PROT_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern const int PROT_GUARD_;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */

#define PROT_NONE  0
#define PROT_READ  1
#define PROT_WRITE 2
#define PROT_EXEC  4

/* cosmo-specific marker consumed by mprotect(); it maps to zero on
 * x86_64 linux, and to the aarch64 kernel's bti bit elsewhere */
#ifdef __aarch64__
#define PROT_GUARD 0x100
#else
#define PROT_GUARD 0
#endif

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_PROT_H_ */
