#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    /*
    头文件：#include  <unistd.h>
    函数：int dup(int  oldfd)
    功能：
        复制 oldfd 文件描述符,并分配一个新的文件描述符,新的文件描述符是调用进程文件描述符表中最小可用的文件描述符。
    参数：
        要复制的文件描述符 oldfd。
    返回值：
       成功：新文件描述符。
       失败：返回－1，错误代码存于 errno 中。
    */

   //案例一：使用dup函数复制文件描述符

   //通过dup函数复制一个文件描述符
   int fd;
   //dup执行后给返回值的文件描述符分配的值是文件描述符表中的最小可用的文件描述符
   fd = dup(1);
   printf("fd = %d\n", fd);

   //由于通过dup函数将1这个文件描述符复制了一个fd，所以fd现在就相当于1,所以写数据就是向终端写数据
   write(fd, "hello world\n", strlen("hello world\n"));

    return 0;
}