#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//有名管道是实现进程通信
//由于有名管道在本地创建了一个管道文件，所以不相关的进程之间也可以实现通信

int main(int argc, char const * argv[])
{

    //如果没有创建有名管道，则创建有名管道
    //为了实现两个进程都可以收发数据，所以需要创建两个有名管道

    if(mkfifo("myfifo1", 0664) == -1)
    {
        if(errno != EEXIST)
        {
            perror("fail to mkfifo");
            exit(1);
        }
    }
    if(mkfifo("myfifo2", 0664) == -1)
    {
        if(errno != EEXIST)
        {
            perror("fail to mkfifo");
            exit(1);
        }
    }

    //打开两个两个有名管道并得到文件描述符
    int fd_w, fd_r;
    if((fd_r = open("myfifo1", O_RDONLY)) == -1)
    {
        perror("fail to open");
        exit(1);
    }
    if((fd_w = open("myfifo2", O_WRONLY)) == -1)
    {
        perror("fail to open");
        exit(1);
    }

    char buf[128] = "";
    ssize_t bytes;
    while(1)
    {
        if((bytes = read(fd_r, buf, sizeof(buf))) == -1)
        {
            perror("fail to read");
            exit(1);
        }

        printf("from send : %s\n", buf);

        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';

        write(fd_w, buf, sizeof(buf));
    }

    return 0;
}