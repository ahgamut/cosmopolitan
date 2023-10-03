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
#include "libc/intrin/kprintf.h"
#include "libc/log/check.h"

int main(int argc, char *argv[]) {
  char name[254];
  gethostname(name, sizeof(name));
  kprintf("gethostname() → %#s\n", name);
  getdomainname(name, sizeof(name));
  kprintf("getdomainname() → %#s\n", name);
  return 0;
}
