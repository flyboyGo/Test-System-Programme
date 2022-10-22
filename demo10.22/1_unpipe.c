/*
无名管道的创建 pipe  函数
头文件：
     #include <unistd.h>
函数：
     int pipe(int filedes[2]);
功能：创建一个无名管道，返回两个文件描述符负责对管道进行读写操作
参数：
     filedes 为 int 型数组的首地址，其存放了管道的文件描述符 fd[0]、fd[1]。
     filedes[0]为 读 而打开，filedes[1]为 写 而打开管道，filedes[0]的输出是 filedes[1]的输入。
返回值：
      成功：返回 0
      失败：返回-1
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //使用pipe创建一个无名管道
    int fd_pipe[2];

    if(pipe(fd_pipe) == -1)
    {
        perror("fail to pipe");
        exit(1);
    }

    printf("fd_pipe[0] = %d\n", fd_pipe[0]);
    printf("fd_pipe[1] = %d\n", fd_pipe[1]);

    //对无名管道执行读写操作
    //由于无名管道给当前用户进程两个文件描述符，所以只要操作这两个文件描述符,
    //就可以通过文件的IO中的read和write函数对无名管道进行操作

    //通过write函数向无名管道中写入数据
    //fd_pipe[1]负责执行写操作
    //如果管道中有数据，再次写入的数据放在之前的数据前面，不会把之前的数据替换
    //读取数据时，直接从管道中读取指定个数的数据，如果管道中没有数据，则read函数会阻塞等待
    if(write(fd_pipe[1], "hello wolrd", 12) == -1)
    {
        perror("fail to write");
        exit(1);
    }

    write(fd_pipe[1], "flig\0t again", strlen("flight again") + 1);

    //通过read函数从无名管道中读取数据
    //fd_pipe[0]负责执行读操作
    char buf[32] = "";
    ssize_t bytes;
    if((bytes = read(fd_pipe[0], buf, 20)) == -1)
    {
        perror("fail to read");
        exit(1);
    }
    printf("buf = [%s]\n", buf);
    printf("size = %ld\n", strlen(buf)); // 15
    printf("bytes = %ld\n", bytes); // 20


    bytes = read(fd_pipe[0], buf, sizeof(buf));
    printf("buf = [%s]\n", buf);
    printf("bytes = %ld\n", bytes); //4

    //如果再次读操作,管道中没有数据，则read函数会阻塞等待
    // bytes = read(fd_pipe[0], buf, sizeof(buf));
    // printf("buf = [%s]\n", buf);
    // printf("bytes = %ld\n", bytes);

    return 0;
}