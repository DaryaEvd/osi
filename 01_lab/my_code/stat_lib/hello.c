#include <stdio.h>
#include "static_hello.h"

int main() {  
  print_hello_static();
  return 0;
}

/*
-link 2 files into one object file 
gcc hello.c static_hello.c -o hello
./hello

-get compiled but not llinked file 
gcc -c static_hello.c

-create static library(archive)
ar rc libhello_static.a static_hello.o

-get linked file using static lib
gcc hello.c -o hello_st -lhello_static -L.
./hello_st
*/
