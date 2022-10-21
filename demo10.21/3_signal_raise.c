#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /*
    头文件： #include <signal.h>
    函数：  int raise(int signum);
    功能：  给调用进程本身发送一个信号。
    参数：  signum：信号的编号。
    返回值： 成功返回 0，失败返回 -1。
    */

   int num = 0;
   while(1)
   {
       printf("hello wolrd\n");
       sleep(1);
       num++;

       //当循环执行5秒后,进程退出
       if(num == 5)
       {
          //使用raise给当前进程本身发送信号
          raise(SIGINT);
          //raise(SIGALRM);
          //kill(getpid(),SIGINT);
       }
   }

    return 0;
}