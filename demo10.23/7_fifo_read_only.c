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

    //在一个进程中,只有读端，没有写端
    //会在open函数的位置阻塞

    int fd;
    if((fd = open("myfifo", O_RDONLY)) == -1)
    {
        perror("fail to open");
        exit(1);
    }

    printf("----------------------\n");

    char buf[128] = "";
    ssize_t bytes;
    while (1)
    {
        if((bytes = read(fd, buf, sizeof(buf))) == -1)
         { 
                perror("fail to read");
                exit(1);
         }

         printf("bytes = %ld\n", bytes);
         printf("bytes = %s\n", buf);   
    }

    return 0;
}