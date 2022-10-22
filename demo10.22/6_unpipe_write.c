/*
从管道中读数据的特点
   1、默认用 read 函数从管道中读数据是阻塞的。
   2、调用 write 函数向管道里写数据，当缓冲区已满时 write 也会阻塞。
   3、通信过程中，读端口全部关闭后，写进程向管道内写数据时，写进程会（收到 SIGPIPE 信号）退出

    //读写端都存在，只读不写

    //读写端都存在，只写不读

    //只有读端

    //只有写端
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int pipefd[2];
    if(pipe(pipefd) == -1)
    {
        perror("fail to pipe");
        exit(1);
    }

    //读写段都存在，只写不读
    //如果一致执行写操作,则无名管道对应的缓冲区会被写满，写满之后,write函数也会被阻塞等待
    //默认无名管道的默认缓冲区64K字节

    int num = 0;
    while(1)
    {
        if(write(pipefd[1], "1234", 1024) == -1)
        {
            perror("fail to write");
            exit(1);
        }

        num++;
        printf("num = %d\n", num);
    }

    return 0;
}