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

    //读写段都存在，只读不写
    //如果原本管道中有数据，正常读取
    //如果管道中没有数据，则read函数会阻塞等待
    int fd;
    //如何保证读写段都存在,open函数的第二个参数的打开方式
    if((fd = open("myfifo", O_RDWR)) == -1)
    {
        perror("fail to open");
        exit(1);
    }

    write(fd, "hello world", 11);

    char buf[128] = "";
    read(fd, buf, sizeof(buf));
    printf("buf = %s\n", buf);

    read(fd, buf, sizeof(buf));
    printf("buf = %s\n", buf);

    return 0;
}