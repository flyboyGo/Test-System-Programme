#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>

int main(int argc, char const * argv[])
{

    /*
    头文件：#include <sys/types.h>    #include <sys/ipc.h>
    函数：key_t ftok(const char *pathname, int proj_id)；
    功能：
        获得项目相关的唯一的 IPC 键值。
    参数：
        pathname：路径名
        proj_id：项目 ID，非 0 整数(只有低 8 位有效)
    返回值：
        成功返回 key 值，
        失败返回 -1

    如果使用ftok函数获取键值，得到的键值是由ftok的第一个参数对应的文件信息和第二个参数一起决定的
    */

   //使用ftok函数获取键值
   //只要保证ftok的一个参数对应的文件和第二个参数值相同，则不管程序运行多少遍或者多少个进程获取键值
   //键值一定是唯一的
   key_t my_key;
   if((my_key = ftok(".", 100)) == -1)
   {
        perror("fail to ftok");
        exit(1);
   }

   printf("my_key = %#x\n", my_key);

    return 0;
}