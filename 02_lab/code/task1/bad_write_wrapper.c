#include <sys/syscall.h>
#include <unistd.h>

/*
http://bricktou.cn/fs/read_writeksys_write_en.html
realisation of ksys_write: (from line 626)
https://elixir.bootlin.com/linux/latest/source/fs/read_write.c#L626
*/

/*
write in termianl-chik
'sudo grep sys_write /proc/kallsyms'
to get address of 'ksys_write':
ffffffffb25852a0 - это адрес, где находится ksys_write
*/

/*
создаем тип 'ksys_write_type', который является указателем на функцию,
которая принимает fildes, buf, nbytes
*/
typedef ssize_t (*ksys_write_type)(unsigned int fildes,
                                   const void *buf, size_t nbytes);

int main(void) {
  /*
  создаем переменную ksys_write типа ksys_write_type и кладем туда
  адрес ffffffffb25852a0
  */
  ksys_write_type ksys_write = (ksys_write_type)0xffffffffb25852a0;

  int ret = ksys_write(10, "hello mir! privet planeta!!\n", 20);
}

/*
когда запустим эту программу, то получим по носу- будет segfault, 
потому что мы не можем напрямую достучаться до этого адреса.

А почему? Наверн, потому что нет прав. 
*/