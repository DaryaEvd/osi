#include <sys/stat.h>
#include <sys/types.h> 
 
int main(void) { 
  struct stat statbuf;
  if(stat("/home/dasha/masec/osi/labs/03_lab/code/task2/dir_for_trash", &statbuf) == -1) {
    mkdir("/home/dasha/masec/osi/labs/03_lab/code/task2/dir_for_trash", 0777);
  }
}
