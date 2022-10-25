#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
头文件：#include <sys/ipc.h>    #include <sys/shm.h>
函数：  int shmget(key_t key, size_t size,int shmflg);
功能:   创建或打开一块共享内存区
参数：
    key：IPC 键值
    size：该共享存储段的长度(字节)
    shmflg：标识函数的行为及共享内存的权限。
        IPC_CREAT：如果不存在就创建
        IPC_EXCL：如果已经存在则返回失败
        位或权限位：共享内存位或权限位后可以设置共享内存的访问权限，格式和 open 函数的 mode_t 一样，
        但可执行权限未使用。
    返回值: 
        成功：返回共享内存标识符。
        失败：返回－1

    使用 shell  命令操作共享内存: 
        查看共享内存：ipcs -m
        删除共享内存：ipcrm -m shmid
*/

int main(int argc, char const * argv[])
{
    //使用ftok函数获取键值
    key_t my_key;
    if((my_key = ftok(".", 100)) == -1)
    {
        perror("fail to ftok");
        exit(1);
    }

    //通过shmget函数创建或者打开一个共享内存，返回一个共享的标识符
    int shmid;
    if((shmid = shmget(my_key, 500, IPC_CREAT | 0666)) == -1)
    {
        perror("fail to shmget");
        exit(1);
    }

    printf("shmid = %d\n", shmid);
    system("ipcs -m");

    return 0;
}