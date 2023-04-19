#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void printPathToDir(const char *pathToDirName) {
  printf("Path to dir is: ");
  for (int i = 0; i < strlen(pathToDirName); i++) {
    printf("%c ", pathToDirName[i]);
  }
  printf("\n");
}

int checkIsDir(const char *name) {
  DIR *dir = opendir(name);
  if (dir != NULL) {
    closedir(dir);
    return 1; // dir is a real dir
  }
  return 0; // dir doesn't exist
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error! No path of dir entered\n");
    return 0;
  }

  char *pathToDir = argv[1];

  if (!checkIsDir(pathToDir)) {
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           pathToDir);
    return 0;
  }
  printf("Entered starting dir is: '%s'\n", pathToDir);

  int countSlashes = 0;
  int hasSlashAtTheEnd = 0;
  for (int i = 0; i < strlen(pathToDir); i++) {
    // printf("help\n");
    if (pathToDir[i] == '/') {
      // printf("please\n");
      countSlashes++;
    } else {
      continue;
    }
  }
  printf("count of slashes: %d\n", countSlashes);

  if (pathToDir[strlen(pathToDir) - 1] == '/') {
    hasSlashAtTheEnd = 1;
  }
  printf("has slash at the end: %d\n", hasSlashAtTheEnd);

  int dirsToReverse =
      (hasSlashAtTheEnd ? countSlashes - 1 : countSlashes);
  printf("dirs to reverse : %d\n", dirsToReverse);

  const int maxDepthOfDirs = 100;
  const int maxLengthOfNameOfFile = 30;

  char **allDirs = (char **)calloc(maxDepthOfDirs, sizeof(char *));
  for (int i = 0; i < maxLengthOfNameOfFile; i++) {
    allDirs[i] = (char *)calloc(maxLengthOfNameOfFile, sizeof(char));
  }

  for (int i = 0; i < maxDepthOfDirs; i++) {
    free(allDirs[i]);
  }
  free(allDirs);
}
