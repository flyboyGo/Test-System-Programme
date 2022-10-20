#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /*
    进程的创建 -- vfork  
    函数:
        pid_t vfork(void)
    功能：
        vfork 函数和 fork 函数一样都是在已有的进程中创建一个新的进程，但它们创建的子进程是有区别的。
    返回值:
         创建子进程成功，则在子进程中返回 0,父进程中返回子进程 ID。出错则返回-1。

    fork和vfork  函数的区别：
         vfork 保证子进程先运行，在它调用 exec 或 exit 之后，父进程才可能被调度运行。
         vfork 和 fork 一样都创建一个子进程，但它并不将父进程的地址空间完全复制到子进程中，
         因为子进程会立即调用 exec(或 exit)，于是也就不访问该地址空间。
         相反,在子进程中调用exec或exit之前,它在父进程的地址空间中运行,在exec之后子进程会有自己的进程空间
    总结：
       子进程在父进程之前运行，在子进程调用exec或exit后，父进程才会被调用
       子进程和父进程共享同一块空间     
    */

    return 0;
}