#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int checkIsDir(const char *name) {
  DIR *entry = opendir(name);
  if (entry != NULL) {
    closedir(entry);
    return 1; // entry is a real entry
  }
  // closedir(entry);
  return 0; // entry doesn't exist
}

int countStringLength(const char *str) {
  int length = 0;
  while(str[length] != '\0') {
    length++;
  }
  return length;
}

void printDirPath(const char *str, int length) {
  for(int i = 0; i < length; i++) {
    printf("%c ", str[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error! No path of entered\n");
    return 0;
  }

  char *startDirPath = argv[1];
    if (!checkIsDir(startDirPath)) {  
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           startDirPath);
    return 0;
  }
  printf("Entered starting entry is: '%s'\n", startDirPath);

  int lengthStartDir = countStringLength(startDirPath);

  char *endDirPath = calloc(lengthStartDir + 1, sizeof(char));

  printf("strlen start path: %ld\n", strlen(startDirPath));
  printf("length start dir: %d\n", lengthStartDir);
  printf("strlen End path: %ld\n", strlen(endDirPath));

  int amountSymbLastDir = 0;
  for(int i = lengthStartDir - 1; i >= 0; i--) {
    if(startDirPath[i] == '/') {
      break;
    }
    amountSymbLastDir++;
  }
  printf("amountSymbLastDir: %d\n", amountSymbLastDir);

  memcpy(endDirPath, startDirPath, lengthStartDir - amountSymbLastDir);
  printDirPath(endDirPath, lengthStartDir);

  char *nameReversedLastDir = calloc(amountSymbLastDir + 1, sizeof(char));
  for(int i = 0; i < amountSymbLastDir; i++) {
    nameReversedLastDir[i] = startDirPath[lengthStartDir - i - 1];
    //printf("iter %d, symb: %s\n", i, &nameReversedLastDir[i]);    
  }

  // char *reversedLastDir = calloc()
  strcat(endDirPath, nameReversedLastDir);
  printDirPath(endDirPath, lengthStartDir);

  struct stat st = {0};
  if (stat(endDirPath, &st) == -1) {
    mkdir(endDirPath, S_IRWXU | S_IRWXO);
  }

  DIR *d;
  struct dirent *entry;
  d = opendir(startDirPath);
  if (d) {
    while ((entry = readdir(d)) != NULL) {

      if (entry->d_type == DT_REG) {

        int lengthRegFileCurr = countStringLength(entry->d_name);

        char *inputFilePath = calloc(1 +lengthStartDir + lengthRegFileCurr, sizeof(char));

        strcat(inputFilePath, endDirPath);
        strcat(inputFilePath, "/");
        strcat(inputFilePath, entry->d_name);

        printDirPath(inputFilePath, 1 + lengthStartDir + lengthRegFileCurr);


      }
    }
    closedir(d);
  }
  return 0;

}
