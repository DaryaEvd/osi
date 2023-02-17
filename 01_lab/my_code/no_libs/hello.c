#include <stdio.h>

void print_hello(void) {
  printf("hello world!!!\n");
}

int main() {
  print_hello();
  return 0;
}

/*
1.
-get object file:
gcc -o hello.o hello.c

-find unreolved symbols:
nm ./hello.o |vim -

-find dependecies
ldd ./hello.o

-run
./hello.o

=========================================================
2.

*/