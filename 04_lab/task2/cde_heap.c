#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  long size = 0;

  // v
  // const int block = 1024 * 100; // brk()
  const int block = 1024 * 1024; //mmap()

  // i
  printf("pid: %d;  size: %ld\n", getpid(), size);

  // i
  sleep(10);

  // v
  while (1) {
    malloc(block);
    size += block;

    printf("pid %d; size %ld\n", getpid(), size);
    usleep(100000);
  }

  return 0;
}


/*
чтобы наблюдать за выводом пишем команду 
'watch -d -n1 cat /proc/pid/maps'

потом пишем 
strace ./heap
*/