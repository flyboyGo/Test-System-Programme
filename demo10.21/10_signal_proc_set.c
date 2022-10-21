#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
/*
信号阻塞集(屏蔽集、掩码)
每个进程都有一个阻塞集,它用来描述哪些信号递送到该进程的时候被阻塞
(在信号发生时记住它,直到进程准备好时再将信号通知进程)。

所谓阻塞并不是禁止传送信号, 而是暂缓信号的传送。
若将被阻塞的信号从信号阻塞集中删除,且对应的信号在被阻塞时发生了，进程将会收到相应的信号。   
*/

/*
igprocmask函数  创建一个阻塞集合
头文件：#include <signal.h>
函数：int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
功能：
   检查或修改信号阻塞集，根据 how 指定的方法对进程的阻塞集合进行修改，新的信号阻塞集由 set 指定,
   而原先的信号阻塞集合由 oldset 保存。
参数：
   how：信号阻塞集合的修改方法。
   set：要操作的信号集地址。
   oldset：保存原先信号集地址。

   how：
      SIG_BLOCK：向信号阻塞集合中添加 set 信号集
      SIG_UNBLOCK：从信号阻塞集合中删除 set 集合
      SIG_SETMASK：将信号阻塞集合设为 set 集合
返回值：
    成功：返回 0
    失败：返回 -1

注：若 set 为 NULL，则不改变信号阻塞集合，函数只把当前信号阻塞集合保存到 oldset 中

*/

   int i = 0;

   //创建信号集并信号集中添加信号
   sigset_t set;
   sigemptyset(&set);
   sigaddset(&set, SIGINT);
   while(1)
   {
      //将set信号集 添加到 信号阻塞集中
      sigprocmask(SIG_BLOCK, &set, NULL);
      for(i=0; i<5; i++)
      {
         printf("SIGINT signal is blocked\n");
         sleep(1);
      }

      //将set信号集 从信号阻塞集 中删除
      sigprocmask(SIG_UNBLOCK, &set, NULL);
      for(i=0; i<5; i++)
      {
         printf("SIGINT signal unblocked\n");
         sleep(1);
      }
   }


    return 0;
}