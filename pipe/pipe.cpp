/**********************************************************
 * 说明: pipe管道的应用
 * 管道只能具有公共祖先的两个进程之间使用，通常fork后，父进程和
 * 子进程就可以使用管道进行数据通讯
 * pipe       用于创建管道描述符，其中fd[0]为读管道，fd[1]为写管道
 * read/write 用于通过管道的读写函数，和文件I/O中应用类似。
 * close      用于关闭管道
************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int fd[2];
    int ret;
    pid_t pid;
    char buf[512]= {0};

    ret = pipe(fd);
    if(ret == -1)
    {
        printf("pipe init failed\n");
    }

    pid = fork();
    if(pid < 0)
    {
         printf("fork failed\n");
    }
    else if(pid == 0)
    {
        close(fd[1]);
        int readsize;
	    readsize = read(fd[0], buf, sizeof(buf));
        if(write(STDOUT_FILENO, buf, readsize)<0)
        {
            printf("write std out fileNO failed\n");
        }
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        if(write(fd[1], "test for pipe\n", strlen("test for pipe\n"))>0)
        {
            wait(NULL);
        }
        else
        {
            printf("write pipe failed\n");
        }
        close(fd[1]);
    }
    
    return 0;
}
