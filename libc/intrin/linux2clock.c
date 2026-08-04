/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2024 Justine Alexandra Roberts Tunney                              │
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
#include "libc/dce.h"
#include "libc/sysv/consts/clock.h"

#define ACTUAL2DEF(X) \
  if (actual == X##_) \
    return X;

#define DEF2ACTUAL(X) \
  if (clock == X)     \
    return X##_;

pureconst int __linux2clock(const int clock) {
  DEF2ACTUAL(CLOCK_REALTIME);
  DEF2ACTUAL(CLOCK_MONOTONIC);
  DEF2ACTUAL(CLOCK_PROCESS_CPUTIME_ID);
  DEF2ACTUAL(CLOCK_THREAD_CPUTIME_ID);
  DEF2ACTUAL(CLOCK_MONOTONIC_RAW);
  DEF2ACTUAL(CLOCK_REALTIME_COARSE);
  DEF2ACTUAL(CLOCK_MONOTONIC_COARSE);
  DEF2ACTUAL(CLOCK_BOOTTIME);
  return -1;
}

pureconst int __clock2linux(const int actual) {
  ACTUAL2DEF(CLOCK_REALTIME);
  ACTUAL2DEF(CLOCK_MONOTONIC);
  ACTUAL2DEF(CLOCK_PROCESS_CPUTIME_ID);
  ACTUAL2DEF(CLOCK_THREAD_CPUTIME_ID);
  ACTUAL2DEF(CLOCK_MONOTONIC_RAW);
  ACTUAL2DEF(CLOCK_REALTIME_COARSE);
  ACTUAL2DEF(CLOCK_MONOTONIC_COARSE);
  ACTUAL2DEF(CLOCK_BOOTTIME);
  return -1;
}
