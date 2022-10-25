#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <sys/msg.h>
    函数：int msgget(key_t key, int msgflg)；
    功能：
       创建一个新的或打开一个已经存在的消息队列。不同的进程调用此函数，只要用相同的 key 值就能得到同一
       个消息队列的标识符。
    参数：
        key：IPC 键值。
             方法1：任意指定一个数
             方法2：使用ftok函数获取键值
        msgflg：标识函数的行为及消息队列的权限

        msgflg 的取值：
              IPC_CREAT：创建消息队列。
              IPC_EXCL：检测消息队列是否存在。
              位或权限位：消息队列位或权限位后可以设置消息队列的访问权限，格式和 open 函数的 mode_t 一样，
                但可执行权限未使用。
    返回值：
        成功：消息队列的标识符，失败：返回-1。

    使用 shell  命令操作消息队列: 
    查看消息队列
         ipcs -q
    删除消息队列
         ipcrm -q msqid
    */

   //通过ftok函数获取ipc的键值
   key_t my_key;
   if((my_key = ftok(".", 100)) == -1)
   {
       perror("fail to ftok");
       exit(1);
   }
   printf("my_key = %#x\n", my_key);


   //通过msgget函数创建一个消息队列
   int msq_id;
   if((msq_id = msgget(my_key, IPC_CREAT | 0666)) == -1)
   {
      perror("fail to msgget");
      exit(1);
   }
   printf("msq_id = %d\n", msq_id);

   system("ipcs -q");

    return 0;
}