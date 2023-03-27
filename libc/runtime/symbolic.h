#ifndef COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_
#define COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_

#ifdef __ASSEMBLER__
/* clang-format off */
#define SYMBOLIC(NAME) NAME(%rip)
#define LITERALLY(NAME) $NAME
#define ACTUALLY(NAME) NAME(%rip)
/* clang-format on */
#else
#define SYMBOLIC(NAME) NAME
#define LITERALLY(NAME) NAME
#ifndef ACTUALLY
#define ACTUALLY(NAME) NAME
#endif
#endif

#endif /* COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_ */
