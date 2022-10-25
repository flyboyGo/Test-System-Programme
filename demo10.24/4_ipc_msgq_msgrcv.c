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
    函数： ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    功能：
        从标识符为 msqid 的消息队列中接收一个消息。一旦接收消息成功，则消息在消息队列中被 "删除"。
    参数：
       msqid：消息队列的标识符，代表要从哪个消息队列中获取消息
       msgp： 存放消息结构体的地址。
       msgsz：消息正文的字节数。
       msgtyp：消息的类型、可以有以下几种类型
          msgtyp = 0：返回队列中的第一个消息
          msgtyp > 0：返回队列中 "第一个" 消息类型为 msgtyp 的消息
          msgtyp < 0：返回队列中消息类型值小于或等于 msgtyp 绝对值的消息，
                      如果这种消息有若干个，则取 "类型值最小" 的消息
    注意：
        若消息队列中有多种类型的消息，msgrcv 获取消息的时候按消息类型获取，不是先进先出的。
        在获取某类型消息的时候，若队列中有多条此类型的消息，则获取最先添加的消息，即先进先出原则。

       msgflg：函数的控制属性
            0：msgrcv 调用阻塞直到接收消息成功为止。
            MSG_NOERROR:若返回的消息字节数比 nbytes 字节数多,则消息就会截短到 nbytes 字节,
                        且不通知消息发送进程。
            IPC_NOWAIT:调用进程会立即返回。若没有收到消息则立即返回-1。
    返回值：
        成功 返回读取消息的长度，失败 返回-1。
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

   system("ipcs -q");

   //通过msgrcv函数接收消息队列中的信息(读操作)
   //注意：如果没有第四个参数指定的消息类型存在时,msgrcv函数会阻塞等待
   MSG msg;
   if(msgrcv(msg_id, &msg, MSGTEXT_SIZE, -3, 0) == -1)
   {
       perror("fail to msgrcv");
       exit(1);
   }

   printf("recv_msg = %s\n", msg.msg_text);

   system("ipcs -q");


    return 0;
}