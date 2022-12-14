#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//线程处理函数就可以认为就是一个普通的全局函数，只不过与不同函数最大的区别
//在于，线程处理函数是在并行执行的，来回交替执行,但是普通函数一定是按照顺序执行一个一个执行的

int num = 100;

void *pthread_fun1(void *arg)
{
    printf("子线程1: num = %d\n", num);
    num++;

    int n = *(int *)arg;
    printf("1 n = %d\n", n);

    *(int *)arg = 777;

}

void *pthread_fun2(void *arg)
{
    sleep(1);
    printf("子线程2: num = %d\n", num);
    num++;

    int n = *(int *)arg;
    printf("2 n = %d\n", n);
}

int main(int argc, char const *argv[])
{
    int a = 666;

    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, pthread_fun1, (void *)&a) !=0)
    {
        perror("fail to pthread_create");
    }

    if(pthread_create(&thread2, NULL, pthread_fun2, (void *)&a) !=0)
    {
        perror("fail to pthread_create");
    }

    while(1);

    return 0;
}