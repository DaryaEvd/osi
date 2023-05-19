#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  // i
  pid_t pid = getpid();
  printf("pid of proc is: %d\n", pid);

  // ii
  sleep(1);

  // iii
  if (execv("argv[0]", argv) == -1) {
   perror("execv()");
  }

  // iv
  printf("hello world\n");

  return 0;
}


/*
exec не меняет меняет процесс, меняется только АП

Каждый раз когда делается exec ОС берет старое пространство 
и выкидывает его и создает новое. 
*/