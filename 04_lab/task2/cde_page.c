#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  // i
  printf("PID: %d\n", getpid());
  
  // ii
  sleep(10);

  // viii
  void *p = mmap(NULL, 10 * getpagesize(),
                 PROT_READ | PROT_WRITE | PROT_EXEC,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  printf("Mapped memory: p = %p\n", p);
  sleep(20);

  // x

  // mprotect(p, 10 * getpagesize(), PROT_READ);
  mprotect(p, 10 * getpagesize(), PROT_WRITE);

  char *array = (char *)p;
  // char symbol = array[1];

  // printf("%c\n", symbol); // we've read from mapped region

  // array[10] = 'a'; // here we got seg fault, cause we have no
                   // permission for writing in this region

  ////////////////////////////////

  for(int i = 0; i < 15; i++) {
    array[i] = i + 1;
    printf("%c ", array[i]);
  }

  // printf("%c\n", symbol);
  // array[10] = 'a';

  return 0;
}