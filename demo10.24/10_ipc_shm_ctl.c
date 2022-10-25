#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const * argv[])
{
    /*
    头文件：  #include <sys/ipc.h>   #include <sys/shm.h>
    函数：  int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    功能： 共享内存空间的控制。
    参数：
        shmid：共享内存标识符。
        cmd：函数功能的控制。
        buf：shmid_ds 数据类型的地址，用来存放或修改共享内存的属性。

        cmd：函数功能的控制
           IPC_RMID：删除。
           IPC_SET：设置 shmid_ds 参数。
           IPC_STAT：获取 shmid_ds 参数。
           SHM_LOCK：锁定共享内存段(超级用户)。
           SHM_UNLOCK：解锁共享内存段。
    返回值：
        成功返回 0，失败返回 -1。
    */

    //通过ftok函数获取ipc的键值
   key_t my_key;
   if((my_key = ftok(".", 100)) == -1)
   {
       perror("fail to ftok");
       exit(1);
   }

   //通过shmget函数创建或打开一个共享内存,返回一个共享内存的标识符
   int shmid;
   if((shmid = shmget(my_key, 500, IPC_CREAT | 0666)) == -1)
   {
       perror("fail to shmget");
       exit(1);
   }

   system("ipcs -m");

   //通过shmctl函数删除共享内存
   if(shmctl(shmid, IPC_RMID, NULL) == -1)
   {
      perror("fail to shmctl");
      exit(1);
   }
   system("ipcs -m");

    return 0;
}