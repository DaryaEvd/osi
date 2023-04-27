#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int returnAddress() {
//   int localVar = 1;
//   return &localVar;
// }

int *returnAddrNoWarning() {
  int localVar = 13;

  int *pointer = &localVar;
  
  return pointer;
}

int main(void) {
  printf("pid: %d\n", getpid());
  
  // int addrToGet = returnAddress();

  int *addressToGet = returnAddrNoWarning();

  printf("%p\n", addressToGet);

  sleep(30);
  
  return 0;
}