#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    //父子进程有时需要简单的进程间同步，如父进程等待子进程的结束。
    //linux下提供了以下两个等待函数  wait() 、 waitpid() 。
    //需要包含头文件：#include <sys/types.h>  #include <sys/wait.h>
    //wait  函数
    //pid_t wait(int *status);

    /*
    功能：
      等待子进程终止，如果子进程终止了，此函数会 "回收子进程的资源"。
      调用 wait 函数的进程会挂起(阻塞)，直到它的 "一个子进程退出" 或收到一个 "不能被忽视的信号" 时才被唤醒。
      若调用进程 "没有子进程" 或 它的 "子进程已经结束" ，该函数立即返回。

    参数：
      函数返回时，参数 status 中包含子进程退出时的状态信息。
      子进程的退出信息在一个 int 中包含了多个字段，用宏定义可以取出其中的每个字段。
      返回值：如果执行成功则返回子进程的进程号；出错返回-1，失败原因存于 errno 中。
    */

    return 0;
}