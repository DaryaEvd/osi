#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// //export MY_PERSONAL_AGE=20
// //echo $MY_PERSONAL_AGE

int main(int argc, char **argv, char **envp) {
  if (argc == 3 && setenv(argv[1], argv[2], 1) != 0) {
    /*
     The  setenv()  function adds the variable name to the environment with the value
       value, if name does not already exist.  If name does exist in  the  environment,
       then  its  value  is  changed  to value if overwrite is nonzero; if overwrite is
       zero, then the value of name is not changed (and setenv() returns a success sta‐
       tus).   This  function  makes copies of the strings pointed to by name and value
       (by contrast with putenv(3)).

    */
    perror("setenv()");
    return 0;
  }
  printf("env var's value: %s\n", getenv(argv[1]));
  /*
    getenv возвращает указатель на строку переменной окружения (при успехе)
    в противном случае - NULL
  */

  if (setenv(argv[1], "5", 1) != 0) {
    perror("setenv()");
    exit(EXIT_FAILURE);
  }
  printf("new env var's value: %s\n", getenv(argv[1]));
  return 0;
}

/*
Environment variables set with the setenv() function will only
exist for the life of the program, and are not saved before program
termination.
*/
