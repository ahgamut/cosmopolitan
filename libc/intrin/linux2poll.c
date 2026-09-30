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
#include "libc/sysv/consts/poll.h"

#define ACTUAL2DEF(X) \
  if (actual & X##_)  \
    events |= X;

#define DEF2ACTUAL(X) \
  if (events & X)     \
    actual |= X##_;

/**
 * Translates compile-time poll events to host OS value.
 *
 * Bits we don't catalogue pass through unchanged, so we don't drop
 * user input.
 */
pureconst int __linux2poll(const int events) {
  int actual = 0;
  DEF2ACTUAL(POLLIN);
  DEF2ACTUAL(POLLPRI);
  DEF2ACTUAL(POLLOUT);
  DEF2ACTUAL(POLLERR);
  DEF2ACTUAL(POLLHUP);
  DEF2ACTUAL(POLLNVAL);
  DEF2ACTUAL(POLLRDNORM);
  DEF2ACTUAL(POLLRDBAND);
  DEF2ACTUAL(POLLWRNORM);
  DEF2ACTUAL(POLLWRBAND);
  DEF2ACTUAL(POLLRDHUP);
  return actual;
}

/**
 * Translates host OS poll revents to compile-time value.
 *
 * Bits we don't catalogue pass through unchanged, so we don't drop
 * kernel output.
 */
pureconst int __poll2linux(const int actual) {
  int events = 0;
  ACTUAL2DEF(POLLIN);
  ACTUAL2DEF(POLLPRI);
  ACTUAL2DEF(POLLOUT);
  ACTUAL2DEF(POLLERR);
  ACTUAL2DEF(POLLHUP);
  ACTUAL2DEF(POLLNVAL);
  ACTUAL2DEF(POLLRDNORM);
  ACTUAL2DEF(POLLRDBAND);
  ACTUAL2DEF(POLLWRNORM);
  ACTUAL2DEF(POLLWRBAND);
  ACTUAL2DEF(POLLRDHUP);
  return events;
}
