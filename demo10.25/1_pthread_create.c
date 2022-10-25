#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//由于线程库原本不是系统本身的,所以在链接时需要手动链接库文件 gcc *.c -lpthread

//线程函数
void *thread_fun(void * arg)
{
    printf("子线程正在运行\n");
}

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <pthread.h>
    函数：
          int pthread_create(pthread_t *thread,const pthread_attr_t *attr,
                                void *(*start_routine)(void *),void *arg);
    功能：创建一个线程。
    参数：
         thread：线程标识符地址。
         attr：线程属性结构体地址。
         start_routine：线程函数的入口地址。
         arg：传给线程函数的参数。
    返回值：
         成功：返回 0   失败：返回非 0

    与 fork 不同的是 pthread_create 创建的线程不与父线程在同一点开始运行，而是从指定的函数开始运行，
    该函数运行完后，该线程也就退出了。
    线程依赖进程存在的，如果创建线程的进程结束了，线程也就结束了。
    线程函数的程序在 pthread 库中，故链接时要加上参数-lpthread。
    */

   printf("主控线程正在执行\n");

   //线程标识符
   pthread_t thread_id;

   //通过pthread_create函数创建子线程
   if(pthread_create(&thread_id, NULL, thread_fun, NULL) !=0)
   {
      perror("fail to pthread");
      exit(1);
   }

   //由于进程结束后,进程中所有的线程都会强制退出，所以现阶段不要让进程退出
   while(1);

    return 0;
}