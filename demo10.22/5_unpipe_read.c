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

    //读写段都存在，只读不写
    //如果管道中有数据,会正常读取数据
    //如果管道中没有数据,则读操作会阻塞等待，直到有数据为止

    write(pipefd[1], "hello world", 11);

    char buf[128] = "";
    if(read(pipefd[0], buf, sizeof(buf)) == 1)
    {
        perror("fail to read");
        exit(1);
    }
    printf("buf = %s\n", buf);


    if(read(pipefd[0], buf, sizeof(buf)) == 1)
    {
        perror("fail to read");
        exit(1);
    }

    printf("buf = %s\n", buf);

    return 0;
}