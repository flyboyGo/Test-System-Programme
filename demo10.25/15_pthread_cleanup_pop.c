#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void mycleanup(void *arg)
{
    printf("in cleanup func1\n");
    printf("clean up ptr = %s\n", (char *)arg);
    free((char *)arg);
}
void mycleanup2(void *arg)
{
    printf("in cleanup func2\n");
}

void *thread(void * arg)
{
    
    //建立线程清理函数
    printf("this is new thread\n");

    char *ptr = NULL;
    ptr = (char*)malloc(100);

    pthread_cleanup_push(mycleanup, (void*)(ptr));
    pthread_cleanup_push(mycleanup2, NULL);

    bzero(ptr, 100);
    strcpy(ptr, "memory from malloc");

    sleep(3);

    //注意push与pop必须配对使用,即使pop执行不到
    printf("before pop\n");
    pthread_cleanup_pop(1);
    printf("before pop\n");
    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    
    pthread_join(tid, NULL);
    printf("process is dying\n");

    return 0;
}