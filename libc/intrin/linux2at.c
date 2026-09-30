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
#include "libc/sysv/consts/at.h"

/**
 * Translates compile-time at() dirfd to host OS value.
 *
 * Real file descriptors pass through unchanged, since the at
 * functions accept actual fds in addition to AT_FDCWD.
 */
pureconst int __linux2atfd(int fd) {
  if (fd == AT_FDCWD)
    return AT_FDCWD_;
  return fd;
}

#define AT2(X, A)  \
  if (flags & X)   \
    r |= A;

#define ATEXIT2(X, A) \
  if (flags & A)      \
    r |= X;

/**
 * Translates compile-time at() flags to host OS value.
 *
 * The bits are translated individually, since cosmo at flags may
 * contain several of them at once. Bits that aren't part of the
 * cosmo abi pass through unchanged.
 */
pureconst int __linux2atflags(int flags) {
  int r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    AT2(AT_SYMLINK_NOFOLLOW, AT_SYMLINK_NOFOLLOW_);
    AT2(AT_SYMLINK_FOLLOW, AT_SYMLINK_FOLLOW_);
    AT2(AT_REMOVEDIR, AT_REMOVEDIR_);
    AT2(AT_EACCESS, AT_EACCESS_);
    return r;
  }
}

/**
 * Translates host OS at() flags to compile-time value.
 */
pureconst int __atflag2linux(int flags) {
  int r = 0;
  if (IsLinux()) {
    return flags;
  } else {
    ATEXIT2(AT_SYMLINK_NOFOLLOW, AT_SYMLINK_NOFOLLOW_);
    ATEXIT2(AT_SYMLINK_FOLLOW, AT_SYMLINK_FOLLOW_);
    ATEXIT2(AT_REMOVEDIR, AT_REMOVEDIR_);
    ATEXIT2(AT_EACCESS, AT_EACCESS_);
    return r;
  }
}
