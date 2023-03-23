#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

static ssize_t write_wrapper(unsigned int fildes, const void *buf,
                             size_t nbytes) {
  /*
  1st arg - SYS_write - number of syscall
  */
  return syscall(SYS_write, fildes, buf, nbytes);
}

int main(void) {
  int ret = write_wrapper(1, "privet mir!!!", 5);

  printf("ret = %d: %s \n", ret, strerror(errno));

  return 0;
}
