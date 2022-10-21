#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /*
     进程接收到信号后的处理方式：
       1、执行系统默认动作
       2、忽略此信号
       3、执行自定义信号处理函数
    程序中可用函数 signal()改变信号的处理方式。

    头文件：
        #include <signal.h>
    函数：
        typedef void (*sighandler_t)(int)；
        sighandler_t signal(int signum,sighandler_t handler);
        //全写
        void (*signal(int sig, void (*func)(int)))(int);
    功能：
        注册信号处理函数（不可用于 SIGKILL、SIGSTOP 信号），即确定收到信号后处理函数的入口地址。
    参数：
        signum ：信号编号
        handler  的取值：
            忽略该信号：SIG_IGN
            执行系统默认动作：SIG_DFL
            自定义信号处理函数：信号处理函数名
    返回值：
        成功：返回函数地址，该地址为此信号 "上一次注册的信号处理函数的地址"。
        失败：返回 SIG_ERR
    */

//声明函数
void handler(int sig);

   //以默认的方式处理信号
#if 0
     if(signal(SIGINT, SIG_DFL) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGTSTP, SIG_DFL) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
#endif

   //以忽略的方式处理信号
#if 0
     if(signal(SIGINT, SIG_IGN) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGTSTP, SIG_IGN) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
#endif

   //以自定义的方式处理信号
#if 1
     if(signal(SIGINT, handler) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGQUIT, handler) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
     if(signal(SIGTSTP, handler) == SIG_ERR)
     {
          perror("fail to signal");
          exit(1);
     }
#endif
      
    //注意：SIGKILL和SIGSTOP这两个信号只能以默认的方式处理，不能忽略或者捕捉(自定义处理)

     while(1)
     {
         printf("hello world\n");
         sleep(1);
     }

    return 0;
}

void handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("SIGINT 正在处理\n");
        exit(1);
    }
    if(sig == SIGQUIT)
    {
        printf("SIGQUIT 正在处理\n");
        exit(1);
    }
    if(sig == SIGTSTP)
    {
        printf("SIGTSTP 正在处理\n");
        exit(1);
    }
    
}

