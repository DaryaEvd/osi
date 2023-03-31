#include <dirent.h>
#include <stddef.h>
#include <stdio.h>

int main(void) {
  DIR *dir;
  struct dirent *my_dir;
  dir = opendir("/home/dasha/masec/osi/labs/03_lab/code/task2");

  if(dir) {
    while ((my_dir = readdir(dir)) != NULL) {
      printf("%ld %d %s\n", my_dir->d_ino, my_dir->d_type, my_dir->d_name);

    }
    closedir(dir);
  }
  return 0;
}