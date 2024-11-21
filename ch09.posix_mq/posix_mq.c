/**********************************************************
 * 说明: 多线程通讯的Posix消息队列实现
 * 使用mq_xx的消息队列接口编译时需要添加-lrt
 * 在了解mq_xx相关信息时，需要掌握一定的线程相关的知识
 * 代码在WSL、WSL2无法正常运行，实际Ubuntu系统工作正常
 * mq_unlink    删除已经存在的消息队列, 否则无法重新创建
 * mq_open      打开或者创建一个消息队列
 * mq_close     关闭消息队列
 * mq_receive   等待消息队列有消息接收
 * mq_send      投递数据给消息队列
 * mq_getattr   获取消息队列的具体参数信息
************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MQ_NAME     "/var/tmp/mqfile"

mqd_t mqd_info;

void *thread_loop_func0(void *arg);

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    struct mq_attr mq_attr_info;
    char *pbuffer;
    int nReadSize;
    unsigned int prio;

    mq_attr_info.mq_maxmsg = 12;
    mq_attr_info.mq_msgsize = 128;

    //创建消息队列
    mq_unlink(MQ_NAME);
    mqd_info = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0666, &mq_attr_info);
    if (mqd_info < 0) {
        printf("mq_open failed, err:%s\n", strerror(errno));
        return errno;
    }

    //获取队列的属性
    mq_getattr(mqd_info, &mq_attr_info);
    if (mq_attr_info.mq_msgsize != 0) {
        printf("msgsize:%d, maxmsg:%d\n", (int)mq_attr_info.mq_msgsize, (int)mq_attr_info.mq_maxmsg);
        
        pbuffer = (char *)malloc(mq_attr_info.mq_msgsize);
        if (pbuffer == NULL) {
            printf("malloc error\n");
        }
        memset(pbuffer, 0, mq_attr_info.mq_msgsize);
    } else {
        printf("mq msgsize is zero\n");
        close(mqd_info);
        return -1;
    }

    //修改Pthread的启动属性
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, thread_loop_func0, NULL);

    //从队列等待消息回复
    nReadSize = mq_receive(mqd_info, pbuffer, mq_attr_info.mq_msgsize, &prio);
    if (nReadSize > 0) {
        printf("receive:%s, len:%d\n", pbuffer, nReadSize);
    }

    printf("test success, finish\n");

    free(pbuffer);
    mq_close(mqd_info); 
    return 0;
}

void *thread_loop_func0(void *arg)
{
    printf("thread start ok\n");

    //向队列投递消息
    if (mq_send(mqd_info, "mq\n", strlen("mq\n"), 0) < 0) {
        printf("mq send error:%s\n", strerror(errno));
        mq_close(mqd_info);
    }
    pthread_detach(pthread_self()); //分离线程, 此时线程与创建的进程无关，后续执行join返回值22
    pthread_exit((void *)0);
}
