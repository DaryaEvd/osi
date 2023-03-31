#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
  const char *pathName =
      "/home/dasha/masec/osi/labs/03_lab/code/task2/new_file.txt";
  size_t lengthPath = strlen(pathName);

  if(open(pathName, O_CREAT, S_IRWXU) == -1) {
    printf("Can't create a file\n");
  }
  printf("File successfuly created\n");
}