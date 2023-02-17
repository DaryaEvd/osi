#include <stdio.h>
#include "dynamic_hello.h"

int main() {
  print_hello_dynamic();
  return 0;
}

/*
--create Position Independent Code
gcc -fPIC -c dynamic_hello.c
-why do we use PIC? Ans: Many different programms can use one library and
all these programs locate in different address space. That's why jumps
should use relative addressing, not absolut. So the code that compiler
generates must be independent of addresses.

-dynamic lib is not archive file (like static lib), but real locating program, so compiler itself makes dyn libs.

--create dynamic lib with flag -shared
gcc dynamic_hello.c -o libhello_dynamic.so -shared
-as a result we got libhello_dynamic.so

-- gcc -o hello hello.c
we got hello, which is compiled but not linked, so we get an error
"undefined reference to `print_hello_dynamic'" cause we didn't link to
anything gcc -o hello hello.c

--we should say who we want to compile with
gcc -o hello hello.c -lhello_dynamic -L.

--check that print_hello_dynamic is unresolved (cuase we don't have
realization of this function in final bin) nm ./hello |vim -

--can't run hello
./hello
--if we wanna see dependencies:
ldd ./hello
-we got libhello_dynamic.so => not found

--so we need to use enviromental variable LD_LIBRARY_PATH
LD_LIBRARY_PATH=./ ./hello
now it works correctly
-or-
export LD_LIBRARY_PATH=./
./hello

--see dependencies again after loading enviroment variable:
ldd ./hello
*/
