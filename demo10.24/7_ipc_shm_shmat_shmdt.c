#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const * argv[])
{

    /*
    头文件：#include <sys/types.h>  #include <sys/shm.h>
    函数：void *shmat(int shmid, const void *shmaddr, int shmflg);
    功能：将一个共享内存段映射到调用进程的数据段中
    参数：
        shmid：共享内存标识符
        shmaddr：共享内存映射地址(若为 NULL 则由系统自动指定)，推荐使用 NULL
        shmflg：共享内存段的访问权限和映射条件
            0：共享内存具有可读可写权限
            SHM_RDONLY：只读
            SHM_RND：（shmaddr 非空时才有效）
            没有指定 SHM_RND 则此段连接到 shmaddr 所指定的地址上(shmaddr 必需页对齐)
            指定了 SHM_RND 则此段连接到 shmaddr- shmaddr%SHMLBA 所表示的地址上
    返回值：
        成功：返回共享内存段映射地址
        失败：返回 -1

    注意：
       shmat 函数使用的时候第二个和第三个参数一般设为 NULL 和 0，
       即系统自动指定共享内存地址，并且共享内存可读可写


    头文件：#include <sys/types.h>   #include <sys/shm.h>
    函数：int shmdt(const void *shmaddr);
    功能：将共享内存和当前进程分离(仅仅是断开联系 "并不删除共享内存")
    参数：
         shmaddr：共享内存映射地址。
    返回值：
         成功返回 0，失败返回 -1
    */

    return 0;
}