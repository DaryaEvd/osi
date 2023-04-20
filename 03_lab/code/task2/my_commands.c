#include "my_commands.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void a_create_dir(const char *pathName) {
  // /home/dasha/masec/osi/labs/03_lab/code/number2/dir_for_trash

  if (mkdir(pathName, 0777) == -1) {
    printf("Error: %s\n", strerror(errno));
  }
}

void b_print_dir_content(const char *pathName) {
  /*DIR
  represents a directory stream
  contains: info about files/subdirs, name, inode, etc
  can: read/write data, change permissions, delete a file
  */
  DIR *dir;

  /*dirent
  represents individual directory entries
  */
  struct dirent *my_dir;

  if (!(dir = opendir(
            pathName))) { // returns a pointer to the directory stream
    printf("Error: %s\n", strerror(errno));
    return;
  }

  else {
    while ((my_dir = readdir(dir)) != NULL) {
      printf("%ld %d %s\n", my_dir->d_ino, my_dir->d_type,
             my_dir->d_name);
    }
    closedir(dir);
  }
}

void c_delete_dir(const char *pathName) {
  if (rmdir(pathName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void d_create_file(const char *pathName) {
  size_t lengthPath = strlen(pathName);

  if (open(pathName, O_CREAT, S_IRUSR, S_IWUSR, S_IXGRP, S_IRWXO) ==
      -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void e_print_file_content(const char *pathName) {
  int fileDescriptor = open(pathName, O_RDONLY); // read only mode

  if (fileDescriptor == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }

  char content[BUFFER_SIZE];

  while (1) {
    ssize_t bytes =
        read(fileDescriptor, content, sizeof(content) - 1);
    if (bytes <= 0) {
      break;
    }
    write(1, content, bytes);
  }

  close(fileDescriptor);
}

void f_delete_file(const char *pathName) {
  if (unlink(pathName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void g_create_symlink(const char *pathName) {
  const char *newName = "/home/dasha/masec/osi/labs/03_lab/code/"
                        "number2/link_to_newfile.txt";

  if (symlink(pathName, newName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void h_print_symlink_content(const char *pathName) {
  e_print_file_content(pathName);
}

void i_print_target_by_symlink(const char *pathName) {
  e_print_file_content(pathName);
}

void j_remove_symlink(const char *pathName) {
  if (unlink(pathName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void k_create_hard_link(const char *pathName) {
  const char *newPathName =
      "/home/dasha/masec/osi/labs/03_lab/code/number2/hard.txt";

  if (link(pathName, newPathName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void l_remove_hard_link(const char *pathName) {
  if (unlink(pathName) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
}

void m_print_perrmission_and_hardlinks_amount(const char *pathName) {
  struct stat fileStat;

  if (stat(pathName, &fileStat) != 0) {
    printf("Error: %s\n", strerror(errno));
    return;
  }
  printf("amout of hard links is %ld\n", fileStat.st_nlink);
  printf("permissions bits are %o\n", fileStat.st_mode);

  printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

  printf("\n");
}

void n_change_perrmissions(const char *pathName, const char *perms) {
  mode_t mode = 0;

  (perms[0] == 'r') ? (mode |= S_IRUSR) : (mode &= ~S_IRUSR);
  (perms[1] == 'w') ? (mode |= S_IWUSR) : (mode &= ~S_IWUSR);
  (perms[2] == 'x') ? (mode |= S_IXUSR) : (mode &= ~S_IXUSR);
  (perms[3] == 'r') ? (mode |= S_IRGRP) : (mode &= ~S_IRGRP);
  (perms[4] == 'w') ? (mode |= S_IWGRP) : (mode &= ~S_IWGRP);
  (perms[5] == 'x') ? (mode |= S_IXGRP) : (mode &= ~S_IXGRP);
  (perms[6] == 'r') ? (mode |= S_IROTH) : (mode &= ~S_IROTH);
  (perms[7] == 'w') ? (mode |= S_IWOTH) : (mode &= ~S_IWOTH);
  (perms[8] == 'x') ? (mode |= S_IXOTH) : (mode &= ~S_IXOTH);

  chmod(pathName, mode);
}
