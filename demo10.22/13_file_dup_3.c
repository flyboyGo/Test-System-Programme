#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    //案例三：实现输出重定向后，还想标准输出，如何实现
    int fd1;
    int fd2;
    fd2 = dup(1);//save stdout
    printf("new:fd2=%d\n",fd2);

    fd1 = open("test.txt", O_CREAT|O_RDWR, S_IRWXU);

    close(1);
    int fd3 = dup(fd1);
    printf("hello world\n");
    printf("fd = %d\n", fd3);


    close(1);
    int fd4 = dup(fd2);
    printf("i love you \n");
    printf("fd = %d\n", fd4);

    return 0;
}