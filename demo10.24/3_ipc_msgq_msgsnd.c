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
    函数：int msgsnd(int msqid, const void *msgp,size_t msgsz, int msgflg);
    功能：
        将新消息添加到消息队列。
    参数：
       msqid： 消息队列的标识符。
       msgp：  待发送消息结构体的地址。
       msgsz： 消息 "正文" 的字节数。
       msgflg：函数的控制属性
             0：msgsnd 调用阻塞直到条件满足为止。
             IPC_NOWAIT: 若消息没有立即发送 则调用该函数的进程会立即返回。

    返回值：
         成功：0；失败：返回-1。

    消息队列的消息的格式。
        typedef struct _msg
        {
            long mtype; 消息类型
            char mtext[100]; 消息正文
           ... 消息的正文可以有多个成员
        }MSG;

    消息类型必须是长整型的，而且必须是结构体类型的第一个成员，
    类型下面是消息正文，正文可以有多个成员（正文成员可以是任意数据类型的）
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

   //使用msgsnd函数向消息队列中发送数据(写操作)
   MSG msg1 = {1, "hello world"};
   MSG msg2 = {1, "flight"};
   MSG msg3 = {1, "again"};
   MSG msg4 = {1, "go on"};

   if(msgsnd(msg_id, &msg1, MSGTEXT_SIZE, 0) == -1)
   {
      perror("fail to msgsnd");
      exit(1);
   }
   if(msgsnd(msg_id, &msg2, MSGTEXT_SIZE, 0) == -1)
   {
      perror("fail to msgsnd");
      exit(1);
   }
   if(msgsnd(msg_id, &msg3, MSGTEXT_SIZE, 0) == -1)
   {
      perror("fail to msgsnd");
      exit(1);
   }
   if(msgsnd(msg_id, &msg4, MSGTEXT_SIZE, 0) == -1)
   {
      perror("fail to msgsnd");
      exit(1);
   }

   system("ipcs -q");

    return 0;
}