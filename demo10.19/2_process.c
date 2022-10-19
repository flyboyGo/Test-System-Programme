#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //头文件#include <sys/types.h> #include <unistd.h>
    //在linux环境下 ,创建进程的主要方法是调用以下两个函数: 
    //pid_t fork(void);    pid_t vfork(void);
    //创建一个新进程
    //pid_t fork(void)
    //功能:
    //fork()函数用于从一个 "已存在的进程" 中创建一个新进程，新进程称为子进程，原进程称为父进程。
    //返回值:  成功：子进程中返回 0，父进程中返回子进程 ID;  失败：返回-1

    //进程的调度机制是 时间片轮转 上下文切换

    //不区分父子进程!!!!!!!!!!!!!!!!
    //通过fork函数创建一个子进程
    //注意：只要执行一次fork() 就会在原有的基础上创建一个新的子进程
    //而且如果fork()之后不区分父子进程的代码区，则后面的所有代码都会执行
#if 0
    fork();
    printf("hello world\n");

    while(1);
#endif
    

    //区分父子进行！！！！！！！
    //通过fork函数的返回值来区分父子进程的独立的代码区
    //父子进程是来回 "交替执行"的，谁先运行，谁后运行是不确定的，不要认为父进程执行完之后才会执行子进程
    pid_t pid;

    pid = fork();
    if(pid <0)
    {
        perror("fail to fork");
        return -1;
    }
    else if(pid > 0) //返回的是子进程的进程号 但是 是 "父进程" 的代码区
    {
        while(1)
        {
            printf("parent: pid = %d, ppid= %d\n", getpid(), getppid());
            printf("pid = %d\n", pid);
            printf("this is a parent process\n");
            sleep(1);
            printf("******************************\n");
        }
    }
    else //pid == 0 子进程的代码区
    {
        while(1)
        {
            printf("parent: pid = %d, ppid= %d\n", getpid(), getppid());
            printf("this is a son process\n");
            sleep(1);
            printf("--------------------------------\n");
        }
    }

    return 0;
}