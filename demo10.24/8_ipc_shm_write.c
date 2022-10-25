#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

typedef struct 
{
    int age;
    char name;
}INFO;


int main(int argc, char const * argv[])
{

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

#if 0
  //使用shmat函数映射共享内存的地址
   char * my_share;
   if((my_share = shmat(shmid, NULL, 0)) == (void *)-1)
   {
       perror("fail to shmat");
       exit(1);
   }

   //通过shmat的返回值,向共享内存中写入数据
   strcpy(my_share, "hello world");
#endif

#if 1
  //使用shmat函数映射共享内存的地址
   INFO * my_share;
   if((my_share = shmat(shmid, NULL, 0)) == (void *)-1)
   {
       perror("fail to shmat");
       exit(1);
   }

   //通过shmat的返回值,向共享内存中写入数据
   my_share->age = 23;
   my_share->name = 'f';
#endif


   //操作完毕接触共享内存的映射
   if(shmdt(my_share) == -1)
   {
      perror("fail to shmat");
      exit(1);
   }

   system("ipcs -m");

    return 0;
}