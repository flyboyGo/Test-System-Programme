#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //需要包含头文件：#include <sys/types.h>   #include <unistd.h>
    //pid_t getpid(void)        功能：获取本进程号(PID)
    //pid_t getppid(void)       功能：获取调用此函数的进程的父进程号(PPID)
    //pid_t getpgid(pid_t pid)  功能：获取进程组号(PGID)，
          //参数为 0 时返回当前 PGID，否则返回参数指定的进程的 PGID

    //获取当前进程的进程号
    printf("pid = %d\n", getpid());
    //获取当前进程的父进程号
    printf("ppid = %d\n", getppid());
    //获取当前进程所在组的进程号
    printf("pgid = %d\n", getpgid(0));
    printf("pgid = %d\n", getpgid(getpid()));

    return 0;
}