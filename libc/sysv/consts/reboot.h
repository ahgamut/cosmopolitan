#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_REBOOT_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_REBOOT_H_
COSMOPOLITAN_C_START_

extern const unsigned RB_AUTOBOOT_;
extern const unsigned RB_POWER_OFF_;
extern const unsigned RB_POWERDOWN_;
extern const unsigned RB_POWEROFF_;
extern const unsigned RB_HALT_SYSTEM_;
extern const unsigned RB_HALT_;
extern const unsigned RB_SW_SUSPEND_;
extern const unsigned RB_KEXEC_;
extern const unsigned RB_ENABLE_CAD_;
extern const unsigned RB_DISABLE_CAD_;
extern const unsigned RB_NOSYNC_;

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define RB_AUTOBOOT    0x01234567
#define RB_POWER_OFF   0x4321fedc
#define RB_POWERDOWN   RB_POWER_OFF
#define RB_POWEROFF    RB_POWER_OFF
#define RB_HALT_SYSTEM 0xcdef0123
#define RB_HALT        RB_HALT_SYSTEM
#define RB_SW_SUSPEND  0xd000fce2
#define RB_KEXEC       0x45584543
#define RB_ENABLE_CAD  0x89abcdef
#define RB_DISABLE_CAD 0
#define RB_NOSYNC      0x20000000

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_REBOOT_H_ */
