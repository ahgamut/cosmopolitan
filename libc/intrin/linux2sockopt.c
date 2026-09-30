/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2026 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/sysv/consts/ip.h"
#include "libc/sysv/consts/ipv6.h"
#include "libc/sysv/consts/sol.h"
#include "libc/sysv/consts/so.h"
#include "libc/sysv/consts/tcp.h"

#define ACTUAL2DEF(X) \
  if (actual == X##_) \
    return X;

#define DEF2ACTUAL(X) \
  if (optname == X)   \
    return X##_;

/**
 * Translates compile-time socket option level to host OS value.
 *
 * Levels other than SOL_SOCKET are consensus, so they're passed as-is.
 * Unknown levels pass through unchanged, so we don't drop user input.
 */
pureconst int __linux2socklevel(const int level) {
  if (level == SOL_SOCKET)
    return SOL_SOCKET_;
  return level;
}

/**
 * Translates compile-time socket option name to host OS value.
 *
 * Unknown option names pass through unchanged, so we don't drop user
 * input; unknown values are best reported by the host OS itself.
 */
pureconst int __linux2sockopt(const int level, const int optname) {
  if (level == SOL_SOCKET) {
    DEF2ACTUAL(SO_USELOOPBACK);
    DEF2ACTUAL(SO_REUSEADDR);
    DEF2ACTUAL(SO_KEEPALIVE);
    DEF2ACTUAL(SO_DONTROUTE);
    DEF2ACTUAL(SO_BROADCAST);
    DEF2ACTUAL(SO_REUSEPORT);
    DEF2ACTUAL(SO_OOBINLINE);
    DEF2ACTUAL(SO_SNDBUF);
    DEF2ACTUAL(SO_RCVBUF);
    DEF2ACTUAL(SO_SNDLOWAT);
    DEF2ACTUAL(SO_RCVLOWAT);
    DEF2ACTUAL(SO_SNDTIMEO);
    DEF2ACTUAL(SO_RCVTIMEO);
    DEF2ACTUAL(SO_ERROR);
    DEF2ACTUAL(SO_TYPE);
    DEF2ACTUAL(SO_ACCEPTCONN);
    DEF2ACTUAL(SO_LINGER);
  } else if (level == SOL_IP) {
    DEF2ACTUAL(IP_TOS);
    DEF2ACTUAL(IP_TTL);
    DEF2ACTUAL(IP_HDRINCL);
    DEF2ACTUAL(IP_OPTIONS);
    DEF2ACTUAL(IP_PKTINFO);
    DEF2ACTUAL(IP_RECVTTL);
    DEF2ACTUAL(IP_RECVTOS);
    DEF2ACTUAL(IP_MTU);
    DEF2ACTUAL(IP_MULTICAST_IF);
    DEF2ACTUAL(IP_MULTICAST_TTL);
    DEF2ACTUAL(IP_MULTICAST_LOOP);
    DEF2ACTUAL(IP_ADD_MEMBERSHIP);
    DEF2ACTUAL(IP_DROP_MEMBERSHIP);
  } else if (level == SOL_TCP) {
    DEF2ACTUAL(TCP_MAXSEG);
    DEF2ACTUAL(TCP_CORK);
    DEF2ACTUAL(TCP_KEEPIDLE);
    DEF2ACTUAL(TCP_KEEPINTVL);
    DEF2ACTUAL(TCP_KEEPCNT);
    DEF2ACTUAL(TCP_SYNCNT);
    DEF2ACTUAL(TCP_LINGER2);
    DEF2ACTUAL(TCP_DEFER_ACCEPT);
    DEF2ACTUAL(TCP_WINDOW_CLAMP);
    DEF2ACTUAL(TCP_INFO);
    DEF2ACTUAL(TCP_QUICKACK);
    DEF2ACTUAL(TCP_CONGESTION);
    DEF2ACTUAL(TCP_MD5SIG);
    DEF2ACTUAL(TCP_COOKIE_TRANSACTIONS);
    DEF2ACTUAL(TCP_THIN_LINEAR_TIMEOUTS);
    DEF2ACTUAL(TCP_THIN_DUPACK);
    DEF2ACTUAL(TCP_USER_TIMEOUT);
    DEF2ACTUAL(TCP_REPAIR);
    DEF2ACTUAL(TCP_REPAIR_QUEUE);
    DEF2ACTUAL(TCP_QUEUE_SEQ);
    DEF2ACTUAL(TCP_REPAIR_OPTIONS);
    DEF2ACTUAL(TCP_FASTOPEN);
    DEF2ACTUAL(TCP_TIMESTAMP);
    DEF2ACTUAL(TCP_NOTSENT_LOWAT);
    DEF2ACTUAL(TCP_CC_INFO);
    DEF2ACTUAL(TCP_SAVE_SYN);
    DEF2ACTUAL(TCP_SAVED_SYN);
    DEF2ACTUAL(TCP_FASTOPEN_CONNECT);
    DEF2ACTUAL(TCP_ULP);
    DEF2ACTUAL(TCP_MD5SIG_MAXKEYLEN);
  } else if (level == SOL_IPV6) {
    DEF2ACTUAL(IPV6_JOIN_GROUP);
    DEF2ACTUAL(IPV6_LEAVE_GROUP);
    DEF2ACTUAL(IPV6_MULTICAST_HOPS);
    DEF2ACTUAL(IPV6_MULTICAST_IF);
    DEF2ACTUAL(IPV6_MULTICAST_LOOP);
    DEF2ACTUAL(IPV6_UNICAST_HOPS);
    DEF2ACTUAL(IPV6_CHECKSUM);
    DEF2ACTUAL(IPV6_V6ONLY);
    DEF2ACTUAL(IPV6_PKTINFO);
    DEF2ACTUAL(IPV6_HOPOPTS);
    DEF2ACTUAL(IPV6_RECVRTHDR);
    DEF2ACTUAL(IPV6_RTHDR);
    DEF2ACTUAL(IPV6_RECVTCLASS);
    DEF2ACTUAL(IPV6_TCLASS);
    DEF2ACTUAL(IPV6_DONTFRAG);
    DEF2ACTUAL(IPV6_HOPLIMIT);
  }
  return optname;
}

/**
 * Translates host OS socket option name to compile-time value.
 *
 * The level argument must be in host OS encoding. Unknown values pass
 * through unchanged, so we don't drop kernel output.
 */
pureconst int __sockopt2linux(const int level, const int actual) {
  if (level == SOL_SOCKET_) {
    ACTUAL2DEF(SO_USELOOPBACK);
    ACTUAL2DEF(SO_REUSEADDR);
    ACTUAL2DEF(SO_KEEPALIVE);
    ACTUAL2DEF(SO_DONTROUTE);
    ACTUAL2DEF(SO_BROADCAST);
    ACTUAL2DEF(SO_REUSEPORT);
    ACTUAL2DEF(SO_OOBINLINE);
    ACTUAL2DEF(SO_SNDBUF);
    ACTUAL2DEF(SO_RCVBUF);
    ACTUAL2DEF(SO_SNDLOWAT);
    ACTUAL2DEF(SO_RCVLOWAT);
    ACTUAL2DEF(SO_SNDTIMEO);
    ACTUAL2DEF(SO_RCVTIMEO);
    ACTUAL2DEF(SO_ERROR);
    ACTUAL2DEF(SO_TYPE);
    ACTUAL2DEF(SO_ACCEPTCONN);
    ACTUAL2DEF(SO_LINGER);
  } else if (level == SOL_IP) {
    ACTUAL2DEF(IP_TOS);
    ACTUAL2DEF(IP_TTL);
    ACTUAL2DEF(IP_HDRINCL);
    ACTUAL2DEF(IP_OPTIONS);
    ACTUAL2DEF(IP_PKTINFO);
    ACTUAL2DEF(IP_RECVTTL);
    ACTUAL2DEF(IP_RECVTOS);
    ACTUAL2DEF(IP_MTU);
    ACTUAL2DEF(IP_MULTICAST_IF);
    ACTUAL2DEF(IP_MULTICAST_TTL);
    ACTUAL2DEF(IP_MULTICAST_LOOP);
    ACTUAL2DEF(IP_ADD_MEMBERSHIP);
    ACTUAL2DEF(IP_DROP_MEMBERSHIP);
  } else if (level == SOL_TCP) {
    ACTUAL2DEF(TCP_MAXSEG);
    ACTUAL2DEF(TCP_CORK);
    ACTUAL2DEF(TCP_KEEPIDLE);
    ACTUAL2DEF(TCP_KEEPINTVL);
    ACTUAL2DEF(TCP_KEEPCNT);
    ACTUAL2DEF(TCP_SYNCNT);
    ACTUAL2DEF(TCP_LINGER2);
    ACTUAL2DEF(TCP_DEFER_ACCEPT);
    ACTUAL2DEF(TCP_WINDOW_CLAMP);
    ACTUAL2DEF(TCP_INFO);
    ACTUAL2DEF(TCP_QUICKACK);
    ACTUAL2DEF(TCP_CONGESTION);
    ACTUAL2DEF(TCP_MD5SIG);
    ACTUAL2DEF(TCP_COOKIE_TRANSACTIONS);
    ACTUAL2DEF(TCP_THIN_LINEAR_TIMEOUTS);
    ACTUAL2DEF(TCP_THIN_DUPACK);
    ACTUAL2DEF(TCP_USER_TIMEOUT);
    ACTUAL2DEF(TCP_REPAIR);
    ACTUAL2DEF(TCP_REPAIR_QUEUE);
    ACTUAL2DEF(TCP_QUEUE_SEQ);
    ACTUAL2DEF(TCP_REPAIR_OPTIONS);
    ACTUAL2DEF(TCP_FASTOPEN);
    ACTUAL2DEF(TCP_TIMESTAMP);
    ACTUAL2DEF(TCP_NOTSENT_LOWAT);
    ACTUAL2DEF(TCP_CC_INFO);
    ACTUAL2DEF(TCP_SAVE_SYN);
    ACTUAL2DEF(TCP_SAVED_SYN);
    ACTUAL2DEF(TCP_FASTOPEN_CONNECT);
    ACTUAL2DEF(TCP_ULP);
    ACTUAL2DEF(TCP_MD5SIG_MAXKEYLEN);
  } else if (level == SOL_IPV6) {
    ACTUAL2DEF(IPV6_JOIN_GROUP);
    ACTUAL2DEF(IPV6_LEAVE_GROUP);
    ACTUAL2DEF(IPV6_MULTICAST_HOPS);
    ACTUAL2DEF(IPV6_MULTICAST_IF);
    ACTUAL2DEF(IPV6_MULTICAST_LOOP);
    ACTUAL2DEF(IPV6_UNICAST_HOPS);
    ACTUAL2DEF(IPV6_CHECKSUM);
    ACTUAL2DEF(IPV6_V6ONLY);
    ACTUAL2DEF(IPV6_PKTINFO);
    ACTUAL2DEF(IPV6_HOPOPTS);
    ACTUAL2DEF(IPV6_RECVRTHDR);
    ACTUAL2DEF(IPV6_RTHDR);
    ACTUAL2DEF(IPV6_RECVTCLASS);
    ACTUAL2DEF(IPV6_TCLASS);
    ACTUAL2DEF(IPV6_DONTFRAG);
    ACTUAL2DEF(IPV6_HOPLIMIT);
  }
  return actual;
}
