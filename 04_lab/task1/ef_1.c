#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const int sizeBuffer = 100;
  // i
  char *buffer = calloc(sizeBuffer, sizeof(char));
  if(!buffer) {
    return 0;
  }

  // ii
  strcpy(buffer, "hello my hoooome");

  // iii
  printf("%s\n", buffer); // prints 'hello my hoooome'

  // iv
  free(buffer);

  // v
  printf("%s\n", buffer); // prints empty string
  // то, что мы освободили данные в куче, асболютно не значит
  // что мы не можем к ней обращаться 
  
  // vi
  char *newBuffer = calloc(sizeBuffer, sizeof(char));
  
  // vii
  strcpy(newBuffer, "My cat is fat :)");

  // viii
  printf("%s\n", newBuffer); //prints 'My cat is fat :)'

  // ix
  char *pointer = &newBuffer[sizeBuffer / 2];

  // x 
  free(&newBuffer[sizeBuffer / 2]);

  // xi
  printf("%s\n", newBuffer);

  return 0;
}
