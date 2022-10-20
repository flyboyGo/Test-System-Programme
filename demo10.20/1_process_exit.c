#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void myfun()
{
    printf("nihao beijing\n");

    //使用return
    //return除了可以返回值以外，在主函数中使用可以退出进程，但是在子函数中使用，只是退出当前函数
    //return ;

    //使用exit
    //exit可以退出进程，可以刷新缓冲区
    //exit(0);

    //使用_exit
    //exit可以退出进程，但是不会刷新缓冲区
    _exit(0);

    printf("welcome to 1000phone\n");
}

int main(int argc, char const *argv[])
{
    /*
        在linux  下可以通过以下方式结束正在运行的进程：结束进程执行
        头文件：
             #include <stdlib.h>
        函数：     
             void exit(int value)
        参数：
            status：返回给父进程的参数(低 8 位有效)，父进程通过wait函数接收这个状态，
                    一般失败退出设置为非0，一般成功退出设置为0
        返回值：
             无         


        头文件：
             #include <unistd.h>
        函数：     
             void _exit(int value)
        参数：
             status：返回给父进程的参数(低 8 位有效)，父进程通过wait函数接收这个状态，
                    一般失败退出设置为非0，一般成功退出设置为0


        exit与_exit函数的区别：
           exit 为库函数，而_exit 为系统调用
           exit会刷新缓冲区，但是_exit不会刷新缓冲区

    */

   printf("hello world\n");

   myfun();

   printf("hello kitty\n");

    return 0;
}