/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
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
#include "libc/bits/bits.h"
#include "libc/bits/likely.h"
#include "libc/bits/popcnt.h"
#include "libc/bits/safemacros.internal.h"
#include "libc/calls/calls.h"
#include "libc/calls/math.h"
#include "libc/calls/sigbits.h"
#include "libc/calls/struct/dirent.h"
#include "libc/calls/struct/flock.h"
#include "libc/calls/struct/rusage.h"
#include "libc/calls/struct/sigaction.h"
#include "libc/calls/struct/stat.h"
#include "libc/dos.h"
#include "libc/errno.h"
#include "libc/fmt/conv.h"
#include "libc/fmt/itoa.h"
#include "libc/log/backtrace.internal.h"
#include "libc/log/check.h"
#include "libc/log/log.h"
#include "libc/macros.internal.h"
#include "libc/math.h"
#include "libc/mem/alloca.h"
#include "libc/mem/fmt.h"
#include "libc/mem/mem.h"
#include "libc/nexgen32e/bsf.h"
#include "libc/nexgen32e/bsr.h"
#include "libc/nexgen32e/crc32.h"
#include "libc/nt/enum/fileflagandattributes.h"
#include "libc/rand/rand.h"
#include "libc/runtime/clktck.h"
#include "libc/runtime/directmap.internal.h"
#include "libc/runtime/gc.internal.h"
#include "libc/runtime/runtime.h"
#include "libc/runtime/stack.h"
#include "libc/sock/goodsocket.internal.h"
#include "libc/sock/sock.h"
#include "libc/stdio/append.internal.h"
#include "libc/stdio/hex.internal.h"
#include "libc/stdio/stdio.h"
#include "libc/str/slice.h"
#include "libc/str/str.h"
#include "libc/str/undeflate.h"
#include "libc/sysv/consts/af.h"
#include "libc/sysv/consts/auxv.h"
#include "libc/sysv/consts/dt.h"
#include "libc/sysv/consts/ex.h"
#include "libc/sysv/consts/exit.h"
#include "libc/sysv/consts/f.h"
#include "libc/sysv/consts/grnd.h"
#include "libc/sysv/consts/inaddr.h"
#include "libc/sysv/consts/ipproto.h"
#include "libc/sysv/consts/lock.h"
#include "libc/sysv/consts/madv.h"
#include "libc/sysv/consts/map.h"
#include "libc/sysv/consts/msync.h"
#include "libc/sysv/consts/o.h"
#include "libc/sysv/consts/poll.h"
#include "libc/sysv/consts/prot.h"
#include "libc/sysv/consts/rusage.h"
#include "libc/sysv/consts/s.h"
#include "libc/sysv/consts/shut.h"
#include "libc/sysv/consts/sig.h"
#include "libc/sysv/consts/so.h"
#include "libc/sysv/consts/sock.h"
#include "libc/sysv/consts/sol.h"
#include "libc/sysv/consts/tcp.h"
#include "libc/sysv/consts/w.h"
#include "libc/time/time.h"
#include "libc/x/x.h"
#include "libc/zip.h"
#include "net/http/http.h"
#include "third_party/zlib/zlib.h"

#define HASH_LOAD_FACTOR /* 1. / */ 4
#define LockInc(P)       asm volatile("lock incq\t%0" : "=m"(*(P)))
#define AppendCrlf(P)    mempcpy(P, "\r\n", 2)

static const uint8_t kGzipHeader[] = {
    0x1F,        // MAGNUM
    0x8B,        // MAGNUM
    0x08,        // CM: DEFLATE
    0x00,        // FLG: NONE
    0x00,        // MTIME: NONE
    0x00,        //
    0x00,        //
    0x00,        //
    0x00,        // XFL
    kZipOsUnix,  // OS
};

struct Buffer {
  size_t n, c;
  char *p;
};

struct Strings {
  size_t n, c;
  struct String {
    size_t n;
    const char *s;
  } * p;
};

struct DeflateGenerator {
  int t;
  void *b;
  size_t i;
  uint32_t c;
  uint32_t z;
  z_stream s;
  struct Asset *a;
};

static struct Freelist {
  size_t n, c;
  void **p;
} freelist;

static struct Unmaplist {
  size_t n, c;
  struct Unmap {
    int f;
    void *p;
    size_t n;
  } * p;
} unmaplist;

static struct Assets {
  uint32_t n;
  struct Asset {
    bool istext;
    uint32_t hash;
    uint64_t cf;
    uint64_t lf;
    int64_t lastmodified;
    char *lastmodifiedstr;
    struct File {
      struct String path;
      struct stat st;
    } * file;
  } * p;
} assets;

static struct Shared {
  int workers;
  long double nowish;
  long double lastreindex;
  long double lastmeltdown;
  char currentdate[32];
  struct rusage server;
  struct rusage children;
  struct Counters {
#define C(x) long x;
#include "tool/net/counters.inc"
#undef C
  } c;
} shared;

static const char kCounterNames[] =
#define C(x) #x "\0"
#include "tool/net/counters.inc"
#undef C
    ;

typedef ssize_t (*reader_f)(int, void *, size_t);
typedef ssize_t (*writer_f)(int, struct iovec *, int);

static bool openzip_inited = false;
static bool killed;
static bool meltdown;
static long double startread;
static char slashpath[PATH_MAX];

static int zfd;
static int gmtoff;
static struct stat zst;
static size_t zsize;
static char *outbuf;
static char *content;
static uint8_t *zmap;
static uint8_t *zbase;
static uint8_t *zcdir;
static const char *zpath;
static struct Strings stagedirs;
static struct Strings hidepaths;

static char *MergePaths(const char *p, size_t n, const char *q, size_t m,
                        size_t *z) {
  char *r;
  if (n && p[n - 1] == '/') --n;
  if (m && q[0] == '/') ++q, --m;
  r = xmalloc(n + 1 + m + 1);
  mempcpy(mempcpy(mempcpy(mempcpy(r, p, n), "/", 1), q, m), "", 1);
  if (z) *z = n + 1 + m;
  return r;
}

static void *FreeLater(void *p) {
  if (p) {
    if (++freelist.n > freelist.c) {
      freelist.c = freelist.n + (freelist.n >> 1);
      freelist.p = xrealloc(freelist.p, freelist.c * sizeof(*freelist.p));
    }
    freelist.p[freelist.n - 1] = p;
  }
  return p;
}

forceinline bool IsCompressed(struct Asset *a) {
  return !a->file &&
         ZIP_LFILE_COMPRESSIONMETHOD(zbase + a->lf) == kZipCompressionDeflate;
}

forceinline int GetMode(struct Asset *a) {
  return a->file ? a->file->st.st_mode : GetZipCfileMode(zbase + a->cf);
}

static char *FormatUnixHttpDateTime(char *s, int64_t t) {
  struct tm tm;
  gmtime_r(&t, &tm);
  FormatHttpDateTime(s, &tm);
  return s;
}

forceinline bool IsCompressionMethodSupported(int method) {
  return method == kZipCompressionNone || method == kZipCompressionDeflate;
}

static inline unsigned Hash(const void *p, unsigned long n) {
  unsigned h, i;
  for (h = i = 0; i < n; i++) {
    h += ((unsigned char *)p)[i];
    h *= 0x9e3779b1;
  }
  return MAX(1, h);
}

static void *Deflate(const void *data, size_t size, size_t *out_size) {
  void *res;
  z_stream zs;
  LockInc(&shared.c.deflates);
  zs.zfree = 0;
  zs.zalloc = 0;
  CHECK_EQ(Z_OK, deflateInit2(&zs, 4, Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL,
                              Z_DEFAULT_STRATEGY));
  zs.next_in = data;
  zs.avail_in = size;
  zs.avail_out = compressBound(size);
  zs.next_out = res = xmalloc(zs.avail_out);
  CHECK_EQ(Z_STREAM_END, deflate(&zs, Z_FINISH));
  CHECK_EQ(Z_OK, deflateEnd(&zs));
  *out_size = zs.total_out;
  return xrealloc(res, zs.total_out);
}

static ssize_t WritevAll(int fd, struct iovec *iov, int iovlen) {
  int i;
  ssize_t rc;
  size_t wrote, total;
  i = 0;
  total = 0;
  do {
    if (i) {
      while (i < iovlen && !iov[i].iov_len) ++i;
      if (i == iovlen) break;
    }
    if ((rc = writev(fd, iov + i, iovlen - i)) != -1) {
      wrote = rc;
      total += wrote;
      do {
        if (wrote >= iov[i].iov_len) {
          wrote -= iov[i++].iov_len;
        } else {
          iov[i].iov_base = (char *)iov[i].iov_base + wrote;
          iov[i].iov_len -= wrote;
          wrote = 0;
        }
      } while (wrote);
    } else if (errno == EINTR) {
      LockInc(&shared.c.writeinterruputs);
      if (killed || (meltdown && nowl() - startread > 2)) {
        return total ? total : -1;
      }
    } else {
      return total ? total : -1;
    }
  } while (i < iovlen);
  return total;
}

static void IndexAssets(void) {
  uint64_t cf;
  struct Asset *p;
  struct timespec lm;
  uint32_t i, n, m, step, hash;
  DEBUGF("(zip) indexing assets (inode %#lx)", zst.st_ino);
  CHECK_GE(HASH_LOAD_FACTOR, 2);
  CHECK(READ32LE(zcdir) == kZipCdir64HdrMagic ||
        READ32LE(zcdir) == kZipCdirHdrMagic);
  n = GetZipCdirRecords(zcdir);
  m = roundup2pow(MAX(1, n) * HASH_LOAD_FACTOR);
  p = xcalloc(m, sizeof(struct Asset));
  for (cf = GetZipCdirOffset(zcdir); n--; cf += ZIP_CFILE_HDRSIZE(zbase + cf)) {
    CHECK_EQ(kZipCfileHdrMagic, ZIP_CFILE_MAGIC(zbase + cf));
    if (!IsCompressionMethodSupported(
            ZIP_CFILE_COMPRESSIONMETHOD(zbase + cf))) {
      WARNF("(zip) don't understand zip compression method %d used by %`'.*s",
            ZIP_CFILE_COMPRESSIONMETHOD(zbase + cf),
            ZIP_CFILE_NAMESIZE(zbase + cf), ZIP_CFILE_NAME(zbase + cf));
      continue;
    }
    hash = Hash(ZIP_CFILE_NAME(zbase + cf), ZIP_CFILE_NAMESIZE(zbase + cf));
    step = 0;
    do {
      i = (hash + (step * (step + 1)) >> 1) & (m - 1);
      ++step;
    } while (p[i].hash);
    GetZipCfileTimestamps(zbase + cf, &lm, 0, 0, gmtoff);
    p[i].hash = hash;
    p[i].cf = cf;
    p[i].lf = GetZipCfileOffset(zbase + cf);
    p[i].istext = !!(ZIP_CFILE_INTERNALATTRIBUTES(zbase + cf) & kZipIattrText);
    p[i].lastmodified = lm.tv_sec;
    p[i].lastmodifiedstr = FormatUnixHttpDateTime(xmalloc(30), lm.tv_sec);
  }
  assets.p = p;
  assets.n = m;
}

static bool OpenZip(bool force) {
  int fd;
  size_t n;
  struct stat st;
  uint8_t *m, *b, *d, *p;
  if (stat(zpath, &st) != -1) {
    if (force || st.st_ino != zst.st_ino || st.st_size > zst.st_size) {
      if (st.st_ino == zst.st_ino) {
        fd = zfd;
      } else if ((fd = open(zpath, O_RDWR)) == -1) {
        WARNF("(zip) open() error: %m");
        return false;
      }
      if ((m = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) !=
          MAP_FAILED) {
        n = st.st_size;
        if ((p = FindEmbeddedApe(m, n))) {
          b = p;
          n -= p - m;
        } else {
          b = m;
        }
        if ((d = GetZipCdir(b, n))) {
          if (zmap) {
            LOGIFNEG1(munmap(zmap, zbase + zsize - zmap));
          }
          zmap = m;
          zbase = b;
          zsize = n;
          zcdir = d;
          DCHECK(IsZipCdir32(zbase, zsize, zcdir - zbase) ||
                 IsZipCdir64(zbase, zsize, zcdir - zbase));
          memcpy(&zst, &st, sizeof(st));
          IndexAssets();
          return true;
        } else {
          WARNF("(zip) couldn't locate central directory");
        }
      } else {
        WARNF("(zip) mmap() error: %m");
      }
    }
  } else {
    WARNF("(zip) stat() error: %m");
  }
  return false;
}

static struct Asset *GetAssetZip(const char *path, size_t pathlen) {
  uint32_t i, step, hash;
  if (pathlen > 1 && path[0] == '/') ++path, --pathlen;
  hash = Hash(path, pathlen);
  for (step = 0;; ++step) {
    i = (hash + (step * (step + 1)) >> 1) & (assets.n - 1);
    if (!assets.p[i].hash) return NULL;
    if (hash == assets.p[i].hash &&
        pathlen == ZIP_CFILE_NAMESIZE(zbase + assets.p[i].cf) &&
        memcmp(path, ZIP_CFILE_NAME(zbase + assets.p[i].cf), pathlen) == 0) {
      return &assets.p[i];
    }
  }
}

static struct Asset *GetAssetFile(const char *path, size_t pathlen) {
  size_t i;
  struct Asset *a;
  if (stagedirs.n) {
    a = FreeLater(xcalloc(1, sizeof(struct Asset)));
    a->file = FreeLater(xmalloc(sizeof(struct File)));
    for (i = 0; i < stagedirs.n; ++i) {
      LockInc(&shared.c.stats);
      a->file->path.s = FreeLater(MergePaths(stagedirs.p[i].s, stagedirs.p[i].n,
                                             path, pathlen, &a->file->path.n));
      if (stat(a->file->path.s, &a->file->st) != -1) {
        a->lastmodifiedstr = FormatUnixHttpDateTime(
            FreeLater(xmalloc(30)),
            (a->lastmodified = a->file->st.st_mtim.tv_sec));
        return a;
      } else {
        LockInc(&shared.c.statfails);
      }
    }
  }
  return NULL;
}

static struct Asset *GetAsset(const char *path, size_t pathlen) {
  char *path2;
  struct Asset *a;
  if (!(a = GetAssetFile(path, pathlen))) {
    if (!(a = GetAssetZip(path, pathlen))) {
      if (pathlen > 1 && path[pathlen - 1] != '/' &&
          pathlen + 1 <= sizeof(slashpath)) {
        memcpy(mempcpy(slashpath, path, pathlen), "/", 1);
        a = GetAssetZip(slashpath, pathlen + 1);
      }
    }
  }
  return a;
}

static void GetDosLocalTime(int64_t utcunixts, uint16_t *out_time,
                            uint16_t *out_date) {
  struct tm tm;
  CHECK_NOTNULL(localtime_r(&utcunixts, &tm));
  *out_time = DOS_TIME(tm.tm_hour, tm.tm_min, tm.tm_sec);
  *out_date = DOS_DATE(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday + 1);
}

static void StoreAsset(char *path, size_t pathlen, char *data, size_t datalen,
                       int mode) {
  int64_t ft;
  int i;
  uint32_t crc;
  char *comp, *p;
  long double now;
  struct Asset *a;
  struct iovec v[13];
  uint8_t *cdir, era;
  const char *use;
  uint16_t gflags, iattrs, mtime, mdate, dosmode, method, disk;
  size_t oldcdirsize, oldcdiroffset, records, cdiroffset, cdirsize, complen,
      uselen;

  if (IsOpenbsd() || IsNetbsd() || IsWindows()) {
    DIEF("(cfg) StoreAsset() not available on Windows/NetBSD/OpenBSD yet");
  }

  INFOF("Storing asset %`'s", path);

  disk = gflags = iattrs = 0;
  if (IsUtf8(path, pathlen)) gflags |= kZipGflagUtf8;
  if (IsText(data, datalen)) iattrs |= kZipIattrText;
  crc = crc32_z(0, data, datalen);
  if (datalen < 100) {
    method = kZipCompressionNone;
    comp = 0;
    use = data;
    uselen = datalen;
    era = kZipEra1989;
  } else {
    comp = Deflate(data, datalen, &complen);
    if (complen < datalen) {
      method = kZipCompressionDeflate;
      use = comp;
      uselen = complen;
      era = kZipEra1993;
    } else {
      method = kZipCompressionNone;
      use = data;
      uselen = datalen;
      era = kZipEra1989;
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  CHECK_NE(-1, fcntl(zfd, F_SETLKW, &(struct flock){F_WRLCK}));
  OpenZip(false);
  now = nowl();
  a = GetAssetZip(path, pathlen);
  if (!mode) mode = a ? GetMode(a) : 0644;
  if (!(mode & S_IFMT)) mode |= S_IFREG;
  if (pathlen > 1 && path[0] == '/') ++path, --pathlen;
  dosmode = !(mode & 0200) ? kNtFileAttributeReadonly : 0;
  ft = (now + MODERNITYSECONDS) * HECTONANOSECONDS;
  GetDosLocalTime(now, &mtime, &mdate);
  // local file header
  if (uselen >= 0xffffffff || datalen >= 0xffffffff) {
    era = kZipEra2001;
    v[2].iov_base = p = alloca((v[2].iov_len = 2 + 2 + 8 + 8));
    p = WRITE16LE(p, kZipExtraZip64);
    p = WRITE16LE(p, 8 + 8);
    p = WRITE64LE(p, uselen);
    p = WRITE64LE(p, datalen);
  } else {
    v[2].iov_len = 0;
    v[2].iov_base = 0;
  }
  v[0].iov_base = p = alloca((v[0].iov_len = kZipLfileHdrMinSize));
  p = WRITE32LE(p, kZipLfileHdrMagic);
  *p++ = era;
  *p++ = kZipOsDos;
  p = WRITE16LE(p, gflags);
  p = WRITE16LE(p, method);
  p = WRITE16LE(p, mtime);
  p = WRITE16LE(p, mdate);
  p = WRITE32LE(p, crc);
  p = WRITE32LE(p, MIN(uselen, 0xffffffff));
  p = WRITE32LE(p, MIN(datalen, 0xffffffff));
  p = WRITE16LE(p, pathlen);
  p = WRITE16LE(p, v[2].iov_len);
  v[1].iov_len = pathlen;
  v[1].iov_base = path;
  // file data
  v[3].iov_len = uselen;
  v[3].iov_base = use;
  // old central directory entries
  oldcdirsize = GetZipCdirSize(zcdir);
  oldcdiroffset = GetZipCdirOffset(zcdir);
  if (a) {
    // to remove an existing asset,
    // first copy the central directory part before its record
    v[4].iov_base = zbase + oldcdiroffset;
    v[4].iov_len = a->cf - oldcdiroffset;
    // and then the rest of the central directory
    v[5].iov_base = zbase + oldcdiroffset +
                    (v[4].iov_len + ZIP_CFILE_HDRSIZE(zbase + a->cf));
    v[5].iov_len =
        oldcdirsize - (v[4].iov_len + ZIP_CFILE_HDRSIZE(zbase + a->cf));
  } else {
    v[4].iov_base = zbase + oldcdiroffset;
    v[4].iov_len = oldcdirsize;
    v[5].iov_base = 0;
    v[5].iov_len = 0;
  }
  // new central directory entry
  if (uselen >= 0xffffffff || datalen >= 0xffffffff || zsize >= 0xffffffff) {
    v[8].iov_base = p = alloca((v[8].iov_len = 2 + 2 + 8 + 8 + 8));
    p = WRITE16LE(p, kZipExtraZip64);
    p = WRITE16LE(p, 8 + 8 + 8);
    p = WRITE64LE(p, uselen);
    p = WRITE64LE(p, datalen);
    p = WRITE64LE(p, zsize);
  } else {
    v[8].iov_len = 0;
    v[8].iov_base = 0;
  }
  v[9].iov_base = p = alloca((v[9].iov_len = 2 + 2 + 4 + 2 + 2 + 8 + 8 + 8));
  p = WRITE16LE(p, kZipExtraNtfs);
  p = WRITE16LE(p, 4 + 2 + 2 + 8 + 8 + 8);
  p = WRITE32LE(p, 0);
  p = WRITE16LE(p, 1);
  p = WRITE16LE(p, 8 + 8 + 8);
  p = WRITE64LE(p, ft);
  p = WRITE64LE(p, ft);
  p = WRITE64LE(p, ft);
  v[6].iov_base = p = alloca((v[6].iov_len = kZipCfileHdrMinSize));
  p = WRITE32LE(p, kZipCfileHdrMagic);
  *p++ = kZipCosmopolitanVersion;
  *p++ = kZipOsUnix;
  *p++ = era;
  *p++ = kZipOsDos;
  p = WRITE16LE(p, gflags);
  p = WRITE16LE(p, method);
  p = WRITE16LE(p, mtime);
  p = WRITE16LE(p, mdate);
  p = WRITE32LE(p, crc);
  p = WRITE32LE(p, MIN(uselen, 0xffffffff));
  p = WRITE32LE(p, MIN(datalen, 0xffffffff));
  p = WRITE16LE(p, pathlen);
  p = WRITE16LE(p, v[8].iov_len + v[9].iov_len);
  p = WRITE16LE(p, 0);
  p = WRITE16LE(p, disk);
  p = WRITE16LE(p, iattrs);
  p = WRITE16LE(p, dosmode);
  p = WRITE16LE(p, mode);
  p = WRITE32LE(p, MIN(zsize, 0xffffffff));
  v[7].iov_len = pathlen;
  v[7].iov_base = path;
  // zip64 end of central directory
  cdiroffset =
      zsize + v[0].iov_len + v[1].iov_len + v[2].iov_len + v[3].iov_len;
  cdirsize = v[4].iov_len + v[5].iov_len + v[6].iov_len + v[7].iov_len +
             v[8].iov_len + v[9].iov_len;
  records = GetZipCdirRecords(zcdir) + !a;
  if (records >= 0xffff || cdiroffset >= 0xffffffff || cdirsize >= 0xffffffff) {
    v[10].iov_base = p =
        alloca((v[10].iov_len = kZipCdir64HdrMinSize + kZipCdir64LocatorSize));
    p = WRITE32LE(p, kZipCdir64HdrMagic);
    p = WRITE64LE(p, 2 + 2 + 4 + 4 + 8 + 8 + 8 + 8);
    p = WRITE16LE(p, kZipCosmopolitanVersion);
    p = WRITE16LE(p, kZipEra2001);
    p = WRITE32LE(p, disk);
    p = WRITE32LE(p, disk);
    p = WRITE64LE(p, records);
    p = WRITE64LE(p, records);
    p = WRITE64LE(p, cdirsize);
    p = WRITE64LE(p, cdiroffset);
    p = WRITE32LE(p, kZipCdir64LocatorMagic);
    p = WRITE32LE(p, disk);
    p = WRITE64LE(p, cdiroffset + cdirsize);
    p = WRITE32LE(p, disk);
  } else {
    v[10].iov_len = 0;
    v[10].iov_base = 0;
  }
  // end of central directory
  v[12].iov_base = GetZipCdirComment(zcdir);
  v[12].iov_len = GetZipCdirCommentSize(zcdir);
  v[11].iov_base = p = alloca((v[11].iov_len = kZipCdirHdrMinSize));
  p = WRITE32LE(p, kZipCdirHdrMagic);
  p = WRITE16LE(p, disk);
  p = WRITE16LE(p, disk);
  p = WRITE16LE(p, MIN(records, 0xffff));
  p = WRITE16LE(p, MIN(records, 0xffff));
  p = WRITE32LE(p, MIN(cdirsize, 0xffffffff));
  p = WRITE32LE(p, MIN(cdiroffset, 0xffffffff));
  p = WRITE16LE(p, v[12].iov_len);
  CHECK_NE(-1, lseek(zfd, zbase + zsize - zmap, SEEK_SET));
  CHECK_NE(-1, WritevAll(zfd, v, 13));
  CHECK_NE(-1, fcntl(zfd, F_SETLK, &(struct flock){F_UNLCK}));
  //////////////////////////////////////////////////////////////////////////////
  OpenZip(false);
  INFOF("DONE.");
  free(comp);
}

static void StoreFile(char *path) {
  char *p;
  size_t n;
  struct stat st;
  if (lstat(path, &st) == -1) DIEF("Can't stat %`'s: %m", path);
  if (!(p = xslurp(path, &n))) DIEF("Can't read %`'s: %m", path);
  StoreAsset(path, strlen(path), p, n, st.st_mode & 0777);
}

static void StorePath(const char *dirpath) {
  DIR *d;
  char *path;
  struct dirent *e;
  if (!isdirectory(dirpath)) return StoreFile(dirpath);
  if (!(d = opendir(dirpath))) DIEF("Can't open %`'s", dirpath);
  while ((e = readdir(d))) {
    if (strcmp(e->d_name, ".") == 0) continue;
    if (strcmp(e->d_name, "..") == 0) continue;
    path = _gc(xjoinpaths(dirpath, e->d_name));
    if (e->d_type == DT_DIR) {
      StorePath(path);
    } else {
      StoreFile(path);
    }
  }
  closedir(d);
}

static void initOpenZip() {
  if (!openzip_inited) {
    zpath = program_executable_name;
    CHECK_NE(-1, (zfd = open(zpath, O_RDWR)));
    CHECK_NE(-1, fstat(zfd, &zst));
    OpenZip(true);
    shared.workers = 1;
    openzip_inited = true;
  }
}
