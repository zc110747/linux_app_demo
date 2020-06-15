/**********************************************************
 * 说明: 用于进程执行的软件定时器, 支持秒级或者毫秒级的触发延时
 * 因为Linux并非实时操作系统，即使使用itimerval定时器也不能保证
 * 微秒级的有效精度。
 * signal 设置需要捕获的信号和信号捕获后的触发函数
 * setitimer 设置定时器的类型和配置启动
************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

static int count = 0;

void TimerSignalHandler(int signo)
{
    printf("SigAlm Counts:%d\n", ++count);
}

int main(int argc, char* argv[])
{
    struct itimerval tick = {0};
    
    signal(SIGALRM, TimerSignalHandler);

    //初始执行的定时器计数值
    tick.it_value.tv_sec = 1;
    tick.it_value.tv_usec = 0;

    //后续定时器执行的加载值
    tick.it_interval.tv_sec = 1;
    tick.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
        printf("Set timer failed!\n");

    while(1)
    {
        pause();
    }
    return 0;
}
