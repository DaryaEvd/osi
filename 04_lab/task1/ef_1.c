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

/* TODO: 
Что просиходит, когда вызывается free?

1 and 2 - дополнительная инфа
про block
                         2
|...| ................ |...|.
  1        block               

1- save here a pointer to 2nd 
2 - save here a pointer to the 1st 

Поэтому когда передаем указатель на 1, то 
мы щнаем, где заканчивается текущий блок 
и где начинается следующий

Так же в доп инфе есть инфа о том, занят ли блок
или свободен 
И если следующий блок свободен, то его можно объединить
стекущим - уменьшим фрагментацию

Во free надо передавать указатель, который нам вернул malloc 

Если malloc вернул указатель вот сюда
  ||
  ||
  \/
|block|block|block|

(типа на 1й блок free полуичил указатель)

Тогда что произойдет при free? 
Указатель сдивнется влево для того, чтоб узнать доп инфу про блок:
зарезервирован ли блок и где следующий
*/
