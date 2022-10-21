#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /* 
    头文件：#include <stdlib.h>
    函数： void abort(void);
    功能： 向进程发送一个 SIGABRT 信号，默认情况下进程会退出。
    注意：
        即使 SIGABRT 信号被加入阻塞集，一旦进程调用了 abort 函数，进程也还是会被终止，
        且在 终止前 会刷新缓冲区、关闭文件描述符。
    */

   //向调用进程发送一个 SIGABRT 信号，默认情况下进程会退出(类似于exit)

   int num = 0;
   while(1)
   {
       printf("hello wolrd\n");
       sleep(1);
       num++;

       //当循环执行5秒后,进程退出
       if(num == 5)
       {
        //向调用进程发送一个 SIGABRT 信号，默认情况下进程会退出
           abort();
       }
   }

    return 0;
}