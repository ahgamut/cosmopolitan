#ifndef COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_
#define COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_

#ifdef __ASSEMBLER__
/* clang-format off */
#define SYMBOLIC(NAME) NAME(%rip)
#define LITERALLY(NAME) $NAME
/* clang-format on */
#else
#ifndef SYMBOLIC
#define SYMBOLIC(NAME) NAME
#endif
#define LITERALLY(NAME) NAME
#endif

#endif /* COSMOPOLITAN_LIBC_RUNTIME_SYMBOLIC_H_ */
