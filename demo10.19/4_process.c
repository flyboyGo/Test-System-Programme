#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd;
    fd = open("file.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("fail to open");
        return -1;
    }

    //BSS(Block Started by Symbol)通常是指用来存放程序中未初始化的全局变量和静态变量的一块内存区域。
    //特点是:可读写的,在程序执行之前BSS段会自动清0。所以,未初始的全局变量在程序执行之前已经成0了。
    
    //数据段包括初始化的数据和未初始化的数据(BSS)两部分
    //BSS段存放的是未初始化的全局变量和静态变量。

    //子进程会继承父进程的一些公有的区域，例如：磁盘空间，内核空间
    //文件描述符的偏移量保存在内核空间中，所以父进程改变偏移量，则子进程获取的偏移量是改变之后的
    pid_t pid;
    pid = fork();
    if(pid <0)
    {
        perror("fail to fork");
        return -1;
    }
    else if(pid > 0) //返回的是子进程的进程号 但是 是 "父进程" 的代码区
    {
        printf("This is a parent process\n");

        char buf[32] = "";
        if(read(fd, buf, 30) == -1)
        {
            perror("fail to read");
            return -1;
        }

        printf("buf = [%s]\n", buf);

    }
    else //pid == 0 子进程的代码区
    {
        sleep(1);
        printf("This is a son process\n");
        
        char buf[32] = "";
        if(read(fd, buf, 30) == -1)
        {
            perror("fail to read");
            return -1;
        }

        printf("buf = [%s]\n", buf);
    }

    while(1);

    return 0;
}