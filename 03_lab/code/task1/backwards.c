#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct FilePos {
  char *file;
  int idx;
} FilePos;

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

int checkSlashAtTheEnd(const char *pathToDirName) {
  int hasSlash = 0;
  if (pathToDirName[strlen(pathToDirName) - 1] == '/') {
    hasSlash = 1;
  }
  printf("has slash at the end: %d\n", hasSlash);

  return hasSlash;
}

int countSlashesAmount(char *pathToDir) {
  int countSlashes = 0;
  for (int i = 0; i < strlen(pathToDir); i++) {
    if (pathToDir[i] == '/') {
      countSlashes++;
    } else {
      continue;
    }
  }
  printf("count of slashes: %d\n", countSlashes);
  return countSlashes;
}

void printNameFile(const char *name, const int lengthName) {
  for(int i = 0; i < lengthName; i++) {
    printf("%c", name[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error! No path of dir entered\n");
    return 0;
  }

  // path should be end with '/' !!!!

  char *pathToDir = argv[1];

  if (!checkIsDir(pathToDir)) {
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           pathToDir);
    return 0;
  }
  printf("Entered starting dir is: '%s'\n", pathToDir);

  const int lengthOfPathInSymbols = strlen(pathToDir);
  printf("length of string in symbols: %d\n", lengthOfPathInSymbols);

  int amountOfSlashes = countSlashesAmount(pathToDir);
  int hasSlashAtTheEnd = checkSlashAtTheEnd(pathToDir);

  int amountDirsToReverse =
      (hasSlashAtTheEnd ? amountOfSlashes - 1 : amountOfSlashes);
  printf("dirs to reverse : %d\n", amountDirsToReverse);

  const int maxDepthOfDirs = 100;
  const int maxLengthOfNameOfFile = 30;

  char **allDirs = (char **)calloc(maxDepthOfDirs, sizeof(char *));
  for (int i = 0; i < maxLengthOfNameOfFile; i++) {
    allDirs[i] = (char *)calloc(maxLengthOfNameOfFile, sizeof(char));
  }

  for (int i = 1; i <= lengthOfPathInSymbols; i++) {
    int symbolsInOneName = 0;
    char *name = calloc(maxLengthOfNameOfFile, sizeof(char));

    while (pathToDir[i] != '/') {      
      name[symbolsInOneName] = pathToDir[i];
      i++;
      symbolsInOneName++;
      
    }
    printf("iteration %d : symbols in name: %d\n", i, symbolsInOneName);
    printNameFile(name, symbolsInOneName);
  }

  for (int i = 0; i < maxDepthOfDirs; i++) {
    free(allDirs[i]);
  }
  free(allDirs);
}

