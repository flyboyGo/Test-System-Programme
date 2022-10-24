#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FIFONAME "fifo_file"
int main(int argc, char const * argv[])
{
    //由于有名管道在本地创建了一个管道文件，所以系统调用的IO函数基本都可以对有名管道进行操作
    //但是不能使用lseek修改管道文件的偏移量(无名管道也是)
    //注意：有名管道创建的本地文件只是起到标识作用,真正有名管道的实现进程间通信还是在内核空间开辟内存，
    //所以本地产生的文件只是一个标识，没有其他作用，对本地管道文件的操作实质就是对内核空间的操作

    //通过mkfifo函数创建有名管道
   if(mkfifo(FIFONAME, 0664) == -1)
   {
       if(errno  != EEXIST)
       {
            perror("fail to fifo");
            exit(1);
       }
   }

   //对有名管道进行操作
   //管道后写入的数据会保存在之前写入的数据之前，不会替换；如果管道中没有数据，read操作会阻塞

   //通过open函数打开管道文件,得到文件描述符
   int fd;
   fd = open(FIFONAME, O_RDWR);
   if(fd == -1)
   {
       perror("fail to open");
       exit(1);
   }

   //通过write函数向管道文件中写入数据
   if(write(fd, "hello world", strlen("hello world")) == -1)
   {
       perror("fail to write");
       exit(1);
   }

   write(fd, " flight again", strlen(" flight again"));

   //通过read函数读取管道文件中的数据
   char buf[32] = "";
   if(read(fd, buf, sizeof(buf)) == -1)
   {
       perror("fail to read");
       exit(1);
   }

   printf("buf = [%s]\n", buf);

    if(read(fd, buf, sizeof(buf)) == -1)
   {
       perror("fail to read");
       exit(1);
   }

   printf("buf = [%s]\n", buf);

   //使用clsoe函数关闭文件描述符
   close(fd);

    return 0;
}