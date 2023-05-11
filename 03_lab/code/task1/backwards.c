#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SLASH 1

int checkIsDir(const char *name) {
  DIR *entry = opendir(name);
  if (entry != NULL) {
    closedir(entry);
    return 1; // entry is a real entry
  }
  return 0; // entry doesn't exist
}

int checkLastSym(const char *startDirPath) {
  if (startDirPath[strlen(startDirPath) - 1] == '/') {
    printf("It ends with slash\n");
    return 1;
  }
  return 0;
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

  int isLastSymSlash = checkLastSym(startDirPath);
  if (isLastSymSlash == 1) {
    startDirPath[strlen(startDirPath) - 1] = '\0';
  }

  int lengthStartDir = countStringLength(startDirPath);

  char *endDirPath = calloc(lengthStartDir + SLASH + 1, sizeof(char));
  if (!endDirPath) {
    return 0;
  } 

  int amountSymbLastDir = 0;
  for (int i = lengthStartDir - 1; i >= 0; i--) {
    if (startDirPath[i] == '/') {
      break;
    }
    amountSymbLastDir++;
  }

  char *beforeLastDir =
      calloc(lengthStartDir - amountSymbLastDir + 1, sizeof(char));
  if (!beforeLastDir) {
    free(endDirPath);
    return 0;
  }
  memcpy(beforeLastDir, startDirPath,
         lengthStartDir - amountSymbLastDir);

  char *nameReversedLastDir =
      calloc(amountSymbLastDir + 1, sizeof(char));
  if (!nameReversedLastDir) {
    free(endDirPath);
    free(beforeLastDir);
    return 0;
  }
  for (int i = 0; i < amountSymbLastDir; i++) {
    nameReversedLastDir[i] = startDirPath[lengthStartDir - i - 1];
  }

  strcat(endDirPath, beforeLastDir);
  strcat(endDirPath, nameReversedLastDir);
  strcat(endDirPath, "/");
  
  struct stat st = {0};
  if(stat(endDirPath, &st) == 0) {
    printf("This folder '%s' already exsists!\n", endDirPath);
    return 0;
  }

  else if (stat(endDirPath, &st) == -1) {
    mkdir(endDirPath, S_IRWXU | S_IRWXO);
  }

  char *buffer = malloc(sizeof(char));

  DIR *d;
  struct dirent *entry;
  d = opendir(startDirPath);
  if (d) {
    while ((entry = readdir(d)) != NULL) {
      if(entry->d_type == DT_DIR) {
        continue;
      }

      if (entry->d_type == DT_REG) {
        // printf("curr file name is: ");
        for (int i = 0; i < strlen(entry->d_name); i++) {
          // printf("%c", entry->d_name[i]);
        }
        // printf("\n");

        int lengthRegFileCurr = countStringLength(entry->d_name);

        char *inputFilePath =
            calloc(1 + SLASH + lengthStartDir + lengthRegFileCurr,
                   sizeof(char));
        if (!inputFilePath) {
          free(endDirPath);
          free(beforeLastDir);
          free(nameReversedLastDir);
          return 0;
        }

        char *reversedFileNameCurr =
            calloc(lengthRegFileCurr + 1, sizeof(char));
        if (!reversedFileNameCurr) {
          free(endDirPath);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(inputFilePath);
          return 0;
        }

        for (int i = 0; i < lengthRegFileCurr; i++) {
          reversedFileNameCurr[i] =
              entry->d_name[lengthRegFileCurr - i - 1];
        }

        strcat(inputFilePath, startDirPath);
        strcat(inputFilePath, "/");
        strcat(inputFilePath, entry->d_name);

        char *outputFilePath =
            calloc(lengthStartDir + lengthRegFileCurr + SLASH + 1,
                   sizeof(char)); // for slash
        if (!outputFilePath) {
          free(endDirPath);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(inputFilePath);
          free(reversedFileNameCurr);
          return 0;
        }

        strcat(outputFilePath, endDirPath);
        strcat(outputFilePath, reversedFileNameCurr);

        int inputFileDescriptor = open(inputFilePath, O_RDONLY);
        if(inputFileDescriptor < 0) {
          printf("File by this path '%s' can't be opened", inputFilePath);
          free(endDirPath);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(inputFilePath);
          free(reversedFileNameCurr);
          return 0;
        }

        int outputFileDescriptor = creat(outputFilePath, 00700);
        if(outputFileDescriptor < 0) {
          printf("Can't create file by this path '%s'", outputFilePath);
          free(endDirPath);
          free(beforeLastDir);
          free(nameReversedLastDir);
          free(inputFilePath);
          free(reversedFileNameCurr);
          return 0;
        }

        /*
        TODO: -почему читать по байтам - это плохо? 
              FIX redaing by bytes !!!!!!!!!!!!
        */
        off_t offset = lseek(inputFileDescriptor, 0L, SEEK_END);
        lseek(inputFileDescriptor, -offset, SEEK_END);


        char *clown = malloc(offset);

        if(read(inputFileDescriptor, clown, offset) == offset) {
          printf("oaoaoao\n");
          write(outputFileDescriptor, clown, offset);
        }

        free(clown);




        // int sizeFile = ftell(outputFileDescriptor);


        // write(outputFileDescriptor, buffer, offset);
        


/*
        while (offset > 0) {
          lseek(inputFileDescriptor, --offset, SEEK_SET);
          ssize_t readCount = read(inputFileDescriptor, buffer, 1); 
          ssize_t writeCount = write(outputFileDescriptor, buffer, readCount);
        }
*/
        close(inputFileDescriptor);
        close(outputFileDescriptor);

        free(inputFilePath); 
        free(reversedFileNameCurr);
        free(outputFilePath);
      }
    }

    free(buffer);
  }

  closedir(d);
  free(beforeLastDir);
  free(nameReversedLastDir);
  free(endDirPath);

  return 0;
}
