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
#include "libc/sysv/consts/sicode.h"
#include "libc/sysv/consts/sig.h"

/**
 * Translates compile-time si_code to host OS value.
 *
 * This is for the queued/user si_code family only, e.g. SI_QUEUE,
 * which is what sigqueue() can legitimately pass to the host os.
 * The kernel generated codes can't be translated this way, since
 * their numeric ranges overlap between operating systems.
 */
const int32_t __linux2sicode(int32_t code) {
  if (IsLinux()) {
    return code;
  } else if (IsXnu()) {
    switch (code) {
      case SI_USER:
        return 0;
      case SI_QUEUE:
        return -2; /* xnu magic */
      case SI_TIMER:
        return -3; /* xnu magic */
      case SI_TKILL:
        return -1; /* xnu magic */
      default:
        return code;
    }
  } else if (IsNetbsd()) {
    switch (code) {
      case SI_USER:
        return 0x010001; /* netbsd magic */
      case SI_QUEUE:
        return 0x010002; /* netbsd magic */
      case SI_TIMER:
        return 0x010003; /* netbsd magic */
      case SI_MESGQ:
        return 0x010005; /* netbsd magic */
      case SI_TKILL:
        return 0x010007; /* netbsd magic */
      default:
        return code;
    }
  } else {
    switch (code) {
      case SI_USER:
        return 0x010001; /* bsd magic */
      case SI_QUEUE:
        return 0x010002; /* bsd magic */
      case SI_TIMER:
        return 0x010003; /* bsd magic */
      case SI_ASYNCIO:
        return 0x010004; /* bsd magic */
      case SI_MESGQ:
        return 0x010005; /* bsd magic */
      case SI_TKILL:
        return 0x010007; /* bsd magic */
      default:
        return code;
    }
  }
}

/**
 * Translates host OS si_code to compile-time value.
 *
 * The si_code numeric ranges overlap across operating systems, so
 * the signal number is needed to disambiguate the dense fpe and
 * ill ranges. Values that an operating system doesn't support are
 * passed through unchanged.
 */
__privileged const int32_t __sicode2linux(int sig, int32_t code) {
  if (IsLinux()) {
    return code;
  } else if (IsXnu()) {
    switch (code) {
      case 0:
        return SI_USER;
      case -1:
        return SI_TKILL; /* xnu magic */
      case -2:
        return SI_QUEUE; /* xnu magic */
      case -3:
        return SI_TIMER; /* xnu magic */
      default:
        return code;
    }
  } else if (IsNetbsd()) {
    switch (code) {
      case 0:
        return SI_USER;
      case 0x010001: /* netbsd magic */
        return SI_USER;
      case 0x010002: /* netbsd magic */
        return SI_QUEUE;
      case 0x010003: /* netbsd magic */
        return SI_TIMER;
      case 0x010005: /* netbsd magic */
        return SI_MESGQ;
      case 0x010006: /* netbsd magic */
        return SI_KERNEL;
      case 0x010007: /* netbsd magic */
        return SI_TKILL;
      case 2: /* netbsd magic */
        if (sig == SIGFPE)
          return FPE_INTDIV;
        return code;
      case 1: /* netbsd magic */
        if (sig == SIGFPE)
          return FPE_INTOVF;
        return code;
      default:
        return code;
    }
  } else {
    switch (code) {
      case 0:
        return SI_USER;
      case 0x010001: /* bsd magic */
        return SI_USER;
      case 0x010002: /* bsd magic */
        return SI_QUEUE;
      case 0x010003: /* bsd magic */
        return SI_TIMER;
      case 0x010004: /* bsd magic */
        return SI_ASYNCIO;
      case 0x010005: /* bsd magic */
        return SI_MESGQ;
      case 0x010007: /* bsd magic */
        return SI_TKILL;
      case 1: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTDIV;
        if (sig == SIGILL)
          return ILL_ILLOPC;
        return code;
      case 2: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTOVF;
        if (sig == SIGILL)
          return ILL_ILLTRP;
        return code;
      case 3: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTUND;
        if (sig == SIGILL)
          return ILL_PRVOPC;
        return code;
      case 4: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTRES;
        if (sig == SIGILL)
          return ILL_ILLOPN;
        return code;
      case 5: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTINV;
        if (sig == SIGILL)
          return ILL_ILLADR;
        return code;
      case 6: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_FLTSUB;
        return code;
      case 7: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_INTDIV;
        return code;
      case 8: /* bsd magic */
        if (sig == SIGFPE)
          return FPE_INTOVF;
        return code;
      default:
        return code;
    }
  }
}
