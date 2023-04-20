#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void printPathToDir(const char *pathToDirName) {
  printf("Path to entry is: ");
  for (int i = 0; i < strlen(pathToDirName); i++) {
    printf("%c ", pathToDirName[i]);
  }
  printf("\n");
}

void printNameFile(const char *name, const int lengthName) {
  for (int i = 0; i < lengthName; i++) {
    printf("%c", name[i]);
  }
  printf("\n");
}

int checkIsDir(const char *name) {
  DIR *entry = opendir(name);
  if (entry != NULL) {
    closedir(entry);
    return 1; // entry is a real entry
  }
  // closedir(entry);
  return 0; // entry doesn't exist
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

void concatStrings(char *pathToReversedDir, char *pathBeforeLastDir,
                   char *lastNameDir) {
  strcat(pathToReversedDir, pathBeforeLastDir);
  strcat(pathToReversedDir, lastNameDir);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error! No path of entry entered\n");
    return 0;
  }

  // path should be end with '/' !!!!

  const int bufferSize = 4096;

  char *pathToDir = argv[1];

  if (!checkIsDir(pathToDir)) {
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           pathToDir);
    return 0;
  }
  printf("Entered starting entry is: '%s'\n", pathToDir);

  const int lengthOfPathInSymbols =
      strlen(pathToDir) - 1; // minus null term
  // printf("length of string in symbols: %d\n",
  // lengthOfPathInSymbols);

  int amountOfSlashes = countSlashesAmount(pathToDir);
  int hasSlashAtTheEnd = checkSlashAtTheEnd(pathToDir);

  char *lastNameDir = calloc(8, sizeof(char));
  int symbolsInLastDir = 0;

  for (int i = lengthOfPathInSymbols - 1; i > 0; i--) {
    while (pathToDir[i] != '/') {
      lastNameDir[symbolsInLastDir] = pathToDir[i];
      i--;
      symbolsInLastDir++;
    }
    break;
  }
  // printf("symbols in last entry: %d\n", symbolsInLastDir);

  // 23, 16
  // printNameFile(lastNameDir, symbolsInLastDir);

  const int lengthPathBeforeLastDir =
      lengthOfPathInSymbols - symbolsInLastDir;

  char *pathBeforeLastDir = (char *)calloc(
      lengthPathBeforeLastDir, sizeof(char)); // maybe + 1 - хз пока

  for (int i = 0; i < lengthPathBeforeLastDir; i++) {
    pathBeforeLastDir[i] = pathToDir[i];
  }

  // printPathToDir(pathBeforeLastDir);

  char *pathToReversedDir =
      calloc(lengthOfPathInSymbols, sizeof(char));

  concatStrings(pathToReversedDir, pathBeforeLastDir, lastNameDir);

  printPathToDir(pathToReversedDir);

  struct stat st = {0};
  if (stat(pathToReversedDir, &st) == -1) {
    mkdir(pathToReversedDir, S_IRWXU | S_IRWXO);
  }

  DIR *d;
  struct dirent *entry;
  d = opendir(pathToDir);
  if (d) {
    while ((entry = readdir(d)) != NULL) {

      if (entry->d_type == DT_REG) {
        printf("%s\n", entry->d_name);

        FILE *fileToCopy = fopen(entry->d_name, "r");
        if(fileToCopy  == NULL) {
          // printf("Error! I can't open file! \n");
          // perror("Error\n");
          printf("Error: %d (%s)\n", errno, strerror(errno));
        }

        if (fileToCopy) {
          printf("\n Now reading %s file...", entry->d_name);
          // char strDestFileName[bufferSize];
        }
      }
    }
    closedir(d);
  }

  free(pathBeforeLastDir);
  free(pathToReversedDir);
  free(lastNameDir);
}

