#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /*
    头文件： #include <sys/types.h>、#include <signal.h>
    函数：
        int kill(pid_t pid, int signum);
    功能：
        给  "指定进程"  发送信号。
    参数：
       pid：
       signum：信号的编号
    返回值：
       成功返回 0，失败返回 -1

    pid  的取值有 4 种情况: 
      pid>0:  将信号传送给进程 ID 为 pid 的进程。
      pid=0:  将信号传送给当前进程 "所在进程组" 中的所有进程。
      pid=-1: 将信号传送给系统内所有的进程。
      pid<-1: 将信号传给 "指定进程组" 的 "所有进程"，这个进程组号等于 pid 的绝对值。
    */

   pid_t pid;
   pid = fork();
   if(pid < 0)
   {
       perror("fail to fork");
       exit(1);
   }
   else if(pid > 0)
   {
        while(1)
        {
            printf("This is parent process\n");
            sleep(1);
        }
   }
   else
   {
      printf("This is son process\n");

      //子进程在3秒后,让父进程退出
      sleep(3);

      //使用kill给父进程发送信号，父进程接收到信号后,父进程直接退出
      kill(getppid(),SIGINT);
   }

    return 0;
}