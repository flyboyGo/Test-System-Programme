#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void mycleanup(void *arg)
{
    printf("clean up ptr = %s\n", (char *)arg);
    free((char *)arg);
}

void *thread(void * arg)
{
    
    //建立线程清理函数
    printf("this is new thread\n");

    char *ptr = NULL;
    ptr = (char*)malloc(100);

    pthread_cleanup_push(mycleanup, (void*)(ptr));

    bzero(ptr, 100);
    strcpy(ptr, "memory from malloc");

    sleep(3);
    printf("before exit\n");

    //线程调用pthread_exit函数时,系统自动调用线程清理函数
    pthread_exit(NULL);

    //注意push与pop必须配对使用,即使pop执行不到
    printf("before pop\n");
    pthread_cleanup_pop(1);
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    printf("process is dying\n");

    return 0;
}