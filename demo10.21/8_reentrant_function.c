#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


void handler(int sig)
{
    printf("SIGINT\n");
}

int main(int argc, char const * argv[])
{
    /*
    可重入函数：
        可重入函数是指函数可以由多个任务并发使用，而不必担心数据错误
        可重入函数就是可以被中断的函数，当前函数可以在任何时刻中断它，并执行另一块代码，
        当执行完毕后，回到原本的代码还可以正常继续运行
    编写可重入函数：
        1、不使用（返回）静态的数据、全局变量（除非用信号量互斥）
        2、不调用动态内存分配、释放的函数。
        3、不调用任何不可重入的函数（如标准I/O函数）
    注：
       即使信号处理函数使用的都是可重入函数（常见的可重入函数），也要注意进入处理函数时，
       首先要保存errno的值，结束时，再恢复原值。因为，信号处理过程中，errno值随时可能被改变。
    */
   
   signal(SIGINT,handler);

   //案例一
#if 0
    //sleep是一个可重入函数，但是当执行信号处理函数之后,不会回到原本的位置继续睡眠(阻塞)
    //sleep(10);

    //alram是一个可重入函数，当执行时,如果信号产生并执行信号处理函数,执行完毕后，回到原本的位置继续睡眠(阻塞)
    alarm(10);

     while(1)
     {
        printf("hello world\n");
        sleep(1);
     }
#endif

   //案例2：
#if 1
    char buf[32] = "";

    //read也是一个可重入函数，在等待终端输入时,如果产生信号并执行处理函数，信号处理函数处理完毕后，
    //可以继续读取数据，read可以读取到  "信号处理函数之后" 的数据
    if(read(0,buf,20) == -1)
    {
        perror("fail to read\n");
        exit(1);
    }

    printf("buf = [%s\n]", buf);
#endif


    return 0;
}