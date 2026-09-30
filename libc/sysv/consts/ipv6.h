#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_IPV6_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_IPV6_H_
COSMOPOLITAN_C_START_

extern const int IPV6_V6ONLY_;
extern const int IPV6_CHECKSUM_;
extern const int IPV6_JOIN_GROUP_;
extern const int IPV6_LEAVE_GROUP_;
extern const int IPV6_MULTICAST_HOPS_;
extern const int IPV6_MULTICAST_IF_;
extern const int IPV6_MULTICAST_LOOP_;
extern const int IPV6_UNICAST_HOPS_;
extern const int IPV6_RECVTCLASS_;
extern const int IPV6_TCLASS_;
extern const int IPV6_DONTFRAG_;
extern const int IPV6_HOPLIMIT_;
extern const int IPV6_HOPOPTS_;
extern const int IPV6_PKTINFO_;
extern const int IPV6_RECVRTHDR_;
extern const int IPV6_RTHDR_;

COSMOPOLITAN_C_END_

/* picking linux values as default */
#define IPV6_UNICAST_HOPS   16
#define IPV6_MULTICAST_IF   17
#define IPV6_MULTICAST_HOPS 18
#define IPV6_MULTICAST_LOOP 19
#define IPV6_JOIN_GROUP     20
#define IPV6_LEAVE_GROUP    21
#define IPV6_CHECKSUM       7
#define IPV6_V6ONLY         26
#define IPV6_PKTINFO        50
#define IPV6_HOPLIMIT       52
#define IPV6_HOPOPTS        54
#define IPV6_RECVRTHDR      56
#define IPV6_RTHDR          57
#define IPV6_RECVTCLASS     66
#define IPV6_TCLASS         67
/* polyfill: linux-specific extension */
#define IPV6_DONTFRAG 62

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_IPV6_H_ */
