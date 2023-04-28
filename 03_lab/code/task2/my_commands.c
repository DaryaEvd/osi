#include "my_commands.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void a_create_dir(const char *pathName) {
  if (mkdir(pathName, S_IROTH | S_IWOTH | S_IXOTH | S_IRUSR |
                          S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP |
                          S_IXGRP) == -1) {
    printf("Error: %s\n", strerror(errno));
    return;
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

  if (open(pathName, O_CREAT, S_IRUSR, S_IWUSR, S_IXGRP, S_IRWXO,
           S_IROTH, S_IROTH) == -1) {
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

void g_create_symlink(const char *pathName, const char *symLinkPath) {
  if (symlink(pathName, symLinkPath) == -1) {
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

void k_create_hard_link(const char *pathName,
                        const char *hardLinkPath) {
  if (link(pathName, hardLinkPath) == -1) {
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

int parsePerms(const char *charPerms);

void n_change_permissions(const char *pathName,
                          const char *charPerms) {

  mode_t mode = parsePerms(charPerms);

  chmod(pathName, mode);
}

int parsePerms(const char *permsChar) {
  mode_t result = 0;

  (permsChar[0] == 'r') ? (result |= S_IRUSR) : (result &= ~S_IRUSR);
  (permsChar[1] == 'w') ? (result |= S_IWUSR) : (result &= ~S_IWUSR);
  (permsChar[2] == 'x') ? (result |= S_IXUSR) : (result &= ~S_IXUSR);
  (permsChar[3] == 'r') ? (result |= S_IRGRP) : (result &= ~S_IRGRP);
  (permsChar[4] == 'w') ? (result |= S_IWGRP) : (result &= ~S_IWGRP);
  (permsChar[5] == 'x') ? (result |= S_IXGRP) : (result &= ~S_IXGRP);
  (permsChar[6] == 'r') ? (result |= S_IROTH) : (result &= ~S_IROTH);
  (permsChar[7] == 'w') ? (result |= S_IWOTH) : (result &= ~S_IWOTH);
  (permsChar[8] == 'x') ? (result |= S_IXOTH) : (result &= ~S_IXOTH);

  return result;
}
