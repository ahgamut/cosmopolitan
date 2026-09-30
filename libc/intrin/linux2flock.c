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
#include "libc/sysv/consts/f.h"

/**
 * Translates compile-time file locking fcntl() commands to host OS
 * value.
 *
 * Only the lock commands translate; the other F_ commands are
 * runtime externs of their own.
 */
pureconst int __linux2flockcmd(int cmd) {
  if (cmd == F_GETLK)
    return F_GETLK_;
  if (cmd == F_SETLK)
    return F_SETLK_;
  if (cmd == F_SETLKW)
    return F_SETLKW_;
  return cmd;
}

/**
 * Translates host OS file locking fcntl() commands to compile-time
 * value.
 */
pureconst int __flockcmd2linux(int cmd) {
  if (cmd == F_GETLK_)
    return F_GETLK;
  if (cmd == F_SETLK_)
    return F_SETLK;
  if (cmd == F_SETLKW_)
    return F_SETLKW;
  return cmd;
}

/**
 * Translates compile-time file lock types to host OS value.
 */
pureconst int16_t __linux2flocktype(int16_t type) {
  if (type == F_RDLCK)
    return F_RDLCK_;
  if (type == F_WRLCK)
    return F_WRLCK_;
  return type;
}

/**
 * Translates host OS file lock types to compile-time value.
 */
pureconst int16_t __flocktype2linux(int16_t type) {
  if (type == F_RDLCK_)
    return F_RDLCK;
  if (type == F_WRLCK_)
    return F_WRLCK;
  return type;
}
