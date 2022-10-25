#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_fun(void *arg)
{
    printf("子线程正在运行\n");

    static char buf[] = "This thread has quited";


    int i;
    for(int i = 0; i < 10; i++)
    {
        if(i == 5)
        {
            //通过pthread_exit函数可以退出当前线程,也可以返回返回值
            printf("子线程要退出了\n");
            //pthread_exit(NULL);

            pthread_exit(buf);
        }
        printf("*************\n");
        sleep(1);
    }

    printf("子线程要退出了\n");
}

int main(int argc, char const *argv[])
{
    /*
    头文件：#include <pthread.h>
    函数：  void pthread_exit(void *retval);
    功能：  退出调用线程。
    参数:   retval：存储线程退出状态的 指针。

    注意：
        一个进程中的多个线程是共享该进程的数据段，因此，通常线程退出后所占用的资源并不会释放。
        如果要释放资源，结合态需要通过pthread_join函数，分离态则自动释放
    */

   printf("主控线程正在运行\n");

   pthread_t thread;

   if(pthread_create(&thread, NULL, thread_fun, NULL) != 0)
   {
      perror("fail to pthread_create");
      exit(1);
   }

   //pthread_join(thread, NULL);

   char *str;
   pthread_join(thread, (void **)&str);

   printf("str = %s\n", str);

   printf("进程退出了\n");

    return 0;
}