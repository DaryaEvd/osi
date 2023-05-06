// https://www.codeguru.com/visual-studio/function-calls-part-3-frame-pointer-and-local-variables/
// https://habr.com/ru/companies/smart_soft/articles/234239/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *badFunction() {
  int localVar = 13;

  int *pointer = &localVar;

  return pointer;
}

/* 
------------------------------------------------

badFunction():
        pushq   %rbp                // добавение адреса возврата в стек
        movq    %rsp, %rbp          // сохранение адреса текущего кадра стека
        movl    $13, -12(%rbp)      // присваиваем localVar-у значение 13
        
        leaq    -12(%rbp), %rax     // загружаем в rax (aka pointer) значение localVar
                  //The instruction LEA reg,addr means 
                  // read the address (not the variable stored at 
                  // the address) into register reg.
        movq    %rax, -8(%rbp)      // присваиваем *pointer значение из rax
        
        movq    -8(%rbp), %rax      // 
        popq    %rbp                // очищаем rbp 
        ret                         // возврат из подпрограммы
.LC0:
        .string "pid: %d\n"
.LC1:
        .string "value in var: %d\n"
.LC2:
        .string "%p\n"
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        call    getpid
        movl    %eax, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf
        call    badFunction()     // помещаем адрес возврата в стек, передаем
                                // управление по метку badFunction
        movq    %rax, -8(%rbp)
        movq    -8(%rbp), %rax
        movl    (%rax), %eax
        movl    %eax, %esi
        movl    $.LC1, %edi
        movl    $0, %eax
        call    printf
        movq    -8(%rbp), %rax
        movq    %rax, %rsi
        movl    $.LC2, %edi
        movl    $0, %eax
        call    printf
        movl    $30, %edi
        call    sleep
        movl    $0, %eax
        leave
        ret
------------------------------------------------


 | pointer --> local var
 | local var 
 | return address 

 | badFunction call  


То есть после выхода из функции BadFunction pointer будет 
указывать на уже освобожденную память, потому что все 
локальные переменные создаются на стеке.
*/ 
 
 int main(void) {
  printf("pid: %d\n", getpid());

  int *addressToGet = badFunction();

  printf("value in var: %d\n", *addressToGet);
  // TODO: почему значение не затерлось ?!??!?!??!?!

  printf("%p\n", addressToGet);

  sleep(30);

  return 0;
}
