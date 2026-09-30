#ifndef COSMOPOLITAN_LIBC_CALLS_AUXV_H_
#define COSMOPOLITAN_LIBC_CALLS_AUXV_H_

/*
 * integral getauxval() keys
 */
#define AT_PHDR                     3
#define AT_PHENT                    4
#define AT_PHNUM                    5
#define AT_PAGESZ                   6
#define AT_BASE                     7
#define AT_FLAGS                    8
#define AT_FLAGS_PRESERVE_ARGV0_BIT 0
#define AT_FLAGS_PRESERVE_ARGV0     (1 << AT_FLAGS_PRESERVE_ARGV0_BIT)
#define AT_ENTRY                    9

COSMOPOLITAN_C_START_

/*
 * platform-proprietary getauxval() keys that linux doesn't define
 * stay runtime externs, since their canonical value is zero and
 * couldn't be told apart when translating a query
 */
extern const unsigned long AT_CANARY;
extern const unsigned long AT_CANARYLEN;
extern const unsigned long AT_EHDRFLAGS;
extern const unsigned long AT_NCPUS;
extern const unsigned long AT_OSRELDATE;
extern const unsigned long AT_PAGESIZES;
extern const unsigned long AT_PAGESIZESLEN;
extern const unsigned long AT_STACKBASE;
extern const unsigned long AT_STACKPROT;
extern const unsigned long AT_TIMEKEEP;

/*
 * portable getauxval() keys
 */
extern const unsigned long AT_EXECFN_;
extern const unsigned long AT_EXECPATH_;
extern const unsigned long AT_SECURE_;
extern const unsigned long AT_RANDOM_;
extern const unsigned long AT_HWCAP_;
extern const unsigned long AT_HWCAP2_;
extern const unsigned long AT_UID_;
extern const unsigned long AT_EUID_;
extern const unsigned long AT_GID_;
extern const unsigned long AT_EGID_;

/*
 * platform-specific getauxval() keys
 */
extern const unsigned long AT_BASE_PLATFORM_;
extern const unsigned long AT_CLKTCK_;
extern const unsigned long AT_DCACHEBSIZE_;
extern const unsigned long AT_EXECFD_;
extern const unsigned long AT_ICACHEBSIZE_;
extern const unsigned long AT_MINSIGSTKSZ_;
extern const unsigned long AT_NOTELF_;
extern const unsigned long AT_NO_AUTOMOUNT_;
extern const unsigned long AT_PLATFORM_;
extern const unsigned long AT_SYSINFO_EHDR_;
extern const unsigned long AT_UCACHEBSIZE_;

COSMOPOLITAN_C_END_

/*
 * picking linux values as default
 */
#define AT_EXECFN        31
#define AT_EXECPATH      31
#define AT_SECURE        23
#define AT_RANDOM        25
#define AT_HWCAP         16
#define AT_HWCAP2        26
#define AT_UID           11
#define AT_EUID          12
#define AT_GID           13
#define AT_EGID          14
#define AT_BASE_PLATFORM 24
#define AT_CLKTCK        17
#define AT_DCACHEBSIZE   19
#define AT_EXECFD        2
#define AT_ICACHEBSIZE   20
#define AT_MINSIGSTKSZ   51
#define AT_NOTELF        10
#define AT_NO_AUTOMOUNT  0x0800
#define AT_PLATFORM      15
#define AT_SYSINFO_EHDR  33
#define AT_UCACHEBSIZE   21

#endif /* COSMOPOLITAN_LIBC_CALLS_AUXV_H_ */
