#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_IFF_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_IFF_H_

/* picking linux values as default */
#define IFF_UP          0x1    /* everyone agrees on these values */
#define IFF_BROADCAST   0x2    /* everyone agrees on these values */
#define IFF_DEBUG       0x4    /* everyone agrees on these values */
#define IFF_LOOPBACK    0x8    /* nt uses 0x4 */
#define IFF_POINTOPOINT 0x10   /* everyone agrees on these values */
#define IFF_NOTRAILERS  0x20   /* not supported on bsd */
#define IFF_RUNNING     0x40   /* everyone agrees on these values */
#define IFF_NOARP       0x80   /* everyone agrees on these values */
#define IFF_ALLMULTI    0x200  /* everyone agrees on these values */
#define IFF_MASTER      0x400  /* not supported on bsd */
#define IFF_SLAVE       0x800  /* not supported on bsd */
#define IFF_MULTICAST   0x1000 /* bsd uses 0x8000 */
#define IFF_PORTSEL     0x2000 /* not supported on bsd */
#define IFF_AUTOMEDIA   0x4000 /* not supported on bsd */
#define IFF_DYNAMIC     0x8000 /* not supported on bsd */
#define IFF_PROMISC     0x100  /* everyone agrees on these values */

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_IFF_H_ */
