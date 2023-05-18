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
  if (execv("./exec", argv) == -1) {
   perror("execv()");
  }

  // iv
  printf("hello world\n");

  return 0;
}
