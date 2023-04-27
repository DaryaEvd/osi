#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const int sizeBuffer = 100;
  // i
  char *buffer = calloc(sizeBuffer, sizeof(char));
  if(!buffer) {
    return 0;
  }

  // ii
  buffer = "hello my world\n"; 

  // iii
  for(int i = 0; i <sizeBuffer; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");

  // iv
  free(buffer);

  // v
  for(int i = 0; i <sizeBuffer; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");

  // vi
  char *newBuffer = calloc(sizeBuffer, sizeof(char));
  
  // vii
  newBuffer = "Hello new buffer\n";  

  // viii
 for(int i = 0; i <sizeBuffer; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");

  // ix
  char *pointer = &newBuffer[sizeBuffer / 2];

  // x 
  free(&newBuffer[sizeBuffer / 2]);

  // xi
  for(int i = 0; i <sizeBuffer; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");

  return 0;
}