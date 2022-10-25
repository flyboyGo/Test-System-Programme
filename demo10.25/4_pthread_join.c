#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fun(void *arg)
{
    printf("子线程正在运行\n");

    sleep(3);

    printf("子线程要退出了\n");
}

int main(int argc, char const *argv[])
{
    /*
    头文件：#include <pthread.h>
    函数：int pthread_join(pthread_t thread, void **retval);
    功能：等待子线程结束，并回收子线程资源。
    参数：
        thread：被等待的线程号。
        retval：用来存储线程退出状态的指针的地址。
    返回值：
        功返回 0，失败返回非 0。
    */

   printf("主控线程正在运行\n");

   pthread_t thread;

   if(pthread_create(&thread, NULL, thread_fun, NULL) != 0)
   {
      perror("fail to pthread_create");
      exit(1);
   }

   //通过调用pthread_join函数阻塞，等待子线程退出

   if(pthread_join(thread, NULL) != 0)
   {
       perror("fail to pthread_join");
       exit(1);
   }

   printf("进程退出了\n");

    return 0;
}