#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_IP_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_IP_H_
COSMOPOLITAN_C_START_

extern const int IP_TOS_;
extern const int IP_TTL_;
extern const int IP_MTU_;
extern const int IP_HDRINCL_;
extern const int IP_OPTIONS_;
extern const int IP_RECVTTL_;
extern const int IP_ADD_MEMBERSHIP_;
extern const int IP_DROP_MEMBERSHIP_;
extern const int IP_MULTICAST_IF_;
extern const int IP_MULTICAST_LOOP_;
extern const int IP_MULTICAST_TTL_;
extern const int IP_PKTINFO_;
extern const int IP_RECVTOS_;

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define IP_TOS             1
#define IP_TTL             2
#define IP_HDRINCL         3
#define IP_OPTIONS         4
#define IP_PKTINFO         8
#define IP_RECVTTL         12
#define IP_RECVTOS         13
#define IP_MTU             14
#define IP_MULTICAST_IF    32
#define IP_MULTICAST_TTL   33
#define IP_MULTICAST_LOOP  34
#define IP_ADD_MEMBERSHIP  35
#define IP_DROP_MEMBERSHIP 36

#define IP_DEFAULT_MULTICAST_TTL  1
#define IP_DEFAULT_MULTICAST_LOOP 1

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_IP_H_ */
