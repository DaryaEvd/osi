#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SLASH 1

int checkIsDir(const char *name) {
  DIR *entry = opendir(name);
  if (entry != NULL) {
    closedir(entry);
    return 1; // entry is a real entry
  }
  return 0; // entry doesn't exist
}

void checkLastSym(const char *startDirPath) {
  // printf("last sym is: %c\n", startDirPath[strlen(startDirPath)]);
  // printf("last sym is: %c\n", startDirPath[strlen(startDirPath) - 1]);
  if(startDirPath[strlen(startDirPath) - 1] == '/') {
    printf("It ends with slash\n");
  }
  for (int i = strlen(startDirPath) - 1; i > 0; i--) {
    printf("iter %d, sym %c \n", i, startDirPath[i]);
    // if(startDirPath[strlen(startDirPath - 1)] == '/') {
    //   printf("It ends with slash\n");
    // }
  }
}

int countStringLength(const char *str) {
  int length = strlen(str);
  if (str[length - 1] == '/') {
    length--;
  }
  return length;
}

void printDirPath(const char *str, const int length) {
  for (int i = 0; i < length; i++) {
    printf("%c ", str[i]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  // works without '/' at the end
  if (argc != 2) {
    printf("Error! No path of entered path\n");
    return 0;
  }

  char *startDirPath = argv[1];
  if (!checkIsDir(startDirPath)) {
    printf("Error! Dir by this name: '%s' doesn't exist!\n",
           startDirPath);
    return 0;
  }
  printf("Entered starting entry is: '%s'\n", startDirPath);

  // int isLastSymSlash = checkLastSym(startDirPath);
  checkLastSym(startDirPath);

  int lengthStartDir = countStringLength(startDirPath);

  char *endDirPath = calloc(lengthStartDir + SLASH + 1, sizeof(char));
  if (!endDirPath) {
    return 0;
  }

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
  memcpy(beforeLastDir, startDirPath,
         lengthStartDir - amountSymbLastDir);
  printf("before last dir: ");
  // printDirPath(beforeLastDir, lengthStartDir);

  char *nameReversedLastDir =
      calloc(amountSymbLastDir + 1, sizeof(char));
  for (int i = 0; i < amountSymbLastDir; i++) {
    nameReversedLastDir[i] = startDirPath[lengthStartDir - i - 1];
    printf("iter %d, symb: %s\n", i, &nameReversedLastDir[i]);
  }

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
        printf("curr file name is: ");
        for (int i = 0; i < strlen(entry->d_name); i++) {
          printf("%c", entry->d_name[i]);
        }
        printf("\n");

        int lengthRegFileCurr = countStringLength(entry->d_name);

        char *inputFilePath =
            calloc(1 + SLASH + lengthStartDir + lengthRegFileCurr,
                   sizeof(char));

        char *reversedFileNameCurr =
            calloc(lengthRegFileCurr + 1, sizeof(char));

        for (int i = 0; i < lengthRegFileCurr; i++) {
          reversedFileNameCurr[i] =
              entry->d_name[lengthRegFileCurr - i - 1];
          printf("iter %d, symb: %s\n", i, &reversedFileNameCurr[i]);
        }

        strcat(inputFilePath, startDirPath);
        strcat(inputFilePath, "/");
        strcat(inputFilePath, entry->d_name);

        printf("path for input file: ");
        printDirPath(inputFilePath,
                     1 + lengthStartDir + lengthRegFileCurr);

        char *outputFilePath =
            calloc(lengthStartDir + lengthRegFileCurr + SLASH + 1,
                   sizeof(char)); // for slash
        strcat(outputFilePath, endDirPath);
        strcat(outputFilePath, reversedFileNameCurr);

        printf("path for output file: ");
        printDirPath(outputFilePath,
                     1 + lengthStartDir + lengthRegFileCurr);

        FILE *input = fopen(inputFilePath, "r");
        if (input == NULL) {
          printf("can't open input file: ");
          printDirPath(inputFilePath,
                       1 + lengthStartDir + lengthRegFileCurr);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(endDirPath);
          free(reversedFileNameCurr);
          free(outputFilePath);
          return 0;
        }

        FILE *output = fopen(outputFilePath, "w");
        if (output == NULL) {
          printf("can't open output file: ");
          printDirPath(outputFilePath,
                       1 + lengthStartDir + lengthRegFileCurr);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(endDirPath);
          free(reversedFileNameCurr);
          free(outputFilePath);
          return 0;
        }

        printf("reading file ... \n");
        printDirPath(inputFilePath,
                     1 + lengthStartDir + lengthRegFileCurr);

        fseek(input, 0L, SEEK_END);

        int sizeFile = ftell(input) - 1;
        printf("size file is: %d\n", sizeFile);

        while (sizeFile >= 0L) {
          fseek(input, sizeFile, SEEK_SET);
          char symb = fgetc(input);
          printf("symb is: %c\n", symb);
          fputc(symb, output);
          sizeFile--;
        }

        fclose(input);
        fclose(output);

        free(inputFilePath);
        free(reversedFileNameCurr);
        free(outputFilePath);
      }
    }
  }
  closedir(d);
  free(beforeLastDir);
  free(nameReversedLastDir);
  free(endDirPath);

  return 0;
}
