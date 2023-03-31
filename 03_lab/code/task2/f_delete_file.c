#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  const char *pathName = 
      "/home/dasha/masec/osi/labs/03_lab/code/task2/file_to_remove.txt";
  
  if(unlink(pathName) == -1) {
    
    printf("Oh no :( Something went wrong with open()");
    
    return 0;
  }
  printf("P o b e d a \n");
  
  return 0;
}
