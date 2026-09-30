#ifndef COSMOPOLITAN_LIBC_CALLS_SYSCALL_SUPPORT_SYSV_INTERNAL_H_
#define COSMOPOLITAN_LIBC_CALLS_SYSCALL_SUPPORT_SYSV_INTERNAL_H_
COSMOPOLITAN_C_START_
/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § syscalls » system five » structless support               ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

long __syscall2(long, long, int);
int __syscall2i(long, long, int) asm("__syscall2");
long __syscall3(long, long, long, int);
int __syscall3i(long, long, long, int) asm("__syscall3");
long __syscall4(long, long, long, long, int);
int __syscall4i(long, long, long, long, int) asm("__syscall4");

bool __is_evil_path(const char *);
bool __is_linux_2_6_23(void);
bool32 sys_isatty_metal(int);
int __fixupnewfd(int, int);
int __linux2af(int);
int __linux2atfd(int);
int __linux2atflags(int);
unsigned long __linux2auxvkey(unsigned long);
struct timespec __linux2utimensentinel(struct timespec);
int __linux2clock(int);
int __linux2ioctl(unsigned long);
int __linux2iflag(int);
int __linux2map(int);
int __linux2msg(int);
int __linux2poll(int);
int __linux2sig(int);
int __linux2how(int);
int32_t __linux2sicode(int32_t);
int32_t __sicode2linux(int, int32_t);
uint32_t __linux2saflags(uint32_t);
int __linux2sock(int);
int __linux2socklevel(int);
int __linux2ssflags(int);
int __linux2sockopt(int, int);
int __notziposat(int, const char *);
int __af2linux(int);
int __atflag2linux(int);
int __clock2linux(int);
int __iflag2linux(int);
int __ioctl2linux(unsigned long);
int __map2linux(int);
int __msg2linux(int);
int __poll2linux(int);
int __sig2linux(int);
int __saflag2linux(uint32_t);
int __sock2linux(int);
int __ssflag2linux(int);
int __sockopt2linux(int, int);
int __tkill(int, int, void *);
int __xoflags(int);
int _isptmaster(int);
int _ptsname(int, char *, size_t);
int getdomainname_linux(char *, size_t);
int gethostname_bsd(char *, size_t, int);
int gethostname_linux(char *, size_t);
int gethostname_nt(char *, size_t, int);
int sys_msyscall(void *, size_t);
long sys_bogus(void);
ssize_t __getrandom(void *, size_t, unsigned);
void *__vdsosym(const char *, const char *);
void __onfork(void);
void __restore_rt();
void __restore_rt_netbsd(void);
void cosmo2flock(uintptr_t);
void flock2cosmo(uintptr_t);

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_CALLS_SYSCALL_SUPPORT_SYSV_INTERNAL_H_ */
