#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd;
  char content[fd];

  // errno = 0;
  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    // printf("File can't be opened.\n");
    // perror("open");

    printf("Oh no :( Something went wrong with open() : %s\n",
           strerror(errno));

    // str
    return 0;
  } else {
    ssize_t bytes = read(fd, content, sizeof(content) - 1);
    write(1, content, bytes);
  }

  return 0;
}
