#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int money = 10000;

//第一步：创建互斥锁(由于两个线程操作同一个互斥锁,所以定义在全局更加方便一点)
pthread_mutex_t my_mutex;

void *pthread_fun1(void *arg)
{

    int get, yu, shiji;
    get = 10000;

    //第三步：对共享资源的操作进行上锁
    if(pthread_mutex_lock(&my_mutex) != 0)
    {
        perror("pthread_mutex_lock fail");
        exit(1);
    }

    printf("张三正在查询余额...\n");
    sleep(1);
    yu = money;

    printf("张三正在取钱...\n");
    sleep(1);
    if(get > yu)
    {
        shiji = 0;
    }
    else
    {
        shiji = get;
        yu = yu - get;
        money = yu;
    }

    printf("张三想取%d元.实际取了%d元,余额为%d\n", get, shiji, yu);

    //第四步：当共享资源的操作执行完毕后,对互斥锁执行解锁操作
    if(pthread_mutex_unlock(&my_mutex) !=0)
    {
        perror("pthread_mutex_unlock");
        exit(1);
    }

    pthread_exit(NULL);
}

void *pthread_fun2(void *arg)
{
    int get, yu, shiji;
    get = 10000;

    //第三步：对共享资源的操作进行上锁
    if(pthread_mutex_lock(&my_mutex) != 0)
    {
        perror("pthread_mutex_lock fail");
        exit(1);
    }

    printf("李四正在查询余额...\n");
    sleep(1);
    yu = money;

    printf("李四正在取钱...\n");
    sleep(1);
    if(get > yu)
    {
        shiji = 0;
    }
    else
    {
        shiji = get;
        yu = yu - get;
        money = yu;
    }

    printf("张三想取%d元.实际取了%d元,余额为%d\n", get, shiji, yu);

    //第四步：当共享资源的操作执行完毕后,对互斥锁执行解锁操作
    if(pthread_mutex_unlock(&my_mutex) !=0)
    {
        perror("pthread_mutex_unlock");
        exit(1);
    }

    pthread_exit(NULL);
}

//通过互斥锁解决线程互斥问题
int main(int argc, char const *argv[])
{

    //第二步：初始化互斥锁
    if(pthread_mutex_init(&my_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init fail");
        exit(1);
    }

    pthread_t thread1, thread2;

    if(pthread_create(&thread1, NULL, pthread_fun1, NULL) != 0)
     {
          perror("fail to pthread_create");
          exit(1);
     }

    if(pthread_create(&thread2, NULL, pthread_fun2, NULL) != 0)
     {
          perror("fail to pthread_create");
          exit(1);
     }

     pthread_join(thread1,NULL);
     pthread_join(thread2,NULL);

     //第五步：当互斥锁使用完毕,销毁互斥锁
     if(pthread_mutex_destroy(&my_mutex) != 0)
     {
        perror("pthread_mutex_destroy fail");
        exit(1);
     }
     
    return 0;
}