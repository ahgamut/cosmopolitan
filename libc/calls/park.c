/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2023 Justine Alexandra Roberts Tunney                              │
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
#include "libc/calls/internal.h"
#include "libc/calls/struct/sigset.h"
#include "libc/intrin/atomic.h"
#include "libc/nt/synchronization.h"
#include "libc/thread/posixthread.internal.h"
#ifdef __x86_64__

// returns 0 on timeout or spurious wakeup
// raises EINTR if a signal delivery interrupted wait operation
// raises ECANCELED if this POSIX thread was canceled in masked mode
textwindows static int _park_thread(uint32_t msdelay, sigset_t waitmask,
                                    bool restartable) {
  if (__sigcheck(waitmask, restartable) == -1)
    return -1;
  int expect = 0;
  atomic_int futex = 0;
  struct PosixThread *pt = _pthread_self();
  pt->pt_blkmask = waitmask;
  atomic_store_explicit(&pt->pt_blocker, &futex, memory_order_release);
  bool32 ok = WaitOnAddress(&futex, &expect, sizeof(int), msdelay);
  atomic_store_explicit(&pt->pt_blocker, 0, memory_order_release);
  if (ok && __sigcheck(waitmask, restartable) == -1)
    return -1;
  return 0;
}

textwindows int _park_norestart(uint32_t msdelay, sigset_t waitmask) {
  return _park_thread(msdelay, waitmask, false);
}

textwindows int _park_restartable(uint32_t msdelay, sigset_t waitmask) {
  return _park_thread(msdelay, waitmask, true);
}

#endif /* __x86_64__ */
