#include <stdio.h>
#include <stdlib.h>//exit
#include <string.h>//memset
#include <errno.h>
#include <sys/types.h>//fork
#include <sys/wait.h>//wait
#include <unistd.h>//fork pipe

#define MSG_LENGTH  20

int main()
{

    int pipefd[2];
    int pipe_ret = pipe(pipefd);
    if(pipe_ret == -1)
    {
        perror("pipe");
        exit(-1);
    }

    int pid = fork();
    if(pid == -1)
    {
        perror("fork");
        exit(-1);
    }
    else if(pid == 0)
    {
        char spreak_mask = '1';//0:父进程不想说话 1：父进程想说话
        char msg_data[MSG_LENGTH];
        while(1)
        {
            memset(msg_data,0,MSG_LENGTH);
            if(spreak_mask == '0')
            {
                printf("请输入要发送给父进程的消息：");//hello
                scanf("%s",msg_data);//我司旦丁
                spreak_mask = msg_data[strlen(msg_data)-1];//更新密令
                write(pipefd[1],msg_data,strlen(msg_data));//write
                
                sleep(1);
            }
            else if(spreak_mask == '1')
            {
                //read
                read(pipefd[0],msg_data,MSG_LENGTH);
                spreak_mask = msg_data[strlen(msg_data)-1];//更新密令
                printf("父进程说：%s\n",msg_data);
            }
            else if(spreak_mask == 'q')
            {
                break;
            }
            else
            {
                printf("数据有误，终止通信！\n");
                exit(-1);
            }
        }

    }
    else
    {
        char spreak_mask = '1';//0:父进程不想说话 1：父进程想说话
        char msg_data[MSG_LENGTH];
        while(1)
        {
            memset(msg_data,0,MSG_LENGTH);
            if(spreak_mask == '0')
            {
                //read
                read(pipefd[0],msg_data,MSG_LENGTH);
                spreak_mask = msg_data[strlen(msg_data)-1];//更新密令
                printf("子进程说：%s\n",msg_data);
            }
            else if(spreak_mask == '1')
            {
                //write

                printf("请输入要发送给子进程的消息：");
                scanf("%s",msg_data);
                spreak_mask = msg_data[strlen(msg_data)-1];//更新密令
                write(pipefd[1],msg_data,strlen(msg_data));//write
                sleep(1);
            }
            else if(spreak_mask == 'q')
            {
                break;
            }
            else
            {
                printf("数据有误，终止通信！\n");
                exit(-1);
            }
        }
    }

    /*共享区域*/
    close(pipefd[0]);
    close(pipefd[1]);

    if(pid>0)
    {
        wait(NULL);
    }
    
    exit(0);
}
