#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    //如果要实现输出重定向的功能
    //首先如printf函数是操作文件描述符1所对应的文件，
    //默认是操作终端，只要能够把1对应标识的文件改变，就可以实现重定向
    //所以实现创建好文件对应的文件描述符之后,将1文件描述符关闭,接着通过dup
    //函数复制的新的文件描述符就是1,这样printf函数对1操作,就写入到文件中了

    //案例二：实现输出重定向的功能
    int fd_file;
    fd_file = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd_file == -1)
    {
        perror("fail to open");
        exit(1);
    }

    //关闭标准输出文件描述符
    close(1);

    //此时dup复制fd_file对应的文件描述符，由于1对应的文件描述符以关闭,因此此时返回的文件描述符是最小的1
    int fd = dup(fd_file);
    printf("hello world\n");
    printf("fd = %d\n", fd);


    return 0;
}