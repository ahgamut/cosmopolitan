#if 0
/*─────────────────────────────────────────────────────────────────╗
│ To the extent possible under law, Justine Tunney has waived      │
│ all copyright and related or neighboring rights to this file,    │
│ as it is written in the following disclaimers:                   │
│   • http://unlicense.org/                                        │
│   • http://creativecommons.org/publicdomain/zero/1.0/            │
╚─────────────────────────────────────────────────────────────────*/
#endif
#include "libc/calls/calls.h"
#include "libc/errno.h"
#include "libc/fmt/itoa.h"
#include "libc/intrin/kprintf.h"
#include "libc/runtime/runtime.h"
#include "libc/stdio/stdio.h"

// this implementation uses cosmopolitan specific apis so that the
// resulting program will be 28kb in size. the proper way to do it
// though is use sysconf(_SC_NPROCESSORS_ONLN), which is humongous

int main() {
  int count;
  if ((count = __get_cpu_count()) != -1) {
    char ibuf[12];
    FormatInt32(ibuf, count);
    tinyprint(1, ibuf, "\n", NULL);
    return 0;
  } else {
    perror("__get_cpu_count");
    return 1;
  }
}
