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
#include "libc/sysv/consts/sock.h"

/**
 * Translates compile-time socket type to host OS value.
 *
 * The type bits (SOCK_STREAM, etc.) are consensus across supported
 * operating systems; only the SOCK_CLOEXEC and SOCK_NONBLOCK bits
 * need translating. Unknown bits pass through unchanged, so we don't
 * drop user input.
 */
pureconst int __linux2sock(const int type) {
  int actual;
  actual = type & ~(SOCK_CLOEXEC | SOCK_NONBLOCK);
  if (type & SOCK_CLOEXEC)
    actual |= SOCK_CLOEXEC_;
  if (type & SOCK_NONBLOCK)
    actual |= SOCK_NONBLOCK_;
  return actual;
}

/**
 * Translates host OS socket type to compile-time value.
 *
 * Unknown bits pass through unchanged, so we don't drop kernel
 * output.
 */
pureconst int __sock2linux(const int actual) {
  int type;
  type = actual & ~(SOCK_CLOEXEC_ | SOCK_NONBLOCK_);
  if (actual & SOCK_CLOEXEC_)
    type |= SOCK_CLOEXEC;
  if (actual & SOCK_NONBLOCK_)
    type |= SOCK_NONBLOCK;
  return type;
}
