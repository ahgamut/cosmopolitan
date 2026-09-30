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
#include "libc/sysv/consts/sched.h"

/**
 * Translates compile-time scheduling policy to host OS value.
 *
 * Unknown policies pass through unchanged, so we don't drop user
 * input; unknown values are best reported by the host OS itself.
 */
pureconst int __linux2schedpolicy(int policy) {
  int fork, base;
  fork = policy & SCHED_RESET_ON_FORK;
  base = policy & ~SCHED_RESET_ON_FORK;
  if (base == SCHED_OTHER)
    base = SCHED_OTHER_;
  else if (base == SCHED_FIFO)
    base = SCHED_FIFO_;
  else if (base == SCHED_RR)
    base = SCHED_RR_;
  else if (base == SCHED_BATCH)
    base = SCHED_BATCH_;
  else if (base == SCHED_IDLE)
    base = SCHED_IDLE_;
  else if (base == SCHED_DEADLINE)
    base = SCHED_DEADLINE_;
  return base | (fork ? SCHED_RESET_ON_FORK_ : 0);
}

/**
 * Translates host OS scheduling policy to compile-time value.
 */
pureconst int __schedpolicy2linux(int policy) {
  int fork, base;
  fork = policy & SCHED_RESET_ON_FORK_;
  base = policy & ~SCHED_RESET_ON_FORK_;
  if (base == SCHED_OTHER_)
    base = SCHED_OTHER;
  else if (base == SCHED_FIFO_)
    base = SCHED_FIFO;
  else if (base == SCHED_RR_)
    base = SCHED_RR;
  else if (base == SCHED_BATCH_)
    base = SCHED_BATCH;
  else if (base == SCHED_IDLE_)
    base = SCHED_IDLE;
  else if (base == SCHED_DEADLINE_)
    base = SCHED_DEADLINE;
  return base | (fork ? SCHED_RESET_ON_FORK : 0);
}
