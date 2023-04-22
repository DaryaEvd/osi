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
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void printDirPath(const char *str, int length) {
  for (int i = 0; i < length; i++) {
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
  for (int i = lengthStartDir - 1; i >= 0; i--) {
    if (startDirPath[i] == '/') {
      break;
    }
    amountSymbLastDir++;
  }
  printf("amountSymbLastDir: %d\n", amountSymbLastDir);

  char *beforeLastDir =
      calloc(lengthStartDir - amountSymbLastDir + 1, sizeof(char));
  int lengthBeforeLastDir = countStringLength(beforeLastDir);
  memcpy(beforeLastDir, startDirPath,
         lengthStartDir - amountSymbLastDir);
  printf("before last dir: ");
  printDirPath(beforeLastDir, lengthStartDir);

  char *nameReversedLastDir =
      calloc(amountSymbLastDir + 1, sizeof(char));
  for (int i = 0; i < amountSymbLastDir; i++) {
    nameReversedLastDir[i] = startDirPath[lengthStartDir - i - 1];
   printf("iter %d, symb: %s\n", i, &nameReversedLastDir[i]);
  }

  // char *reversedLastDir = calloc()
  strcat(endDirPath, beforeLastDir);
  strcat(endDirPath, nameReversedLastDir);
  strcat(endDirPath, "/");
  printf("path for reversed dir: ");
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

        char *inputFilePath = calloc(
            1 + lengthStartDir + lengthRegFileCurr, sizeof(char));

        // strcat(inputFilePath, endDirPath);
        // strcat(inputFilePath, "/");

        char *reversedFileNameCurr =
            calloc(lengthRegFileCurr + 1, sizeof(char));

        for (int i = 0; i < lengthRegFileCurr; i++) {
          reversedFileNameCurr[i] =
              entry->d_name[lengthRegFileCurr - i - 1];
          // printf("iter %d, symb: %s\n", i,
          // &reversedFileNameCurr[i]);
        }

        // strcat(inputFilePath, entry->d_name);

        strcat(inputFilePath, startDirPath);
        strcat(inputFilePath, "/");
        strcat(inputFilePath, entry->d_name);

        printf("path for input file: ");
        printDirPath(inputFilePath,
                     1 + lengthStartDir + lengthRegFileCurr);

        char *outputFilePath =
            calloc(lengthRegFileCurr + 1, sizeof(char));

        strcat(outputFilePath, endDirPath);
        strcat(outputFilePath, reversedFileNameCurr);

        printf("path for output file: ");
       printDirPath(outputFilePath,
                    1 + lengthStartDir + lengthRegFileCurr);

        FILE *input = fopen(inputFilePath, "r");
        if(!input) {
          printf("can't open file: ");
        }
 
    
        FILE *output = fopen(outputFilePath, "w");
        if (input == NULL) {
          printf("can't open file: ");
          printDirPath(inputFilePath, 1 + lengthStartDir + lengthRegFileCurr);
          return 0;
        }
        if(output == NULL) {
          printf("can't open file: ");
          printDirPath(outputFilePath, 1 + lengthStartDir + lengthRegFileCurr);
          return 0;
        } 
    
        printf("reading file ... \n");
        fseek(input, 0, SEEK_END);
        int sizeFile = ftell(input);
        int idx = 0;
        while(idx < sizeFile) {
          fseek(input, -idx, SEEK_END);
          char symb = fgetc(input);
          fprintf(output, "%c", symb);
          idx++;
        }

        fclose(input);
        fclose(output);


        free(inputFilePath);
        free(reversedFileNameCurr);
        free(outputFilePath);
      }
    }
    closedir(d);
  }
  
  free(beforeLastDir);
  free(nameReversedLastDir);
  free(endDirPath);

  return 0;
}
