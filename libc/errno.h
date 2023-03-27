#ifndef COSMOPOLITAN_LIBC_ERRNO_H_
#define COSMOPOLITAN_LIBC_ERRNO_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

/**
 * @fileoverview System error codes.
 * @see libc/sysv/consts.sh for numbers
 */

#if defined(__GNUC__) && defined(__x86_64__) && defined(__MNO_RED_ZONE__) && \
    !defined(__STRICT_ANSI__)
#define errno                                                           \
  (*({                                                                  \
    errno_t *_ep;                                                       \
    asm("call\t__errno_location" : "=a"(_ep) : /* no inputs */ : "cc"); \
    _ep;                                                                \
  }))
#else
#define errno (*__errno_location())
#endif

/**
 * System call unavailable.
 * @note kNtErrorInvalidFunction on NT
 */
extern const errno_t ENOSYS;

/**
 * Operation not permitted.
 * @note kNtErrorInvalidAccess on NT
 */
extern const errno_t EPERM;

/**
 * No such file or directory.
 */
extern const errno_t ENOENT;

/**
 * No such process.
 */
extern const errno_t ESRCH;

/**
 * The greatest of all errnos.
 */
extern const errno_t EINTR;

/**
 * Unix consensus.
 */
extern const errno_t EIO;

/**
 * No such device or address.
 */
extern const errno_t ENXIO;

/**
 * Argument list too errno_t.
 */
extern const errno_t E2BIG;

/**
 * Exec format error.
 */
extern const errno_t ENOEXEC;

/**
 * Bad file descriptor.
 */
extern const errno_t EBADF;

/**
 * No child process.
 */
extern const errno_t ECHILD;

/**
 * Resource temporarily unavailable (e.g. SO_RCVTIMEO expired, too many
 * processes, too much memory locked, read or write with O_NONBLOCK needs
 * polling, etc.).
 */
extern const errno_t EAGAIN;

/**
 * We require more vespene gas.
 */
extern const errno_t ENOMEM;

/**
 * Permission denied.
 */
extern const errno_t EACCES;

/**
 * Pointer passed to system call that would otherwise segfault.
 */
extern const errno_t EFAULT;

/**
 * Block device required.
 */
extern const errno_t ENOTBLK;

/**
 * Device or resource busy.
 */
extern const errno_t EBUSY;

/**
 * File exists.
 */
extern const errno_t EEXIST;

/**
 * Improper link.
 */
extern const errno_t EXDEV;

/**
 * No such device.
 */
extern const errno_t ENODEV;

/**
 * Not a directory.
 */
extern const errno_t ENOTDIR;

/**
 * Is a a directory.
 */
extern const errno_t EISDIR;

/**
 * Invalid argument.
 */
extern const errno_t EINVAL;

/**
 * Too many open files in system.
 */
extern const errno_t ENFILE;

/**
 * Too many open files.
 */
extern const errno_t EMFILE;

/**
 * Inappropriate i/o control operation.
 */
extern const errno_t ENOTTY;

/**
 * Won't open executable that's executing in write mode.
 */
extern const errno_t ETXTBSY;

/**
 * File too large.
 */
extern const errno_t EFBIG;

/**
 * No space left on device.
 */
extern const errno_t ENOSPC;

/**
 * Disk quota exceeded.
 */
extern const errno_t EDQUOT;

/**
 * Invalid seek.
 */
extern const errno_t ESPIPE;

/**
 * Read-only filesystem.
 */
extern const errno_t EROFS;

/**
 * Too many links.
 */
extern const errno_t EMLINK;

/**
 * Broken pipe.
 */
extern const errno_t EPIPE;

/**
 * Mathematics argument out of domain of function.
 */
extern const errno_t EDOM;

/**
 * Result too large.
 */
extern const errno_t ERANGE;

/**
 * Resource deadlock avoided.
 */
extern const errno_t EDEADLK;

/**
 * Filename too errno_t.
 */
extern const errno_t ENAMETOOLONG;

/**
 * No locks available.
 */
extern const errno_t ENOLCK;

/**
 * Directory not empty.
 */
extern const errno_t ENOTEMPTY;

/**
 * Too many levels of symbolic links.
 */
extern const errno_t ELOOP;

/**
 * No message error.
 */
extern const errno_t ENOMSG;

/**
 * Identifier removed.
 */
extern const errno_t EIDRM;

/**
 * Timer expired.
 */
extern const errno_t ETIME;

/**
 * Protocol error.
 */
extern const errno_t EPROTO;

/**
 * Overflow error.
 */
extern const errno_t EOVERFLOW;

/**
 * Unicode decoding error.
 */
extern const errno_t EILSEQ;

/**
 * Too many users.
 */
extern const errno_t EUSERS;

/**
 * Not a socket.
 */
extern const errno_t ENOTSOCK;

/**
 * Destination address required.
 */
extern const errno_t EDESTADDRREQ;

/**
 * Message too errno_t.
 */
extern const errno_t EMSGSIZE;

/**
 * Protocol wrong type for socket.
 */
extern const errno_t EPROTOTYPE;

/**
 * Protocol not available.
 */
extern const errno_t ENOPROTOOPT;

/**
 * Protocol not supported.
 */
extern const errno_t EPROTONOSUPPORT;

/**
 * Socket type not supported.
 */
extern const errno_t ESOCKTNOSUPPORT;

/**
 * Operation not supported.
 */
extern const errno_t ENOTSUP;

/**
 * Socket operation not supported.
 */
extern const errno_t EOPNOTSUPP;

/**
 * Protocol family not supported.
 */
extern const errno_t EPFNOSUPPORT;

/**
 * Address family not supported.
 */
extern const errno_t EAFNOSUPPORT;

/**
 * Address already in use.
 */
extern const errno_t EADDRINUSE;

/**
 * Address not available.
 */
extern const errno_t EADDRNOTAVAIL;

/**
 * Network is down.
 */
extern const errno_t ENETDOWN;

/**
 * Host is unreachable.
 */
extern const errno_t ENETUNREACH;

/**
 * Connection reset by network.
 */
extern const errno_t ENETRESET;

/**
 * Connection reset before accept.
 */
extern const errno_t ECONNABORTED;

/**
 * Connection reset by client.
 */
extern const errno_t ECONNRESET;

/**
 * No buffer space available.
 */
extern const errno_t ENOBUFS;

/**
 * Socket is connected.
 */
extern const errno_t EISCONN;

/**
 * Socket is not connected.
 */
extern const errno_t ENOTCONN;

/**
 * Cannot send after transport endpoint shutdown.
 */
extern const errno_t ESHUTDOWN;

/**
 * Too many references: cannot splice.
 */
extern const errno_t ETOOMANYREFS;

/**
 * Connection timed out.
 */
extern const errno_t ETIMEDOUT;

/**
 * Connection refused error.
 */
extern const errno_t ECONNREFUSED;

/**
 * Host down error.
 */
extern const errno_t EHOSTDOWN;

/**
 * Host unreachable error.
 */
extern const errno_t EHOSTUNREACH;

/**
 * Connection already in progress.
 */
extern const errno_t EALREADY;

/**
 * Operation already in progress.
 */
extern const errno_t EINPROGRESS;

/**
 * Stale error.
 */
extern const errno_t ESTALE;

/**
 * Remote error.
 */
extern const errno_t EREMOTE;

/**
 * Bad message.
 */
extern const errno_t EBADMSG;

/**
 * Operation canceled.
 */
extern const errno_t ECANCELED;

/**
 * Owner died.
 */
extern const errno_t EOWNERDEAD;

/**
 * State not recoverable.
 */
extern const errno_t ENOTRECOVERABLE;

/**
 * No network.
 */
extern const errno_t ENONET;

/**
 * Please restart syscall.
 */
extern const errno_t ERESTART;

/**
 * Out of streams resources.
 */
extern const errno_t ENOSR;

/**
 * No string.
 */
extern const errno_t ENOSTR;

/**
 * No data.
 */
extern const errno_t ENODATA;

/**
 * Multihop attempted.
 */
extern const errno_t EMULTIHOP;

/**
 * Link severed.
 */
extern const errno_t ENOLINK;

/**
 * No medium found.
 */
extern const errno_t ENOMEDIUM;

/**
 * Wrong medium type.
 */
extern const errno_t EMEDIUMTYPE;

/**
 * Inappropriate file type or format. (BSD only)
 */
extern const errno_t EFTYPE;

extern const errno_t EAUTH;
extern const errno_t EBADARCH;
extern const errno_t EBADEXEC;
extern const errno_t EBADMACHO;
extern const errno_t EBADRPC;
extern const errno_t EDEVERR;
extern const errno_t ENEEDAUTH;
extern const errno_t ENOATTR;
extern const errno_t ENOPOLICY;
extern const errno_t EPROCLIM;
extern const errno_t EPROCUNAVAIL;
extern const errno_t EPROGMISMATCH;
extern const errno_t EPROGUNAVAIL;
extern const errno_t EPWROFF;
extern const errno_t ERPCMISMATCH;
extern const errno_t ESHLIBVERS;

extern const errno_t EADV;
extern const errno_t EBADE;
extern const errno_t EBADFD;
extern const errno_t EBADR;
extern const errno_t EBADRQC;
extern const errno_t EBADSLT;
extern const errno_t ECHRNG;
extern const errno_t ECOMM;
extern const errno_t EDOTDOT;
extern const errno_t EHWPOISON;
extern const errno_t EISNAM;
extern const errno_t EKEYEXPIRED;
extern const errno_t EKEYREJECTED;
extern const errno_t EKEYREVOKED;
extern const errno_t EL2HLT;
extern const errno_t EL2NSYNC;
extern const errno_t EL3HLT;
extern const errno_t EL3RST;
extern const errno_t ELIBACC;
extern const errno_t ELIBBAD;
extern const errno_t ELIBEXEC;
extern const errno_t ELIBMAX;
extern const errno_t ELIBSCN;
extern const errno_t ELNRNG;
extern const errno_t ENAVAIL;
extern const errno_t ENOANO;
extern const errno_t ENOCSI;
extern const errno_t ENOKEY;
extern const errno_t ENOPKG;
extern const errno_t ENOTNAM;
extern const errno_t ENOTUNIQ;
extern const errno_t EREMCHG;
extern const errno_t EREMOTEIO;
extern const errno_t ERFKILL;
extern const errno_t ESRMNT;
extern const errno_t ESTRPIPE;
extern const errno_t EUCLEAN;
extern const errno_t EUNATCH;
extern const errno_t EXFULL;

#define E2BIG           ACTUALLY(E2BIG)
#define EACCES          ACTUALLY(EACCES)
#define EADDRINUSE      ACTUALLY(EADDRINUSE)
#define EADDRNOTAVAIL   ACTUALLY(EADDRNOTAVAIL)
#define EADV            ACTUALLY(EADV)
#define EAFNOSUPPORT    ACTUALLY(EAFNOSUPPORT)
#define EAGAIN          ACTUALLY(EAGAIN)
#define EALREADY        ACTUALLY(EALREADY)
#define EAUTH           ACTUALLY(EAUTH)
#define EBADARCH        ACTUALLY(EBADARCH)
#define EBADE           ACTUALLY(EBADE)
#define EBADEXEC        ACTUALLY(EBADEXEC)
#define EBADF           ACTUALLY(EBADF)
#define EBADFD          ACTUALLY(EBADFD)
#define EBADMACHO       ACTUALLY(EBADMACHO)
#define EBADMSG         ACTUALLY(EBADMSG)
#define EBADR           ACTUALLY(EBADR)
#define EBADRPC         ACTUALLY(EBADRPC)
#define EBADRQC         ACTUALLY(EBADRQC)
#define EBADSLT         ACTUALLY(EBADSLT)
#define EBUSY           ACTUALLY(EBUSY)
#define ECANCELED       ACTUALLY(ECANCELED)
#define ECHILD          ACTUALLY(ECHILD)
#define ECHRNG          ACTUALLY(ECHRNG)
#define ECOMM           ACTUALLY(ECOMM)
#define ECONNABORTED    ACTUALLY(ECONNABORTED)
#define ECONNREFUSED    ACTUALLY(ECONNREFUSED)
#define ECONNRESET      ACTUALLY(ECONNRESET)
#define EDEADLK         ACTUALLY(EDEADLK)
#define EDESTADDRREQ    ACTUALLY(EDESTADDRREQ)
#define EDEVERR         ACTUALLY(EDEVERR)
#define EDOM            ACTUALLY(EDOM)
#define EDOTDOT         ACTUALLY(EDOTDOT)
#define EDQUOT          ACTUALLY(EDQUOT)
#define EEXIST          ACTUALLY(EEXIST)
#define EFAULT          ACTUALLY(EFAULT)
#define EFBIG           ACTUALLY(EFBIG)
#define EFTYPE          ACTUALLY(EFTYPE)
#define EHOSTDOWN       ACTUALLY(EHOSTDOWN)
#define EHOSTUNREACH    ACTUALLY(EHOSTUNREACH)
#define EHWPOISON       ACTUALLY(EHWPOISON)
#define EIDRM           ACTUALLY(EIDRM)
#define EILSEQ          ACTUALLY(EILSEQ)
#define EINPROGRESS     ACTUALLY(EINPROGRESS)
#define EINTR           ACTUALLY(EINTR)
#define EINVAL          ACTUALLY(EINVAL)
#define EIO             ACTUALLY(EIO)
#define EISCONN         ACTUALLY(EISCONN)
#define EISDIR          ACTUALLY(EISDIR)
#define EISNAM          ACTUALLY(EISNAM)
#define EKEYEXPIRED     ACTUALLY(EKEYEXPIRED)
#define EKEYREJECTED    ACTUALLY(EKEYREJECTED)
#define EKEYREVOKED     ACTUALLY(EKEYREVOKED)
#define EL2HLT          ACTUALLY(EL2HLT)
#define EL2NSYNC        ACTUALLY(EL2NSYNC)
#define EL3HLT          ACTUALLY(EL3HLT)
#define EL3RST          ACTUALLY(EL3RST)
#define ELIBACC         ACTUALLY(ELIBACC)
#define ELIBBAD         ACTUALLY(ELIBBAD)
#define ELIBEXEC        ACTUALLY(ELIBEXEC)
#define ELIBMAX         ACTUALLY(ELIBMAX)
#define ELIBSCN         ACTUALLY(ELIBSCN)
#define ELNRNG          ACTUALLY(ELNRNG)
#define ELOOP           ACTUALLY(ELOOP)
#define EMEDIUMTYPE     ACTUALLY(EMEDIUMTYPE)
#define EMFILE          ACTUALLY(EMFILE)
#define EMLINK          ACTUALLY(EMLINK)
#define EMSGSIZE        ACTUALLY(EMSGSIZE)
#define EMULTIHOP       ACTUALLY(EMULTIHOP)
#define ENAMETOOLONG    ACTUALLY(ENAMETOOLONG)
#define ENAVAIL         ACTUALLY(ENAVAIL)
#define ENEEDAUTH       ACTUALLY(ENEEDAUTH)
#define ENETDOWN        ACTUALLY(ENETDOWN)
#define ENETRESET       ACTUALLY(ENETRESET)
#define ENETUNREACH     ACTUALLY(ENETUNREACH)
#define ENFILE          ACTUALLY(ENFILE)
#define ENOANO          ACTUALLY(ENOANO)
#define ENOATTR         ACTUALLY(ENOATTR)
#define ENOBUFS         ACTUALLY(ENOBUFS)
#define ENOCSI          ACTUALLY(ENOCSI)
#define ENODATA         ACTUALLY(ENODATA)
#define ENODEV          ACTUALLY(ENODEV)
#define ENOENT          ACTUALLY(ENOENT)
#define ENOEXEC         ACTUALLY(ENOEXEC)
#define ENOKEY          ACTUALLY(ENOKEY)
#define ENOLCK          ACTUALLY(ENOLCK)
#define ENOLINK         ACTUALLY(ENOLINK)
#define ENOMEDIUM       ACTUALLY(ENOMEDIUM)
#define ENOMEM          ACTUALLY(ENOMEM)
#define ENOMSG          ACTUALLY(ENOMSG)
#define ENONET          ACTUALLY(ENONET)
#define ENOPKG          ACTUALLY(ENOPKG)
#define ENOPOLICY       ACTUALLY(ENOPOLICY)
#define ENOPROTOOPT     ACTUALLY(ENOPROTOOPT)
#define ENOSPC          ACTUALLY(ENOSPC)
#define ENOSR           ACTUALLY(ENOSR)
#define ENOSTR          ACTUALLY(ENOSTR)
#define ENOSYS          ACTUALLY(ENOSYS)
#define ENOTBLK         ACTUALLY(ENOTBLK)
#define ENOTCONN        ACTUALLY(ENOTCONN)
#define ENOTDIR         ACTUALLY(ENOTDIR)
#define ENOTEMPTY       ACTUALLY(ENOTEMPTY)
#define ENOTNAM         ACTUALLY(ENOTNAM)
#define ENOTRECOVERABLE ACTUALLY(ENOTRECOVERABLE)
#define ENOTSOCK        ACTUALLY(ENOTSOCK)
#define ENOTSUP         ACTUALLY(ENOTSUP)
#define ENOTTY          ACTUALLY(ENOTTY)
#define ENOTUNIQ        ACTUALLY(ENOTUNIQ)
#define ENXIO           ACTUALLY(ENXIO)
#define EOPNOTSUPP      ACTUALLY(EOPNOTSUPP)
#define EOVERFLOW       ACTUALLY(EOVERFLOW)
#define EOWNERDEAD      ACTUALLY(EOWNERDEAD)
#define EPERM           ACTUALLY(EPERM)
#define EPFNOSUPPORT    ACTUALLY(EPFNOSUPPORT)
#define EPIPE           ACTUALLY(EPIPE)
#define EPROCLIM        ACTUALLY(EPROCLIM)
#define EPROCUNAVAIL    ACTUALLY(EPROCUNAVAIL)
#define EPROGMISMATCH   ACTUALLY(EPROGMISMATCH)
#define EPROGUNAVAIL    ACTUALLY(EPROGUNAVAIL)
#define EPROTO          ACTUALLY(EPROTO)
#define EPROTONOSUPPORT ACTUALLY(EPROTONOSUPPORT)
#define EPROTOTYPE      ACTUALLY(EPROTOTYPE)
#define EPWROFF         ACTUALLY(EPWROFF)
#define ERANGE          ACTUALLY(ERANGE)
#define EREMCHG         ACTUALLY(EREMCHG)
#define EREMOTE         ACTUALLY(EREMOTE)
#define EREMOTEIO       ACTUALLY(EREMOTEIO)
#define ERESTART        ACTUALLY(ERESTART)
#define ERFKILL         ACTUALLY(ERFKILL)
#define EROFS           ACTUALLY(EROFS)
#define ERPCMISMATCH    ACTUALLY(ERPCMISMATCH)
#define ESHLIBVERS      ACTUALLY(ESHLIBVERS)
#define ESHUTDOWN       ACTUALLY(ESHUTDOWN)
#define ESOCKTNOSUPPORT ACTUALLY(ESOCKTNOSUPPORT)
#define ESPIPE          ACTUALLY(ESPIPE)
#define ESRCH           ACTUALLY(ESRCH)
#define ESRMNT          ACTUALLY(ESRMNT)
#define ESTALE          ACTUALLY(ESTALE)
#define ESTRPIPE        ACTUALLY(ESTRPIPE)
#define ETIME           ACTUALLY(ETIME)
#define ETIMEDOUT       ACTUALLY(ETIMEDOUT)
#define ETOOMANYREFS    ACTUALLY(ETOOMANYREFS)
#define ETXTBSY         ACTUALLY(ETXTBSY)
#define EUCLEAN         ACTUALLY(EUCLEAN)
#define EUNATCH         ACTUALLY(EUNATCH)
#define EUSERS          ACTUALLY(EUSERS)
#define EWOULDBLOCK     EAGAIN
#define EXDEV           ACTUALLY(EXDEV)
#define EXFULL          ACTUALLY(EXFULL)

extern errno_t __errno;
errno_t *__errno_location(void);

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_ERRNO_H_ */
