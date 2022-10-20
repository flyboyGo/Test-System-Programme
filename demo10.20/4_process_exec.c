#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /*
    进程的替换  
    exec函数族，是由六个exec函数组成的。
    1、exec函数族提供了六种在进程中启动另一个程序的方法。
    2、exec函数族可以根据指定的文件名或目录名找到可执行文件。
    3、调用exec函数的进程并不创建新的进程，故调用exec前后，进程的 "进程号" 并不会改变，
       其执行的程序完全由新的程序替换，而新程序则从其main函数开始执行。

    exec函数族取代调用进程的数据段、代码段和堆、栈段。

    一个进程调用exec后，除了进程ID，进程还保留了下列特征不变：
    父进程号、进程组号、控制终端、根目录、当前工作目录、进程信号屏蔽集、未处理信号

    exec函数族：
    头文件: #include <unistd.h>
    int execl (const char *path, const char *arg0, ..., NULL);
    int execlp(const char *file, const char *arg0, ..., NULL);
    int execle(const char *path, char *const arg, ..., NULL, char * const envp[]);

    int execv (const char *path, char *const argv[]);
    int execvp(const char *file, char *const argv[]);
    int execve(const char *path, char *const argv[], char *const envp[]);

    6个exec 函数中只有 execve  是真正意义的系统调用((内核提供的接口)),
    其它函数都是在此基础上经过封装的库函数。

    注意：
       exec 函数族与一般的函数不同，exec 函数族中的函数执行成功后不会返回。
       只有调用失败了，它们才会返回－1。
       失败后从原程序的调用点接着往下执行。
       在平时的编程中，如果用到了 exec 函数族，一定要记得加错误判断语句。

    重点:
        //exec函数取代调用进程的数据段、代码段、和堆、栈段
        //所以当exec函数执行完毕后，当前进程就结束了，所以 "原本进程中" 的代码 "不会在执行"

    */

    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if(pid > 0) //父进程
    {
        printf("Parent Process\n");
        wait(NULL);
        printf("The Child Process has quited\n");
    }
    else //子进程
    {
        printf("Son Process\n");

    //调用exec函数族中的函数，执行其他命令或者程序
    //查看命令的路径：whereis 命令或者which 命令

    //***************exec函数族调用shell命令******************

    //不带p的函数，命令的路径一定要用绝对路径
#if 0
        if(execl("/usr/bin/ls","ls","-l",NULL) == -1)
        {
            perror("fail to execl");
            exit(1);
        }
#endif

    //带p的函数，(第一个参数)命令的路径可以是绝对路径，也可以是相对路径
#if 0
        if(execlp("ls","ls","-l",NULL) == -1)
        {
            perror("fail to execlp");
            exit(1);
        }
#endif

    //带v的函数需要使用指针数组来传递命令参数
#if 0
        char *str[] = {"ls", "-l", NULL};
        if(execv("/usr/bin/ls",str) == -1)
        {
            perror("fail to execv");
            exit(1);
        }
#endif


    //***************exec函数族调用可执行文件******************
#if 0
    if(execlp("./hello","./hello", NULL) == -1)
    {
        perror("fail to execlp");
        exit(1);
    }

#endif

#if 0
    if(execl("./hello","./hello", NULL) == -1)
    {
        perror("fail to execl");
        exit(1);
    }
#endif


    //***************exec函数族调用shell脚本******************
#if 0
    if(execlp("./myshell.sh","./myshell.sh", NULL) == -1)
    {
        perror("fail to execlp");
        exit(1);
    }
#endif

#if 0
    char * env[] = {"USER=ME"};
    if(execle("/usr/bin/echo","echo", "$USER", NULL, env) == -1)
    {
        perror("fail to execle");
        exit(1);
    }
#endif


#if 1
    char * env[] = {"USER=ME"};
    char * str[] = {"echo $USER"};
    if(execve("/usr/bin/echo", str, env) == -1)
    {
        perror("fail to execve");
        exit(1);
    }
#endif


        printf("hello world\n");
    }

    return 0;
}