#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fun(void *arg)
{
    while(1)
    {
        printf("子线程正在运行\n");
        sleep(1);

        //设置取消点(pthread_testcancel可以产生阻塞)
        pthread_testcancel();
    }
}

int main(int argc, char const *argv[])
{
    /*
      线程的取消点
      线程被取消后，该线程并不是马上终止，默认情况下线程执行到消点时才能被终止。
      编程时可以通过pthread_testcancel 函数设置线程的取消点。
      void pthread_testcancel(void);
      当别的线程取消调用此函数的线程时候，被取消的线程执行到此函数时结束。

      头文件：#include <pthread.h>
      函数：void pthread_testcancel(void);
      功能：设置线程的取消点
      参数：无
      返回值：无

    取消点概述：
        我们都知道，程序的进行是一个时间过程而不是一个时间点。
        取消点的简单意思来说在一个时间段内,程序被挂起时,可以被取消的一个时间点.(APUE363页有详细的取消点函数）
        也就是说，当线程出现 block(阻塞) 时，这个被阻塞的地方就是可被取消的地方。

    更通俗的来说：就是线程A执行过程中，如果遇到其他线程B执行cancel函数，线程继续运行，直到线程某一行代码出现阻塞

    (如：pthread_testcancel、pthread_join、pthread_cond_wait、printf、sleep、read、write、
    等都是可以产生阻塞的函数）此时就会退出。

    如果线程B还使用了pthread_join去获取返回值，返回值为整型且为PTHREAD_CANCELED（-1）
    */

   printf("主控线程正在运行\n");

   pthread_t thread;

   if(pthread_create(&thread, NULL, thread_fun, NULL) != 0)
   {
      perror("fail to pthread_create");
      exit(1);
   }

   sleep(3);

   //通过调用pthread_cancel函数取消另一个线程
   pthread_cancel(thread);

   pthread_join(thread, NULL);

    return 0;
}