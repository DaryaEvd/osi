#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
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
  printf("reversed name is: ");
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

void reverseNameFile(char *dst, char *src) {
  int idx = 0;
  for (int i = strlen(src) - 1; i >= 0; i--) {
    dst[idx] = src[i];
    // printf("iter %d : sym is %c\n", i, dst[idx]);
    idx++;
  }
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

  const int bufferSize = 1;

  char *pathToDir = argv[1];

  if (!checkIsDir(pathToDir)) {
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           pathToDir);
    return 0;
  }
  printf("Entered starting entry is: '%s'\n", pathToDir);

  const int lengthOfPathInSymbols = strlen(pathToDir);
  printf("length of string in symbols: %d\n", lengthOfPathInSymbols);

  //  char *lastNameDir = calloc(8, sizeof(char));
  int symbolsInLastDir = 0;

  for (int i = lengthOfPathInSymbols - 1; i > 0; i--) {
    while (pathToDir[i] != '/') {
      //     lastNameDir[symbolsInLastDir] = pathToDir[i];
      i--;
      symbolsInLastDir++;
    }
    break;
  }
  // printf("symbols in last entry: %d\n", symbolsInLastDir);

  char *lastNameDir = calloc(symbolsInLastDir + 1, sizeof(char));
  printf("%c", pathToDir[lengthOfPathInSymbols]);
  for (int i = 0; i < symbolsInLastDir + 1; i++) {
    lastNameDir[i] = pathToDir[lengthOfPathInSymbols - i - 1];
  }

  // 23, 16
  printNameFile(lastNameDir, symbolsInLastDir);

  const int lengthPathBeforeLastDir =
      lengthOfPathInSymbols - symbolsInLastDir;

  char *pathBeforeLastDir = (char *)calloc(
      lengthPathBeforeLastDir, sizeof(char)); // maybe + 1 - хз пока

  for (int i = 0; i < lengthPathBeforeLastDir; i++) {
    pathBeforeLastDir[i] = pathToDir[i];
  }

  // printPathToDir(pathBeforeLastDir);

  char *pathToReversedDir = calloc(lengthOfPathInSymbols,
                                   sizeof(char)); // changed heere

  concatStrings(pathToReversedDir, pathBeforeLastDir, lastNameDir);
  // strcat(pathToReversedDir, pathBeforeLastDir);
  // strcat(pathToReversedDir, lastNameDir);

  printf("pathToReversedDir: ");
  printPathToDir(pathToReversedDir);

  /*
  struct stat st = {0};
  if (stat(pathToReversedDir, &st) == -1) {
    mkdir(pathToReversedDir, S_IRWXU | S_IRWXO);
  }
  */

  DIR *d;
  struct dirent *entry;
  d = opendir(pathToDir);
  if (d) {
    while ((entry = readdir(d)) != NULL) {

      if (entry->d_type == DT_REG) {
        
        char *pathWithReversedName =
            calloc(bufferSize,
                   sizeof(char));
        //printPathToDir(pathToReversedDir);

        for(int i = 0; i < lengthOfPathInSymbols; i++) {
          pathWithReversedName[i] = pathToReversedDir[i];
        }
        printPathToDir(pathWithReversedName);   
        //
        for(int i = strlen(pathToReversedDir); i < lengthOfPathInSymbols + strlen(pathToReversedDir); i++) {
          pathWithReversedName[i] = pathToReversedDir[i]; 
        }

//        strcat(pathWithReversedName, pathToReversedDir);
   //     strcat(pathWithReversedName, "/");
     //   strcat(pathWithReversedName, entry->d_name);

       printPathToDir(pathWithReversedName);
      }
    }
    closedir(d);
  }

  free(pathBeforeLastDir);
  free(pathToReversedDir);
  free(lastNameDir);
}

