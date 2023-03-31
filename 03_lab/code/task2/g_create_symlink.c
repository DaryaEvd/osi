#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  const char *target = "/home/dasha/masec/osi/labs/03_lab/code/task2/a_create_dir.c";
  const char *linkpath = "/home/dasha/masec/osi/labs/03_lab/code/task2/symlink_to_a.c";

  if(symlink(target, linkpath) == -1) {
    printf("Can't create symlink\n");
  }
  else {
    printf("Pobeda\n");
  }
}
