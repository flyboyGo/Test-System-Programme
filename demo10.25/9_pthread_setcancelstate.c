#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fun(void *arg)
{
    //通过pthread_setcancelstate设置取消状态(线程默认可以取消)
    //设置可以取消
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //设置不可以取消
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    while(1)
    {
        printf("子线程正在运行\n");
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    /*
      线程的取消状态
          即线程能不能被取消
      线程取消点
          即线程被取消的地方
      线程的取消类型
          在线程能被取消的状态下，是立马被取消结束还是执行到取消点的时候被取消结束

    线程的取消状态
       在 Linux 系统下，线程默认可以被取消。
       编程时可以通过 pthread_setcancelstate函数 设置线程是否可以被取消。
    函数：
          pthread_setcancelstate(int state,int *old_state);
    功能：
          设置线程是否被取消
    参数：
        state：
              PTHREAD_CANCEL_DISABLE：不可以被取消
              PTHREAD_CANCEL_ENABLE：可以被取消
        old_state：
              保存调用线程原来的可取消状态的内存地址。
    返回值：
          成功：0   失败：非0
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