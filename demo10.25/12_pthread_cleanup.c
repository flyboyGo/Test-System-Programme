#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /*
     和进程的退出清理一样，线程也可以注册它退出时要调用的函数，
     这样的函数称为线程清理处理程序(threadcleanup handler)

     注意:
         线程可以建立多个清理处理程序。
         处理程序在栈中，故它们的执行顺序与它们注册时的顺序相反

    注册清理函数
    头文件：#include <pthread.h>
    函数：       
         void pthread_cleanup_push(void (* routine)(void *), void *arg)
    功能:
         将清除函数压栈。即注册清理函数。
    参数:
         routine：线程清理函数的指针。
         arg：传给线程清理函数的参数。


    弹出清理函数
    头文件：#include <pthread.h>
    函数：void pthread_cleanup_pop(int execute);
    功能：
         将清除函数弹栈，即删除清理函数。
    参数：
        execute:线程清理函数执行标志位。
             非 0，弹出清理函数，执行清理函数。
             0，弹出清理函数，不执行清理函数。


    当线程执行以下动作时会调用清理函数：
       1、调用 pthread_exit 退出线程
       2、响应其它线程的取消请求
       3、用非零 execute 调用 pthread_cleanup_pop

      无论哪种情况 pthread_cleanup_pop 都将删除上一次 pthread_cleanup_push 调用注册的清理处理函数。
    */

    return 0;
}