#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define N 128

typedef struct
{
    long msg_type; //消息类型,必须在结构体的第一个位置并且类型必须是long
    char msg_text[N]; //消息正文，也可以有多个成员并且类型也可以是任意的
}MSG;

#define MSGTEXT_SIZE (sizeof(MSG) - sizeof(long))

int main(int argc, char const * argv[])
{
    /*
    头文件：#include <sys/msg.h>
    函数： int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    功能：
        对消息队列进行各种控制，如修改消息队列的属性，或删除消息消息队列。
    参数：
        msqid：消息队列的标识符。
        cmd：函数功能的控制。
        buf：msqid_ds 数据类型的地址，用来存放或更改消息队列的属性。

        cmd：函数功能的控制
             IPC_RMID：删除由 msqid 指示的消息队列，将它从系统中删除并破坏相关数据结构。
             IPC_STAT：将 msqid 相关的数据结构中各个元素的当前值存入到由 buf 指向的结构中。
             IPC_SET：将 msqid 相关的数据结构中的元素设置为由 buf 指向的结构中的对应值。
    返回值：
        成功：返回 0；失败：返回 -1
    */

   //通过ftok函数获取ipc的键值
   key_t my_key;
   if((my_key = ftok(".", 100)) == -1)
   {
       perror("fail to ftok");
       exit(1);
   }

   //通过msgget函数创建一个消息队列
   int msg_id;
   if((msg_id = msgget(my_key, IPC_CREAT | 0666)) == -1)
   {
      perror("fail to msgget");
      exit(1);
   }
   printf("msgid = %d\n", msg_id);
   system("ipcs -q");

   //通过msgctl函数删除消息队列
   if(msgctl(msg_id, IPC_RMID, NULL) == -1)
   {
       perror("fail to msgctl");
       exit(1);
   }

   system("ipcs -q");
   

    return 0;
}