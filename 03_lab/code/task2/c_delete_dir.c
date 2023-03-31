#include <stdlib.h>
#include <unistd.h>

/*
PSEUDOCODE from stackoverflow
create a stack to hold directory names.
push argv contents onto the stack
while (stack !empty) {
    look at the top directory name on the stack
    for each item in directory {
        if (item is a directoy) {
            push it onto the stack
        } else {
            delete it
        }
    }
    if (no subdirs were pushed) {
        pop the top dir name from the stack
        delete it
    }
}
*/

int main() {
  size_t nmemb = 100;
  char *stackOfContent = calloc(100, sizeof(char *));

  

  free(stackOfContent);
}