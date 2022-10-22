#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    //创建两个无名管道
    int pipefd1[2] = {0};
    int pipefd2[2] = {0};
    int pipe_father = pipe(pipefd1);
    int pipe_son = pipe(pipefd2);

    pid_t ret = fork(); //创建进程
    if (ret == -1)
    {
        perror("fork");
    }
    else if (ret == 0) //子进程
    {
        char msg_son[32] = {0};
        char msg_father[32] = {0};
        while (1)
        {
            memset(msg_father, 0, 32);
            read(pipefd2[0], msg_father, 32);   //读阻塞，当管道没有数据时，对管道进行读取会阻塞
            printf("父亲说:%s\n", msg_father);
            
            printf("儿子：");
            scanf("%s", msg_son);
            write(pipefd1[1], msg_son, strlen(msg_son));
        }
        close(pipefd1[1]);
        close(pipefd2[0]);
    }
    else //父进程
    {
        char msg_father[32] = {0};
        char msg_son[32] = {0};
        while (1)
        {
            printf("父亲：");
            scanf("%s", msg_father);
            write(pipefd2[1], msg_father, strlen(msg_father));

            memset(msg_son, 0, 32);
            read(pipefd1[0], msg_son, 32);
            printf("儿子说:%s\n", msg_son);
        }

        close(pipefd2[1]);
        close(pipefd1[0]);
        
        wait(NULL);
    }
    return 0;
}