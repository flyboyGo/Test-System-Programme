/*
      dup2  函数重定向
      头文件：#include  <unistd.h>
      函数：int t dup2(int oldfd, int  newfd)
      功能：
          复制一份打开的文件描述符oldfd,并分配新的文件描述符 newfd，newfd 也标识 oldfd 所标识的文件。
      注意：
          newfd 是小于文件描述符最大允许值的非负整数，如果 newfd 是一个已经打开的文件描述符，
           则首先关闭该文件，然后再复制。
      参数：
          要复制的文件描述符 oldfd
          分配的新的文件描述符 newfd
      返回值：
          成功：返回 newfd
          失败：返回-1，错误代码存于 errno 中
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    //实现输出重定向
#if 0
    int fd1;
    int fd2;

    fd1 = open("test.txt", O_CREAT|O_RDWR, S_IRWXU);
    if(fd1 < 0)
    {
        perror("fail to open");
        exit(1);
    }

    //关闭1标识的文件描述符,然后将fd1复制给1,意味着1和fd1都标识test.txt文件
    fd2 = dup2(fd1, 1);
    printf("hello world\n");
    printf("fd2 = %d\n", fd2);

#endif

    //实现输出重定向后,再恢复标准输出
#if 1

    int fd1;
    printf("%d\n", fd1);
    //如果使用dup2，则需要事先给第二个参数对应的变量赋一个初始值
    int fd2 = 3;

    //将1复制一份为fd2,所以fd2标识的是标准输出
    dup2(1, fd2);
    printf("fd2 = %d\n", fd2);

    fd1 = open("test.txt", O_CREAT | O_RDWR, 0664);

    //输出重定向:关闭文件描述符1,将fd1复制一份为1，所以1此时标识的是test.txt文件
    dup2(fd1, 1);
    printf("hello world\n");

    //再次实现标准输出：关闭文件描述符1,将fd2复制一份为1,所以1此时标识的是标准输出
    dup2(fd2, 1);
    printf("你好北京\n");

#endif

    return 0;
}