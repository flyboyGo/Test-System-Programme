#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void clear_fun1(void)
{
    printf("perform clear fun1\n");
}
void clear_fun2(void)
{
    printf("perform clear fun2\n");
}
void clear_fun3(void)
{
    printf("perform clear fun3\n");
}

int main(int argc, char const *argv[])
{
    /*
    进程在退出前可以用 t atexit  函数注册退出处理函数
    头文件：#include <stdlib.h>
           int atexit(void (*function)(void));
    功能：
        注册进程正常结束前调用的函数，进程退出执行注册函数。
    参数：
        function：进程结束前，调用函数的入口地址
    返回值：
        成功：0
        失败：非0

    一个进程中可以多次调用 atexit 函数注册清理函数，正常结束前调用函数的顺序和注册时的顺序相反
    
    */

   //atexit函数在进程结束时才会区执行参数对应的回调函数
   //atexit多次调用后，执行顺序与调用的顺序相反
   atexit(clear_fun1);
   atexit(clear_fun2);
   atexit(clear_fun3);
   printf("process exit 3 sec later!!!\n");
   sleep(3);

    return 0;
}