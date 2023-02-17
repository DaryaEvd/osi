#include <dlfcn.h>
#include <stdio.h>

void load_lib_and_print_hello(void) {
  //load dynamic library 
  void *lib = dlopen("./libdyn_runtime.so", RTLD_LAZY);
  if(lib == NULL) {
    printf("can't load library: %s\n", dlerror());
    return;
  }

  //searching for address of this func and save it in dyn_print
  void (*dyn_print)(void);
  dyn_print = (void (*)(void)) dlsym(lib, "print_hello_from_dyn_runtime");
  
  char *error;
  if((error = dlerror()) != NULL) {
    printf("dlsym() failes: %s\n", dlerror());
    dlclose(lib);
    return;
  }

  dyn_print();
  dlclose(lib);
}

int main(int argc, char* argv[]) {
  load_lib_and_print_hello();
  
  return 0;
}

/*
-- generate PIC and create dyamic lib
gcc -fPIC -c dyn_run.c
gcc dyn_run.c -o libdyn_run.so -shared

--build program and run
gcc hello.c -o hello -ldl
./hello
*/
