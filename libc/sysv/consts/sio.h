#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_SIO_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_SIO_H_
COSMOPOLITAN_C_START_

extern const unsigned long SIOCADDDLCI_;
extern const unsigned long SIOCADDMULTI_;
extern const unsigned long SIOCADDRT_;
extern const unsigned long SIOCDARP_;
extern const unsigned long SIOCDELDLCI_;
extern const unsigned long SIOCDELMULTI_;
extern const unsigned long SIOCDELRT_;
extern const unsigned long SIOCDEVPRIVATE_;
extern const unsigned long SIOCDIFADDR_;
extern const unsigned long SIOCDRARP_;
extern const unsigned long SIOCGARP_;
extern const unsigned long SIOCGIFADDR_;
extern const unsigned long SIOCGIFBR_;
extern const unsigned long SIOCGIFBRDADDR_;
extern const unsigned long SIOCGIFCONF_;
extern const unsigned long SIOCGIFCOUNT_;
extern const unsigned long SIOCGIFDSTADDR_;
extern const unsigned long SIOCGIFENCAP_;
extern const unsigned long SIOCGIFFLAGS_;
extern const unsigned long SIOCGIFHWADDR_;
extern const unsigned long SIOCGIFINDEX_;
extern const unsigned long SIOCGIFMAP_;
extern const unsigned long SIOCGIFMEM_;
extern const unsigned long SIOCGIFMETRIC_;
extern const unsigned long SIOCGIFMTU_;
extern const unsigned long SIOCGIFNAME_;
extern const unsigned long SIOCGIFNETMASK_;
extern const unsigned long SIOCGIFPFLAGS_;
extern const unsigned long SIOCGIFSLAVE_;
extern const unsigned long SIOCGIFTXQLEN_;
extern const unsigned long SIOCGPGRP_;
extern const unsigned long SIOCGRARP_;
extern const unsigned long SIOCGSTAMP_;
extern const unsigned long SIOCGSTAMPNS_;
extern const unsigned long SIOCPROTOPRIVATE_;
extern const unsigned long SIOCRTMSG_;
extern const unsigned long SIOCSARP_;
extern const unsigned long SIOCSIFADDR_;
extern const unsigned long SIOCSIFBR_;
extern const unsigned long SIOCSIFBRDADDR_;
extern const unsigned long SIOCSIFDSTADDR_;
extern const unsigned long SIOCSIFENCAP_;
extern const unsigned long SIOCSIFFLAGS_;
extern const unsigned long SIOCSIFHWADDR_;
extern const unsigned long SIOCSIFHWBROADCAST_;
extern const unsigned long SIOCSIFLINK_;
extern const unsigned long SIOCSIFMAP_;
extern const unsigned long SIOCSIFMEM_;
extern const unsigned long SIOCSIFMETRIC_;
extern const unsigned long SIOCSIFMTU_;
extern const unsigned long SIOCSIFNAME_;
extern const unsigned long SIOCSIFNETMASK_;
extern const unsigned long SIOCSIFPFLAGS_;
extern const unsigned long SIOCSIFSLAVE_;
extern const unsigned long SIOCSIFTXQLEN_;
extern const unsigned long SIOCSPGRP_;
extern const unsigned long SIOCSRARP_;
extern const unsigned long SIOGIFINDEX_;

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define SIOCADDDLCI 0x8980
#define SIOCADDMULTI 0x8931
#define SIOCADDRT 0x890b
#define SIOCDARP 0x8953
#define SIOCDELDLCI 0x8981
#define SIOCDELMULTI 0x8932
#define SIOCDELRT 0x890c
#define SIOCDEVPRIVATE 0x89f0
#define SIOCDIFADDR 0x8936
#define SIOCDRARP 0x8960
#define SIOCGARP 0x8954
#define SIOCGIFADDR 0x8915
#define SIOCGIFBR 0x8940
#define SIOCGIFBRDADDR 0x8919
#define SIOCGIFCONF 0x8912
#define SIOCGIFCOUNT 0x8938
#define SIOCGIFDSTADDR 0x8917
#define SIOCGIFENCAP 0x8925
#define SIOCGIFFLAGS 0x8913
#define SIOCGIFHWADDR 0x8927
#define SIOCGIFINDEX 0x8933
#define SIOCGIFMAP 0x8970
#define SIOCGIFMEM 0x891f
#define SIOCGIFMETRIC 0x891d
#define SIOCGIFMTU 0x8921
#define SIOCGIFNAME 0x8910
#define SIOCGIFNETMASK 0x891b
#define SIOCGIFPFLAGS 0x8935
#define SIOCGIFSLAVE 0x8929
#define SIOCGIFTXQLEN 0x8942
#define SIOCGPGRP 0x8904
#define SIOCGRARP 0x8961
#define SIOCGSTAMP 0x8906
#define SIOCGSTAMPNS 0x8907
#define SIOCPROTOPRIVATE 0x89e0
#define SIOCRTMSG 0x890d
#define SIOCSARP 0x8955
#define SIOCSIFADDR 0x8916
#define SIOCSIFBR 0x8941
#define SIOCSIFBRDADDR 0x891a
#define SIOCSIFDSTADDR 0x8918
#define SIOCSIFENCAP 0x8926
#define SIOCSIFFLAGS 0x8914
#define SIOCSIFHWADDR 0x8924
#define SIOCSIFHWBROADCAST 0x8937
#define SIOCSIFLINK 0x8911
#define SIOCSIFMAP 0x8971
#define SIOCSIFMEM 0x8920
#define SIOCSIFMETRIC 0x891e
#define SIOCSIFMTU 0x8922
#define SIOCSIFNAME 0x8923
#define SIOCSIFNETMASK 0x891c
#define SIOCSIFPFLAGS 0x8934
#define SIOCSIFSLAVE 0x8930
#define SIOCSIFTXQLEN 0x8943
#define SIOCSPGRP 0x8902
#define SIOCSRARP 0x8962

#define SIOGIFINDEX SIOCGIFINDEX

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_SIO_H_ */
