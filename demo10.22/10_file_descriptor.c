/*
   文件描述符概述:
   文件描述符是 "非负整数" ，是文件的标识。 用户使用文件描述符（file descriptor）来访问文件。
   利用open打开一个文件时，内核会返回一个文件描述符。
   1、每个进程都有一张文件描述符的表，进程刚被创建时，标准输入、标准输出、标准错误输出设备文件被打开，
      对应的文件描述符0、1、2 记录在表中。
   2、在进程中打开其他文件时,系统会返回文件描述符表中 "最小可用" 的文件描述符,并将此文件描述符记录在表中。

   注意：
   Linux中一个进程最多只能打开NR_OPEN_DEFAULT(即1024)个文件，
   故当文件不再使用时应及时调用close函数关闭文件。
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{

    //在进程中打开其他文件时,
    //系统会返回文件描述符表中 "最小可用" 的文件描述符,
    //并将此文件描述符记录在表中
    //注意：新创建的文件描述符不一定是最大的
#if 0    
    close(0); //关闭输入文件描述符

    int fd1, fd2, fd3;
    fd1 = open("file.txt", O_RDONLY | O_CREAT , 0664);
    fd2 = open("file.txt", O_RDONLY | O_CREAT , 0664);
    fd3 = open("file.txt", O_RDONLY | O_CREAT , 0664);

    printf("fd1 = %d\n", fd1);
    printf("fd1 = %d\n", fd2);
    printf("fd1 = %d\n", fd3);
#endif
    
    //Linux中一个进程最多只能打开NR_OPEN_DEFAULT(即1024)个文件，
    //故当文件不再使用时应及时调用close函数关闭文件

    int fd;
    while(1)
    {
        if((fd = open("file.txt", O_RDONLY | O_CREAT, 0664)) == -1)
        {
               perror("fail to open");
               exit(1);
        }

        printf("fd = %d\n", fd);
    }

    return 0;
}