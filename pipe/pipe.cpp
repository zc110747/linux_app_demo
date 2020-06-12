/**********************************************************
 * 说明: pipe管道的应用
 * 
 * 
************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

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
