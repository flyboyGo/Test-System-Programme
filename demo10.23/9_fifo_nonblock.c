#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const * argv[])
{
    if(mkfifo("myfifo", 0664) == -1)
    {
        if(errno != EEXIST)
        {
            perror("fail to mkfifo");
            exit(1);
        }
    }

    int fd;

#if 0

    //如果open标志位被设置为非阻塞，并且以只读的方式打开管道文件
    //open函数和read函数都不会阻塞

    fd = open("myfifo", O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
        perror("open fifo");
        exit(1);
    }

    while(1)
    {
        char recv[100];
        bzero(recv, sizeof(recv));
        read(fd, recv, sizeof(recv));
        printf("read from my_fifo buf = [%s]\n", recv);
        sleep(1);
    }

#endif

#if 1

    //如果open标志位被设置为非阻塞，并且以只写的方式打开管道文件
    //open函数会直接报错
    //如果open标志位被设置为可读、可写,那么跟阻塞是一样的效果

    char send[100] = "hello world";

    fd = open("myfifo", O_WRONLY | O_NONBLOCK);
    if(fd < 0)
    {
        perror("open fifo");
        exit(1);
    }

    write(fd, send, strlen(send));
    printf("write to my_fifo buf = %s\n", send);

    char recv[100];
    read(fd, recv, sizeof(recv));
    printf("read from my_fifo buf=[%s]\n", recv);
#endif

    return 0;
}