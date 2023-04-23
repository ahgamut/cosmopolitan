#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_BAUD_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_BAUD_H_
#include "libc/runtime/symbolic.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern const uint32_t B0;
extern const uint32_t B50;
extern const uint32_t B75;
extern const uint32_t B110;
extern const uint32_t B134;
extern const uint32_t B150;
extern const uint32_t B200;
extern const uint32_t B300;
extern const uint32_t B600;
extern const uint32_t B1200;
extern const uint32_t B1800;
extern const uint32_t B2400;
extern const uint32_t B4800;
extern const uint32_t B9600;
extern const uint32_t B19200;
extern const uint32_t B38400;
extern const uint32_t B57600;
extern const uint32_t B115200;
extern const uint32_t B230400;
extern const uint32_t B500000;
extern const uint32_t B576000;
extern const uint32_t B1000000;
extern const uint32_t B1152000;
extern const uint32_t B1500000;
extern const uint32_t B2000000;
extern const uint32_t B2500000;
extern const uint32_t B3000000;
extern const uint32_t B3500000;
extern const uint32_t B4000000;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */

#define B0       LITERALLY(0)
#define B50      ACTUALLY(B50)
#define B75      ACTUALLY(B75)
#define B110     ACTUALLY(B110)
#define B134     ACTUALLY(B134)
#define B150     ACTUALLY(B150)
#define B200     ACTUALLY(B200)
#define B300     ACTUALLY(B300)
#define B600     ACTUALLY(B600)
#define B1200    ACTUALLY(B1200)
#define B1800    ACTUALLY(B1800)
#define B2400    ACTUALLY(B2400)
#define B4800    ACTUALLY(B4800)
#define B9600    ACTUALLY(B9600)
#define B19200   ACTUALLY(B19200)
#define B38400   ACTUALLY(B38400)
#define B57600   ACTUALLY(B57600)
#define B115200  ACTUALLY(B115200)
#define B230400  ACTUALLY(B230400)
#define B500000  ACTUALLY(B500000)
#define B576000  ACTUALLY(B576000)
#define B1000000 ACTUALLY(B1000000)
#define B1152000 ACTUALLY(B1152000)
#define B1500000 ACTUALLY(B1500000)
#define B2000000 ACTUALLY(B2000000)
#define B2500000 ACTUALLY(B2500000)
#define B3000000 ACTUALLY(B3000000)
#define B3500000 ACTUALLY(B3500000)
#define B4000000 ACTUALLY(B4000000)

#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_BAUD_H_ */
