#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void function() {
  int array[4096];
  int i = 0;
  printf("%d: %d\n", i++, getpid());
  usleep(20000);
  function();

}

int main(int argc, char **argv) {
  // i
  pid_t pid = getpid();
  printf("main pid is: %d", pid);
  
  // // ii
  sleep(20);

  // // iii
  function();

  return 0;
}


/*
получим сигфолт
*/