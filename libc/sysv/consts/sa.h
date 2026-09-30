#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SA_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SA_H_
COSMOPOLITAN_C_START_

extern const unsigned SA_NOCLDSTOP_;
extern const unsigned SA_NOCLDWAIT_;
extern const unsigned SA_NODEFER_;
extern const unsigned SA_ONSTACK_;
extern const unsigned SA_RESETHAND_;
extern const unsigned SA_RESTART_;
extern const unsigned SA_SIGINFO_;

#define SA_NOCLDSTOP 1 /* consensus on linux values */
#define SA_NOCLDWAIT 2
#define SA_SIGINFO   4
#define SA_ONSTACK   0x08000000
#define SA_RESTART   0x10000000
#define SA_NODEFER   0x40000000
#define SA_RESETHAND 0x80000000

/* compatibility constants */
#define SA_NOMASK  SA_NODEFER
#define SA_ONESHOT SA_RESETHAND

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SA_H_ */
