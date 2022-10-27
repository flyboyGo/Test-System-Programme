#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


//信号量实现互斥操作

//第一步：创建信号量
sem_t sem;

void printer(char *str)
{
    //第三步：执行P操作
    //由于使用信号量实现互斥,信号量的初始值设置为1,则两个线程执行p操作
    //先执行P操作的线程先执行,后执行P操作的先阻塞等待
    sem_wait(&sem);

    while(*str)
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }

    //第四步：执行V操作
    sem_post(&sem);

}

void *thread_fun1(void *arg)
{
    char *str1 = "hello";
    printer(str1);
}

void *thread_fun2(void *arg)
{
    char *str2 = "world";
    printer(str2);
}

int main(int argc, char const *argv[])
{
    //第二部：初始化信号量
    sem_init(&sem, 0, 1);

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_fun1, NULL);
    pthread_create(&tid2, NULL, thread_fun2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("\n");

    //第五步：使用完毕销毁信号量
    sem_destroy(&sem);

    return 0;
}