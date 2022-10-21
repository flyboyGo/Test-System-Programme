#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
   /*
      信号集概述：
         一个用户进程常常需要对多个信号做出处理。为了方便对多个信号进行处理，在 Linux 系统中引入了信号集。

      信号集是用来表示多个信号的数据类型。
      信号集数据类型：
           sigset_t
           #define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
           typedef struct
           {
              unsigned long int _val[_SIGSET_NWORDS];
           }_sigset_t;

      定义路径：
           /usr/include/x86_64-linux-gnu/bits/sigset.h

      信号集相关的操作主要有如下几个函数：
          sigemptyset
          sigfillset
          sigismember
          sigaddset
          sigdelset
    */

   /*
     sigemptyset函数  初始化一个空的信号集
     头文件： #include <signal.h>
     函数：
         int sigemptyset(sigset_t *set);
     功能：
         初始化由 set 指向的信号集，清除其中所有的信号即初始化一个空信号集
     参数：
         set：信号集标识的地址，以后操作此信号集，对 set 进行操作就可以了
     返回值: 
         成功返回 0，失败返回 -1
   */

   /*
      sigfillset函数  初始化一个满的信号集
      头文件：#include <signal.h>
      函数： int sigfillset(sigset_t *set)；
      功能：
           初始化信号集合 set, 将信号集合设置为所有信号的集合。
      参数：
           信号集标识的地址，以后操作此信号集，对 set 进行操作就可以了。
      返回值: 
           成功返回 0，失败返回 -1。
    */

   /*
   sigismember函数  判断某个集合中是否有某个信号
   头文件：#include <signal.h>
   函数：
       int sigismember(const sigset_t *set,int signum);
   功能：
       查询 signum 标识的信号是否在信号集合 set 之中。
   参数：
        set：信号集标识符号的地址。
        signum：信号的编号。
   返回值: 
        在信号集中返回 1，不在信号集中返回 0
        失败，返回 -1
   */

   /*
  sigaddset函数   向某个集合中添加一个信号
  头文件：#include <signal.h>
  函数：
       int sigaddset(sigset_t *set, int signum);
  功能：
       将信号 signum 加入到信号集合 set 之中。
  参数：
      set：信号集标识的地址。
      signum：信号的编号
  返回值:
     成功返回 0，失败返回 -1。
  */

   /*
 sigdelset函数   向某个集合中删除一个信号
  头文件：#include <signal.h>
  函数：
       int sigdelset(sigset_t *set, int signum);
  功能：
       将 signum 所标识的信号从信号集合 set 中删除
  参数：
      set：信号集标识的地址
      signum：信号的编号
  返回值:
     成功返回 0，失败返回 -1
 */
   
   //创建也给信号集
   sigset_t set;
   int ret = 0;

   //初始化一个空的信号集
   sigemptyset(&set);

   //判断SIGINT信号是否在信号集合中
   ret = sigismember(&set, SIGINT);
   if(ret == 0)
   {
      printf("SIGINT is not a membet of sigprocmask \n ret = %d\n", ret);
   }

   //将指定的信号添加到信号集中
   sigaddset(&set, SIGINT);
   sigaddset(&set, SIGQUIT);

   ret = sigismember(&set, SIGINT);
   if(ret == 1)
   {
      printf("SIGINT is a membet of sigprocmask \n ret = %d\n", ret);
   }

    return 0;
}