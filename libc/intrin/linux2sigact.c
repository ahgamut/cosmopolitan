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
#include "libc/sysv/consts/sa.h"

#define SA2(X, A) \
  if (flags & X)  \
    r |= A;

/**
 * Translates compile-time sigaction flags to host OS value.
 *
 * The bits are translated individually, since cosmo sa_flags may
 * contain several of them at once. Bits that aren't part of the
 * cosmo abi are dropped, e.g. the SA_RESTORER bit only matters on
 * linux where its encoding is the same.
 */
const uint32_t __linux2saflags(uint32_t flags) {
  uint32_t r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    SA2(SA_NOCLDSTOP, SA_NOCLDSTOP_);
    SA2(SA_NOCLDWAIT, SA_NOCLDWAIT_);
    SA2(SA_SIGINFO, SA_SIGINFO_);
    SA2(SA_ONSTACK, SA_ONSTACK_);
    SA2(SA_RESTART, SA_RESTART_);
    SA2(SA_NODEFER, SA_NODEFER_);
    SA2(SA_RESETHAND, SA_RESETHAND_);
    return r;
  }
}

/**
 * Translates host OS sigaction flags to compile-time value.
 */
const uint32_t __saflag2linux(uint32_t flags) {
  uint32_t r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    SA2(SA_NOCLDSTOP_, SA_NOCLDSTOP);
    SA2(SA_NOCLDWAIT_, SA_NOCLDWAIT);
    SA2(SA_SIGINFO_, SA_SIGINFO);
    SA2(SA_ONSTACK_, SA_ONSTACK);
    SA2(SA_RESTART_, SA_RESTART);
    SA2(SA_NODEFER_, SA_NODEFER);
    SA2(SA_RESETHAND_, SA_RESETHAND);
    return r;
  }
}
