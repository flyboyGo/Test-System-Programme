#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //进程在一定的时间内没有任何动作，称为进程的挂起(阻塞)   #include <unistd.h>
    //unsigned int sleep(unsigned int sec);
    //功能：进程挂起指定的秒数，直到指定的时间用完或收到信号才解除挂起。
    //返回值：
    //若进程挂起(阻塞)到 sec 指定的时间则返回 0，若有信号中断则返回剩余秒数。
    //注意：
    //进程挂起(阻塞)指定的秒数后程序并不会立即执行，系统只是将此进程切换到就绪态。

    while(1)
    {
        printf("hello world\n");

        //当运行到sleep函数后 程序会在此位置等待设定的秒数 直到秒数时间到后 代码就会继续执行
        //sleep运行时进程此时为等待(阻塞)态，时间到后会先切回就绪态，如果代码继续执行，再切换到运行态
        sleep(2);
    }

    return 0;
}