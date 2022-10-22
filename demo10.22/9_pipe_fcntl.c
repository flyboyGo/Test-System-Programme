#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    /*
       编程时可通过 fcntl  函数设置文件的阻塞特性。
       设置为阻塞：fcntl(fd, F_SETFL, 0);
       设置为非阻塞：fcntl(fd, F_SETFL, O_NONBLOCK);

       阻塞：
       1、如果是阻塞，管道中没有数据，read会一直等待，直到有数据才会继续运行，否则一直等待
       2、如果是非阻塞，read函数运行时，会先看一下管道中是否有数据，
          如果有数据，则正常运行读取数据，如果管道中没有数据，则read函数会 立即返回，继续下面的代码运行
    */
    int fd_pipe[2];
    if(pipe(fd_pipe) == -1)
    {
        perror("fail to pipe");
        exit(1);
    }

   char buf[32] = "hello world";
   pid_t pid;

   pid = fork();
   if(pid < 0)
   {
      perror("fail to fork");
      exit(1);
   }
   else if(pid == 0)
   {
      while(1)
      {
          sleep(5);
          write(fd_pipe[1], buf, strlen(buf));
      }
   }
   else
   {
       //将fd_pipe[0]设置为阻塞
       //fcntl(fd_pipe[0], F_SETFL, 0);
       //将fd_pipe[0]设置为非阻塞
       fcntl(fd_pipe[0], F_SETFL, O_NONBLOCK);

       while(1)
       {
           memset(buf, 0, sizeof(buf));
           read(fd_pipe[0], buf, sizeof(buf));
           printf("buf = [%s]\n", buf);
           sleep(1);
       }
   }

    return 0;
}