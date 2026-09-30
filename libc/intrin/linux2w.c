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
#include "libc/dce.h"
#include "libc/sysv/consts/waitid.h"
#include "libc/sysv/consts/w.h"

#define W2(X, A)   \
  if (flags & X)   \
    r |= A;

#define W2EXIT(X, A) \
  if (flags & A)     \
    r |= X;

/**
 * Translates compile-time wait options to host OS value.
 *
 * WNOHANG and WUNTRACED are consensus, so only WCONTINUED needs a
 * translation; unknown bits pass through unchanged.
 */
pureconst int __linux2wflags(int flags) {
  int r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    W2(WCONTINUED, WCONTINUED_);
    return r;
  }
}

/**
 * Translates host OS wait options to compile-time value.
 */
pureconst int __wflags2linux(int flags) {
  int r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    W2EXIT(WCONTINUED, WCONTINUED_);
    return r;
  }
}
