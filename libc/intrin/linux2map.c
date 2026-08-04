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
#include "libc/sysv/consts/map.h"

#define ACTUAL2DEF(X)          \
  if ((actual & X##_) == X##_) \
    flags |= X;

#define DEF2ACTUAL(X)   \
  if ((flags & X) == X) \
    actual |= X##_;

pureconst int __linux2map(const int flags) {
  int actual = 0;
  DEF2ACTUAL(MAP_FILE);
  DEF2ACTUAL(MAP_SHARED);
  DEF2ACTUAL(MAP_PRIVATE);
  DEF2ACTUAL(MAP_SHARED_VALIDATE);
  DEF2ACTUAL(MAP_TYPE);
  DEF2ACTUAL(MAP_FIXED);
  DEF2ACTUAL(MAP_ANONYMOUS);
  DEF2ACTUAL(MAP_32BIT);
  DEF2ACTUAL(MAP_CONCEAL);
  DEF2ACTUAL(MAP_HASSEMAPHORE);
  DEF2ACTUAL(MAP_NOSYNC);
  DEF2ACTUAL(MAP_JIT);
  DEF2ACTUAL(MAP_DENYWRITE);
  DEF2ACTUAL(MAP_EXECUTABLE);
  DEF2ACTUAL(MAP_LOCKED);
  DEF2ACTUAL(MAP_NORESERVE);
  DEF2ACTUAL(MAP_POPULATE);
  DEF2ACTUAL(MAP_NONBLOCK);
  DEF2ACTUAL(MAP_INHERIT);
  DEF2ACTUAL(MAP_HUGETLB);
  DEF2ACTUAL(MAP_SYNC);
  DEF2ACTUAL(MAP_FIXED_NOREPLACE);
  DEF2ACTUAL(MAP_NOCACHE);
  DEF2ACTUAL(MAP_NOEXTEND);
  /* todo: this can be a for loop? */
  return actual;
}

pureconst int __map2linux(const int actual) {
  int flags = 0;
  ACTUAL2DEF(MAP_FILE);
  ACTUAL2DEF(MAP_SHARED);
  ACTUAL2DEF(MAP_PRIVATE);
  ACTUAL2DEF(MAP_SHARED_VALIDATE);
  ACTUAL2DEF(MAP_TYPE);
  ACTUAL2DEF(MAP_FIXED);
  ACTUAL2DEF(MAP_ANONYMOUS);
  ACTUAL2DEF(MAP_32BIT);
  ACTUAL2DEF(MAP_CONCEAL);
  ACTUAL2DEF(MAP_HASSEMAPHORE);
  ACTUAL2DEF(MAP_NOSYNC);
  ACTUAL2DEF(MAP_JIT);
  ACTUAL2DEF(MAP_DENYWRITE);
  ACTUAL2DEF(MAP_EXECUTABLE);
  ACTUAL2DEF(MAP_LOCKED);
  ACTUAL2DEF(MAP_NORESERVE);
  ACTUAL2DEF(MAP_POPULATE);
  ACTUAL2DEF(MAP_NONBLOCK);
  ACTUAL2DEF(MAP_INHERIT);
  ACTUAL2DEF(MAP_HUGETLB);
  ACTUAL2DEF(MAP_SYNC);
  ACTUAL2DEF(MAP_FIXED_NOREPLACE);
  ACTUAL2DEF(MAP_NOCACHE);
  ACTUAL2DEF(MAP_NOEXTEND);
  /* todo: this can be a for loop? */
  return flags;
}
