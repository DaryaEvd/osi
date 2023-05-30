#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void sigHandler(int num){
  printf("SIGSEGV FOUND! PROGRAM WILL BE EXIT WITH CODE -1\n");
	exit(-1);
}

int main() {
  // i
  printf("PID: %d\n", getpid());

  // ii
  sleep(5);

  // viii
  void *p = mmap(NULL, 10 * getpagesize(), 
                  // PROT_READ,
                 // PROT_WRITE ,
                 // PROT_EXEC |
                 PROT_NONE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  printf("Mapped memory: p = %p\n", p);

  /*
      PROT_NONE  The memory cannot be accessed at all.
       PROT_READ  The memory can be read.
       PROT_WRITE The memory can be modified.
       PROT_EXEC  The memory can be executed.
  */
  sleep(5);


  signal(SIGSEGV, sigHandler); 
  // x
  

  mprotect(p, 10 * getpagesize(), PROT_READ);
  char *array = (char *)p;
  array[5] = 'c';
  printf("array[5] = %c", array[5]);
  // here we get segfault

  // mprotect(p, 10 * getpagesize(), PROT_NONE);

  // mprotect(p, 10 * getpagesize(), PROT_WRITE);
  // char *array = (char *)p;
  // array[6] = 'b';

  // printf("%c\n", array[6] ); // here we get segfault


  // sleep(10);
  // if(munmap(p + getpagesize() * 4, getpagesize() * 2) != 0){
  //   perror("bad munmap");
  // }

  // sleep(10);

  return 0;
}