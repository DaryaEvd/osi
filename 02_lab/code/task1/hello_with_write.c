#include <unistd.h>

void print_hello(void) {
  write(1, "hello world!!!\n", 15);
}

int main() {
  print_hello();
 	return 0;
}
