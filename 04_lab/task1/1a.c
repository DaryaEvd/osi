#include <stdio.h>
#include <stdlib.h>

void function() {
  // i
  int localVarInit = 5;
  printf("local initialized: \t 0x%p (%d)\n", &localVarInit, localVarInit);

  int localVarNotInit;
  printf("local not init: \t 0x%p (%d)\n", &localVarNotInit, localVarNotInit);

  char *localCharArray = "Hello from local";
  printf("local char arr: \t 0x%p (%s)\n", &localCharArray, localCharArray);

  // ii
  static int staticInit = 1;
  printf("static int init: \t 0x%p (%d)\n", &staticInit, staticInit);

  static int staticNotInit;
  printf("static in not init: \t 0x%p (%d)\n", &staticNotInit, staticNotInit);

  static char *staticChar = "Hello from static char";
  printf("static char arr: \t 0x%p (%s)\n", &staticChar, staticChar);

  // iii
  const int myConst = 78;
  printf("const int: \t\t 0x%p (%d)\n", &myConst, myConst);

  const char *constChar = "h e l l o   m y  c o n s t n";
  printf("const char arr: \t 0x%p (%s)\n", &constChar, constChar);
  
}

int main(void) {

  printf("function():: \t\t 0x%p\n", function);
  function();

  return 0;
}