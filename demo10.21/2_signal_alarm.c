#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <unistd.h>
    函数：unsigned int alarm(unsigned int seconds);
    功能：
        在seconds秒后,向 "调用进程" 发送一个 SIGALRM 信号,SIGALRM 信号的默认动作是终止调用 alarm 函数的进程
    返回值：
        若 "之前" 没有设置过定时器，或设置的定时器已超时，返回 0；否则返回定时器剩余的秒数，并重新设定定时器。
    */

   //当执行到alarm之后，代码会继续执行，当设定的时间到后,会产生SIGALRM信号

   //如果alram之前没有设置其他闹钟，则返回0，如果之前设置了，则返回之前剩余的秒数
   //如果一个程序中出现多个闹钟,第一个如果没有到达指定的时间就遇到第二个
   //则第一个的闹钟时间清除，按照第二个alarm闹钟的时间继续往下运行
   unsigned int sec;

   sec = alarm(5);
   printf("sec = %d\n", sec);

   sleep(3);

   sec = alarm(6);
   printf("sec = %d\n", sec);

   while(1)
   {
       printf("hello world\n");
       sleep(1);
   }
   
    return 0;
}