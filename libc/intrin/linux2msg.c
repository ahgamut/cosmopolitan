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
#include "libc/sysv/consts/msg.h"

#define ACTUAL2DEF(X) \
  if (actual & X##_)  \
    flags |= X;

#define DEF2ACTUAL(X) \
  if (flags & X)      \
    actual |= X##_;

/**
 * Translates compile-time message flags to host OS value.
 *
 * Bits we don't catalogue pass through unchanged, so we don't drop
 * user input; unknown values are best reported by the host OS itself.
 */
pureconst int __linux2msg(const int flags) {
  int actual;
  actual = flags &
           ~(MSG_DONTWAIT | MSG_WAITALL | MSG_NOSIGNAL | MSG_TRUNC |
             MSG_CTRUNC | MSG_FASTOPEN);
  DEF2ACTUAL(MSG_DONTWAIT);
  DEF2ACTUAL(MSG_WAITALL);
  DEF2ACTUAL(MSG_NOSIGNAL);
  DEF2ACTUAL(MSG_TRUNC);
  DEF2ACTUAL(MSG_CTRUNC);
  DEF2ACTUAL(MSG_FASTOPEN);
  return actual;
}

/**
 * Translates host OS message flags to compile-time value.
 *
 * Bits we don't catalogue pass through unchanged, so we don't drop
 * kernel output.
 */
pureconst int __msg2linux(const int actual) {
  int flags;
  flags = actual & ~(MSG_DONTWAIT_ | MSG_WAITALL_ | MSG_NOSIGNAL_ |
                     MSG_TRUNC_ | MSG_CTRUNC_ | MSG_FASTOPEN_);
  ACTUAL2DEF(MSG_DONTWAIT);
  ACTUAL2DEF(MSG_WAITALL);
  ACTUAL2DEF(MSG_NOSIGNAL);
  ACTUAL2DEF(MSG_TRUNC);
  ACTUAL2DEF(MSG_CTRUNC);
  ACTUAL2DEF(MSG_FASTOPEN);
  return flags;
}
