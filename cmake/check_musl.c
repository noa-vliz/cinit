#include <stdio.h>

#if defined(__linux__) && !defined(__GLIBC__)
  int main() { return 0; }
#else
  #error "Not using musl"
#endif
