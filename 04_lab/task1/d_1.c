#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *returnAddrNoWarning() {
  int localVar = 13;

  int *pointer = &localVar;

  return pointer;
}

int main(void) {
  printf("pid: %d\n", getpid());

  int *addressToGet = returnAddrNoWarning();

  printf("value in var: %d\n", *addressToGet);
  printf("%p\n", addressToGet);

  sleep(30);

  return 0;
}
