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

    printf("**********************\n");

    //在一个进程中,只有写端，没有读端
    //会在open函数的位置阻塞

    int fd;
    if((fd = open("myfifo", O_WRONLY)) == -1)
    {
        perror("fail to open");
        exit(1);
    }

    printf("---------------------\n");

    while(1)
    {
        write(fd, "hello world", 11);
        printf("666\n");

        sleep(1);
    }


    //注意！！！！！！！！！！！！！！！！！！！！
    //将7_fifo_read_only.c 和 8_fifo_write_only.c 同时运行，保证有名管道读写端都存在
    //规律：只要保证有名管道的读写端都存在，不管是几个进程,都不会在open函数这里阻塞了
    //如果一个进程只读，一个进程只写，都运行后,如果关闭写端后,读端会返回0
    //如果一个进程只读，一个进程只写，都运行后,如果关闭读端后,写段会立即产生SIGPIPE信号
    //SIGPIPE信号的默认的处理方式是退出进程

    return 0;
}