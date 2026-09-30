#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_MOUNT_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_MOUNT_H_
COSMOPOLITAN_C_START_

extern const unsigned long MS_RDONLY_;
extern const int MNT_RDONLY_;
extern const unsigned long MS_NOSUID_;
extern const int MNT_NOSUID;
extern const unsigned long MS_NODEV_;
extern const int MNT_NODEV_;
extern const unsigned long MS_NOEXEC_;
extern const int MNT_NOEXEC_;
extern const unsigned long MS_SYNCHRONOUS_;
extern const int MNT_SYNCHRONOUS_;
extern const unsigned long MS_REMOUNT_;
extern const int MNT_UPDATE_;
extern const unsigned long MS_MANDLOCK_;
extern const unsigned long MS_DIRSYNC_;
extern const unsigned long MS_NOATIME_;
extern const int MNT_NOATIME_;
extern const unsigned long MS_NODIRATIME_;
extern const unsigned long MS_BIND_;
extern const unsigned long MS_MOVE_;
extern const unsigned long MS_REC_;
extern const unsigned long MS_SILENT_;
extern const unsigned long MS_POSIXACL_;
extern const unsigned long MS_UNBINDABLE_;
extern const unsigned long MS_PRIVATE_;
extern const unsigned long MS_SLAVE_;
extern const unsigned long MS_SHARED_;
extern const unsigned long MS_RELATIME_;
extern const int MNT_RELATIME_;
extern const unsigned long MS_KERNMOUNT_;
extern const unsigned long MS_I_VERSION_;
extern const unsigned long MS_STRICTATIME_;
extern const int MNT_STRICTATIME_;
extern const unsigned long MS_LAZYTIME_;
extern const unsigned long MS_ACTIVE_;
extern const unsigned long MS_NOUSER_;
extern const unsigned long MS_RMT_MASK_;
extern const unsigned long MS_MGC_VAL_;
extern const unsigned long MS_MGC_MSK_;
extern const int MNT_ASYNC;
extern const int MNT_RELOAD;
extern const int MNT_SUIDDIR;
extern const int MNT_NOCLUSTERR;
extern const int MNT_NOCLUSTERW;
extern const int MNT_SNAPSHOT;

COSMOPOLITAN_C_END_

/* picking linux values as default; MNT_* names that have no linux
   value keep their runtime externs, since zero can't encode them */
#define MS_RDONLY       0x00000001
#define MNT_RDONLY      0x00000001
#define MS_NOSUID       0x00000002
#define MS_NODEV        0x00000004
#define MNT_NODEV       0x00000004
#define MS_NOEXEC       0x00000008
#define MNT_NOEXEC      0x00000008
#define MS_SYNCHRONOUS  0x00000010
#define MNT_SYNCHRONOUS 0x00000010
#define MS_REMOUNT      0x00000020
#define MNT_UPDATE      0x00000020
#define MS_MANDLOCK     0x00000040
#define MS_DIRSYNC      0x00000080
#define MS_NOATIME      0x00000400
#define MNT_NOATIME     0x00000400
#define MS_NODIRATIME   0x00000800
#define MS_BIND         0x00001000
#define MS_MOVE         0x00002000
#define MS_REC          0x00004000
#define MS_SILENT       0x00008000
#define MS_POSIXACL     0x00010000
#define MS_UNBINDABLE   0x00020000
#define MS_PRIVATE      0x00040000
#define MS_SLAVE        0x00080000
#define MS_SHARED       0x00100000
#define MS_RELATIME     0x00200000
#define MNT_RELATIME    0x00200000
#define MS_KERNMOUNT    0x00400000
#define MS_I_VERSION    0x00800000
#define MS_STRICTATIME  0x01000000
#define MNT_STRICTATIME 0x01000000
#define MS_LAZYTIME     0x02000000
#define MS_ACTIVE       0x40000000
#define MS_NOUSER       0x80000000
#define MS_RMT_MASK     0x02800051
#define MS_MGC_VAL      0xc0ed0000
#define MS_MGC_MSK      0xffff0000

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_MOUNT_H_ */
