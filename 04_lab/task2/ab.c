#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  //i
  printf("Pid: %d\n", getpid());
  
  // ii
  sleep(1);

  // iii
  if(execvp(argv[0], argv) != 0) {
    perror("execvp()");
    return 0;
  }

  // iv
  printf("Hello, world!\n");

  // sleep(60);
  return 0;
}

/*
exec не меняет меняет процесс, меняется только АП

Каждый раз когда делается exec ОС берет старое пространство
и выкидывает его и создает новое.
*/

//watch -n1 -d cat /proc/15701/maps