#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int a = 666;
int main(int argc, char const *argv[])
{
    pid_t pid;
    static int b = 777;
    int c = 888;

    //子进程会复制父进程fork()之前的所有内容
    //但是fork之后，父子进程完全独立，所以不管双方怎么改变(堆区、栈区、数据区等),都不会受对方的影响

    pid = fork();
    if(pid <0)
    {
        perror("fail to fork");
        return -1;
    }
    else if(pid > 0) //返回的是子进程的进程号 但是 是 "父进程" 的代码区
    {
        printf("This is a parent process\n");
        a++;
        b++;
        c++;
        printf("a = %d, b = %d, c = %d\n", a, b, c);
    }
    else //pid == 0 子进程的代码区
    {
        sleep(1);
        printf("This is a son process\n");
        printf("a = %d, b = %d, c = %d\n", a, b, c);
    }

    while(1);

    return 0;
}