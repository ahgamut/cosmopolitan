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
#include "libc/sysv/consts/mount.h"
#include "libc/sysv/consts/unmount.h"

#define MNT2(X, A)   \
  if (flags & A)     \
    r |= X;

/**
 * Translates compile-time mount flags to host OS value.
 *
 * Linux-only bits that have no host equivalent, e.g. MS_BIND and
 * MS_REC, are dropped since the host kernels reject them anyway.
 */
unsigned long __linux2mountflags(unsigned long flags) {
  unsigned long r = 0;
  MNT2(MS_RDONLY, MS_RDONLY_);
  MNT2(MS_NOSUID, MS_NOSUID_);
  MNT2(MS_NODEV, MS_NODEV_);
  MNT2(MS_NOEXEC, MS_NOEXEC_);
  MNT2(MS_SYNCHRONOUS, MS_SYNCHRONOUS_);
  MNT2(MS_REMOUNT, MS_REMOUNT_);
  MNT2(MS_MANDLOCK, MS_MANDLOCK_);
  MNT2(MS_DIRSYNC, MS_DIRSYNC_);
  MNT2(MS_NOATIME, MS_NOATIME_);
  MNT2(MS_NODIRATIME, MS_NODIRATIME_);
  MNT2(MS_RELATIME, MS_RELATIME_);
  MNT2(MS_BIND, MS_BIND_);
  MNT2(MS_MOVE, MS_MOVE_);
  MNT2(MS_REC, MS_REC_);
  MNT2(MS_SILENT, MS_SILENT_);
  MNT2(MS_POSIXACL, MS_POSIXACL_);
  MNT2(MS_UNBINDABLE, MS_UNBINDABLE_);
  MNT2(MS_PRIVATE, MS_PRIVATE_);
  MNT2(MS_SLAVE, MS_SLAVE_);
  MNT2(MS_SHARED, MS_SHARED_);
  MNT2(MS_KERNMOUNT, MS_KERNMOUNT_);
  MNT2(MS_I_VERSION, MS_I_VERSION_);
  MNT2(MS_STRICTATIME, MS_STRICTATIME_);
  MNT2(MS_LAZYTIME, MS_LAZYTIME_);
  MNT2(MS_ACTIVE, MS_ACTIVE_);
  MNT2(MS_NOUSER, MS_NOUSER_);
  MNT2(MS_MGC_VAL, MS_MGC_VAL_);
  return r;
}

/**
 * Translates compile-time unmount flags to host OS value.
 */
int __linux2unmountflags(int flags) {
  int r = 0;
  MNT2(MNT_FORCE, MNT_FORCE_);
  MNT2(MNT_DETACH, MNT_DETACH_);
  MNT2(MNT_EXPIRE, MNT_EXPIRE_);
  MNT2(UMOUNT_NOFOLLOW, UMOUNT_NOFOLLOW_);
  return r;
}
