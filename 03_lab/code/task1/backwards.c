#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void printPathToDir(const char *pathToDirName) {
  // printf("Path to dir is: ");
  for (int i = 0; i < strlen(pathToDirName); i++) {
    printf("%c ", pathToDirName[i]);
  }
  printf("\n");
}

void printNameFile(const char *name, const int lengthName) {
  // printf("file name is: ");
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
  return countSlashes;
}

void concatStrings(char *pathToReversedDir, char *pathBeforeLastDir,
                   char *lastDirReversed) {
  strcat(pathToReversedDir, pathBeforeLastDir);
  strcat(pathToReversedDir, lastDirReversed);

  // strcat(pathToReversedDir, "/");
}

void reverseNameFile(char *dst, char *src) {
  int idx = 0;
  for (int i = strlen(src) - 1; i >= 0; i--) {
    dst[idx] = src[i];
    // printf("iter %d : sym is %c\n", i, dst[idx]);
    idx++;
  }
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
  printf("At the beginning entered starting entry is: '%s'\n",
         pathToDir);

  const int lengthOfPathInSymbols = strlen(pathToDir);
  printf("length of string in symbols: %d\n",
  lengthOfPathInSymbols);

  int symbolsInLastDir = 0;
  for (int i = lengthOfPathInSymbols - 1; i > 0; i--) {
    if (pathToDir[i] == '/') {
      break;
    }
    symbolsInLastDir++;
  }
  printf("symbols in last dir: %d\n", symbolsInLastDir);

  char *lastDirReversed = calloc(symbolsInLastDir + 1, sizeof(char));
  for (int i = 0; i < symbolsInLastDir + 1; i++) {
    lastDirReversed[i] = pathToDir[lengthOfPathInSymbols - i];
  }

  printf("last dir reversed name is: ");
  printNameFile(lastDirReversed, symbolsInLastDir + 1);

  const int lengthPathBeforeLastDir =
      lengthOfPathInSymbols - symbolsInLastDir;
  printf("diff is %d\n", lengthPathBeforeLastDir);

  char *pathBeforeLastDir = (char *)calloc(
      lengthPathBeforeLastDir + 1, sizeof(char)); // maybe + 1 - хз пока

  for (int i = 0; i < lengthPathBeforeLastDir; i++) {
    pathBeforeLastDir[i] = pathToDir[i];
  }

  printf("path before last dir: ");
  printPathToDir(pathBeforeLastDir);

  char *pathToReversedDir =
      calloc(lengthOfPathInSymbols + 1, sizeof(char));

  concatStrings(pathToReversedDir, pathBeforeLastDir, lastDirReversed);

  printf("pathToReversedDir: ");
  printPathToDir(pathToReversedDir);
  // printNameFile(pathToReversedDir, lengthOfPathInSymbols);

  // struct stat st = {0};
  // if (stat(pathToReversedDir, &st) == -1) {
  //   mkdir(pathToReversedDir, S_IRWXU | S_IRWXO);
  // }

  // DIR *d;
  // struct dirent *entry;
  // d = opendir(pathToDir);
  // if (d) {
  //   while ((entry = readdir(d)) != NULL) {

  //     if (entry->d_type == DT_REG) {
  //       printf("entry name is: %s\n", entry->d_name);

  //       char *nameRegFile = (char *)calloc(bufferSize, sizeof(char));
  //       concatStrings(nameRegFile, pathToDir, entry->d_name);
  //       printPathToDir(nameRegFile);

  //       FILE *fileToCopy = fopen(nameRegFile, "r");
  //       if (fileToCopy == NULL) {
  //         printf("Error: %d (%s)\n", errno, strerror(errno));
  //       }

  //       else {
  //         printf("Now reading file: %s\n", entry->d_name);
  //         const int lengthEntryName = strlen(entry->d_name);
  //         char reversedName[lengthEntryName];
  //         reverseNameFile(reversedName, entry->d_name);
  //         printNameFile(reversedName, lengthEntryName);

  //         char *pathWithReversedName =
  //             (char *)calloc(bufferSize, sizeof(char));

  //         strcat(pathWithReversedName, pathToReversedDir);
  //         // strcat(pathWithReversedName, "/");
  //         strcat(pathWithReversedName, reversedName);

  //         printPathToDir(pathWithReversedName);

  //         FILE *output = fopen(pathWithReversedName, "w");
  //         if (output == NULL) {
  //           printf("Error: %d (%s)\n", errno, strerror(errno));

  //         } else {

  //           fseek(fileToCopy, 0, SEEK_END);
  //           int lastPos = ftell(output) - 1;
  //           int idx = 0;

  //           while (lastPos >= 0L) {
  //             fseek(fileToCopy, lastPos, SEEK_SET);
  //             fprintf(output, "%c", fgetc(fileToCopy));
  //             lastPos--;
  //           }

  //           // char buffer[bufferSize];
  //           // while (fgets(buffer, bufferSize, fileToCopy)) {
  //           //   fputs(buffer, output);
  //           // }

  //           fclose(output);
  //         }
  //       }
  //     }
  //   }
  //   closedir(d);
  // }

  free(pathBeforeLastDir);
  free(pathToReversedDir);
  free(lastDirReversed);
}

