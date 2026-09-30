#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SICODE_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SICODE_H_
COSMOPOLITAN_C_START_

extern const int32_t SI_ASYNCIO_;
extern const int32_t SI_ASYNCNL_;
extern const int32_t SI_KERNEL_;
extern const int32_t SI_MESGQ_;
extern const int32_t SI_NOINFO_;
extern const int32_t SI_QUEUE_;
extern const int32_t SI_TIMER_;
extern const int32_t SI_TKILL_;
extern const int32_t SI_USER_;
extern const int32_t BUS_MCEERR_AO_;
extern const int32_t BUS_MCEERR_AR_;
extern const int32_t BUS_OOMERR_;
extern const int32_t FPE_FLTDIV_;
extern const int32_t FPE_FLTINV_;
extern const int32_t FPE_FLTOVF_;
extern const int32_t FPE_FLTRES_;
extern const int32_t FPE_FLTSUB_;
extern const int32_t FPE_FLTUND_;
extern const int32_t FPE_INTDIV_;
extern const int32_t FPE_INTOVF_;
extern const int32_t ILL_ILLADR_;
extern const int32_t ILL_ILLOPN_;
extern const int32_t ILL_ILLTRP_;
extern const int32_t ILL_PRVOPC_;
extern const int32_t SEGV_PKUERR_;
extern const int32_t SYS_SECCOMP_;
extern const int32_t SYS_USER_DISPATCH_;

#define CLD_EXITED    1 /* everyone agrees on these values */
#define CLD_KILLED    2
#define CLD_DUMPED    3
#define CLD_TRAPPED   4
#define CLD_STOPPED   5
#define CLD_CONTINUED 6
#define TRAP_BRKPT    1
#define TRAP_TRACE    2
#define SEGV_MAPERR   1
#define SEGV_ACCERR   2
#define SEGV_PKUERR   -1
#define ILL_ILLOPC    1
#define ILL_ILLOPN    2
#define ILL_ILLADR    3
#define ILL_ILLTRP    4
#define ILL_PRVOPC    5
#define ILL_PRVREG    6
#define ILL_COPROC    7
#define ILL_BADSTK    8
#define FPE_INTDIV    1
#define FPE_INTOVF    2
#define FPE_FLTDIV    3
#define FPE_FLTOVF    4
#define FPE_FLTUND    5
#define FPE_FLTRES    6
#define FPE_FLTINV    7
#define FPE_FLTSUB    8
#define BUS_ADRALN    1
#define BUS_ADRERR    2
#define BUS_OBJERR    3
#define BUS_MCEERR_AO 5
#define BUS_MCEERR_AR 4
#define BUS_OOMERR    -1
#define POLL_IN       1
#define POLL_OUT      2
#define POLL_MSG      3
#define POLL_ERR      4
#define POLL_PRI      5
#define POLL_HUP      6
#define SYS_SECCOMP       1
#define SYS_USER_DISPATCH 2

#define SI_USER    0 /* picking linux values as default */
#define SI_QUEUE   -1
#define SI_TIMER   -2
#define SI_MESGQ   -3
#define SI_ASYNCIO -4
#define SI_TKILL   -6
#define SI_ASYNCNL -60
#define SI_KERNEL  128
#define SI_NOINFO  32767

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SICODE_H_ */
