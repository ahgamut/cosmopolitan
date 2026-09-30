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
#include "libc/sysv/consts/st.h"

#define ST2(X, A)    \
  if (flags & A)     \
    r |= X;

/**
 * Translates host OS statfs mount flags to compile-time value.
 *
 * The bits are tested using the actual values, since the kernel
 * fills f_flags with host mount flags; bits that aren't part of
 * the cosmo abi are dropped, e.g. the bsd local and quota bits.
 */
const int __statfs2linux(int flags) {
  int r = 0;
  ST2(ST_RDONLY, ST_RDONLY_);
  ST2(ST_NOSUID, ST_NOSUID_);
  ST2(ST_NODEV, ST_NODEV_);
  ST2(ST_NOEXEC, ST_NOEXEC_);
  ST2(ST_SYNCHRONOUS, ST_SYNCHRONOUS_);
  ST2(ST_MANDLOCK, ST_MANDLOCK_);
  ST2(ST_WRITE, ST_WRITE_);
  ST2(ST_APPEND, ST_APPEND_);
  ST2(ST_IMMUTABLE, ST_IMMUTABLE_);
  ST2(ST_NOATIME, ST_NOATIME_);
  ST2(ST_NODIRATIME, ST_NODIRATIME_);
  ST2(ST_RELATIME, ST_RELATIME_);
  return r;
}
