/**********************************************************
 * 说明: 多进程应用的创建和应用
 * 可参考pipe的应用同步学习
 * fork 系统调用创建和原进程资源一致的的新进程(会复制资源重新分配)
 * getpid 获取当前进程的pid信息
 * getppid 获取当前进程的父进程pid信息
************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t system_pid;
    int count = 0;

    system_pid = fork();
    if (system_pid < 0) {
        printf("fork error:%s\n", strerror(errno));
    }
    else if (system_pid == 0) {
        count += 1;
        printf("child process, pid_id:%d\n", getpid());
        printf("father's pid_id:%d\n", getppid());
    } else {
        count += 2;
        printf("father process, pid_id:%d\n", getpid());
    }
    
    printf("process finish:%d\n", count);
    return 0;
}


