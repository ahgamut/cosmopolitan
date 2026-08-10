#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_AF_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_AF_H_
COSMOPOLITAN_C_START_

extern const int AF_ALG_;
extern const int AF_APPLETALK_;
extern const int AF_ASH_;
extern const int AF_ATMPVC_;
extern const int AF_ATMSVC_;
extern const int AF_AX25_;
extern const int AF_BLUETOOTH_;
extern const int AF_BRIDGE_;
extern const int AF_CAIF_;
extern const int AF_CAN_;
extern const int AF_ECONET_;
extern const int AF_FILE_;
extern const int AF_IB_;
extern const int AF_IEEE802154_;
extern const int AF_INET6_;
extern const int AF_INET_;
extern const int AF_IPX_;
extern const int AF_IRDA_;
extern const int AF_ISDN_;
extern const int AF_IUCV_;
extern const int AF_KCM_;
extern const int AF_KEY_;
extern const int AF_LINK_;
extern const int AF_LLC_;
extern const int AF_LOCAL_;
extern const int AF_MAX_;
extern const int AF_MPLS_;
extern const int AF_NETBEUI_;
extern const int AF_NETLINK_;
extern const int AF_NETROM_;
extern const int AF_NFC_;
extern const int AF_PACKET_;
extern const int AF_PHONET_;
extern const int AF_PPPOX_;
extern const int AF_RDS_;
extern const int AF_ROSE_;
extern const int AF_ROUTE_;
extern const int AF_RXRPC_;
extern const int AF_SECURITY_;
extern const int AF_SNA_;
extern const int AF_TIPC_;
extern const int AF_UNIX_;
extern const int AF_UNSPEC_;
extern const int AF_VSOCK_;
extern const int AF_WANPIPE_;
extern const int AF_X25_;

/* everyone agrees on these values internally */
#define AF_UNSPEC     0
#define AF_UNIX       1
#define AF_LOCAL      1
#define AF_INET       2

/* picking linux values as default, polyfilling otherwise */
#define AF_FILE       1
#define AF_AX25       3
#define AF_IPX        4
#define AF_APPLETALK  5
#define AF_NETROM     6
#define AF_BRIDGE     7
#define AF_ATMPVC     8
#define AF_X25        9
#define AF_INET6      10
#define AF_ROSE       11
#define AF_LINK       12 /* polyfill */
#define AF_NETBEUI    13
#define AF_SECURITY   14
#define AF_KEY        15
#define AF_NETLINK    16
#define AF_ROUTE      16
#define AF_PACKET     17
#define AF_ASH        18
#define AF_ECONET     19
#define AF_ATMSVC     20
#define AF_RDS        21
#define AF_SNA        22
#define AF_IRDA       23
#define AF_PPPOX      24
#define AF_WANPIPE    25
#define AF_LLC        26
#define AF_IB         27
#define AF_MPLS       28
#define AF_CAN        29
#define AF_TIPC       30
#define AF_BLUETOOTH  31
#define AF_IUCV       32
#define AF_RXRPC      33
#define AF_ISDN       34
#define AF_PHONET     35
#define AF_IEEE802154 36
#define AF_CAIF       37
#define AF_ALG        38
#define AF_NFC        39
#define AF_VSOCK      40
#define AF_KCM        41
#define AF_MAX        42

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_AF_H_ */
