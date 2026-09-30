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
#include "libc/sysv/consts/auxv.h"

/**
 * Translates compile-time getauxval() key to host OS value.
 *
 * __auxv holds the keys the host kernel provided verbatim. Keys
 * that linux doesn't define (e.g. AT_CANARY) are still runtime
 * externs, so they translate to themselves.
 */
pureconst unsigned long __linux2auxvkey(unsigned long key) {
  if (key == AT_EXECFN)
    return AT_EXECFN_;
  if (key == AT_EXECPATH)
    return AT_EXECPATH_;
  if (key == AT_SECURE)
    return AT_SECURE_;
  if (key == AT_RANDOM)
    return AT_RANDOM_;
  if (key == AT_HWCAP)
    return AT_HWCAP_;
  if (key == AT_HWCAP2)
    return AT_HWCAP2_;
  if (key == AT_UID)
    return AT_UID_;
  if (key == AT_EUID)
    return AT_EUID_;
  if (key == AT_GID)
    return AT_GID_;
  if (key == AT_EGID)
    return AT_EGID_;
  if (key == AT_BASE_PLATFORM)
    return AT_BASE_PLATFORM_;
  if (key == AT_CLKTCK)
    return AT_CLKTCK_;
  if (key == AT_DCACHEBSIZE)
    return AT_DCACHEBSIZE_;
  if (key == AT_EXECFD)
    return AT_EXECFD_;
  if (key == AT_ICACHEBSIZE)
    return AT_ICACHEBSIZE_;
  if (key == AT_MINSIGSTKSZ)
    return AT_MINSIGSTKSZ_;
  if (key == AT_NOTELF)
    return AT_NOTELF_;
  if (key == AT_NO_AUTOMOUNT)
    return AT_NO_AUTOMOUNT_;
  if (key == AT_PLATFORM)
    return AT_PLATFORM_;
  if (key == AT_SYSINFO_EHDR)
    return AT_SYSINFO_EHDR_;
  if (key == AT_UCACHEBSIZE)
    return AT_UCACHEBSIZE_;
  return key;
}
