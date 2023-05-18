#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  long size = 0;

  // const int block = 1024 * 100; // brk()
  const int block = 1024 * 1024; //mmap()

  printf("pid: %d;  size: %ld\n", getpid(), size);

  sleep(10);

  while (1) {
    malloc(block);
    size += block;

    printf("pid %d; size %ld\n", getpid(), size);
    usleep(100000);
  }

  return 0;
}


/*
чтобы нублюдать за выводом пишем команду 
'watch -d -n1 cat /proc/pid/maps'

потом пишем 
strace ./heap
*/