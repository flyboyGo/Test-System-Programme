#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <sys/types.h>   #include <sys/stat.h>
    函数：  int mkfifo(const char *pathname, mode_t mode);
    功能：创建一个有名管道，产生一个 "本地文件系统可见" 的文件pathname
    参数：
         pathname：有名管道创建后生成的文件，可以带路径
         mode：管道文件的权限，一般通过八进制数设置即可，例如0664
    返回值：成功：0   失败：‐1  错误保存在errno中
    */

   //通过mkfifo函数创建有名管道
   if(mkfifo("fifo_file", 0664) == -1)
   {
       //如果管道文件存在，不需要报错退出,直接使用即可，所以需要在错误输出之前把因为文件存在的错误排除
       if(errno  != EEXIST)
       {
            perror("fail to fifo");
            exit(1);
       }
   }

    return 0;
}