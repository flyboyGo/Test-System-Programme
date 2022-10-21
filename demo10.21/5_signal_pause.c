#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <unistd.h>
    函数：  int pause(void);
    功能：  将调用进程挂起(阻塞)直至捕捉到信号为止。这个函数通常用于判断信号是否已到。
    返回值：直到捕获到信号，pause 函数才返回-1，且 errno 被设置成 EINTR。
    */
   pid_t pid;
   pid = fork();
   if(pid < 0)
   {
        perror("fail to work");
        exit(1);
   }
   else if(pid > 0)
   {
        printf("This is parent process\n");
        //使用pause阻塞调用进程，等待捕捉信号
        pause();
   }
   else
   {
        printf("This is son process\n");

        sleep(3);

        kill(getppid(),SIGINT);
   }


    return 0;
}