/**********************************************************
 * 说明: 消息队列的运用(服务器端)
 * 消息队列可以用于所有进程间的数据通讯，即使是非公共祖先，
 * 消息队列是消息的列表，存储在内核中
 * msgget 创建消息队列
 * msgrcv 从消息队列中读取数据
 * msgsnd  向消息队列中写入数据
 * msgctrl 操作消息队列的实现
 * 删除消息的脚本:
 * ipcs -q | grep '^[0-9]' | awk '{system("ipcrm msg "$2"")}'
 * 消息队列代码在WSL上测试不成功
************************************************************/
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //for strerror

#define MESSAGE_QUEUE_ID  2345

struct msgsys
{
    long mtype;
    int size;
    char text[512];
};

int main(int argc, char* argv[])
{
    int  result, nMsgId;   
    struct msgsys nMsgSys;
    int nSize;

    /*后台守护进程*/
    result = daemon(1, 1);
	if(result < 0)
	{
		printf("daemon error\n");
		return result;
	}

    //申请消息队列
    nMsgId = msgget((key_t)MESSAGE_QUEUE_ID, 0666 | IPC_CREAT);
    if(nMsgId == -1)
    {
        printf("msg queue create failed, error:%s", strerror(errno));
        return result;
    }

    while(1)
    {
        //type: 0返回消息队列中的第一条消息，>0返回队列中mtype等于该值的消息
        //<0返回mtype绝对值最小的消息
        if ((nSize = msgrcv(nMsgId, (void *)&nMsgSys, BUFSIZ, 0, 0)) != -1)
        {
            printf("server queue recv data: %s, %d\n", nMsgSys.text, nSize);
            nMsgSys.mtype = 1;
            nMsgSys.size = strlen("server send queue msg");
            memcpy(nMsgSys.text, "server send queue msg", nMsgSys.size);
            msgsnd(nMsgId, (void *)&nMsgSys, nSize, 0);
        }
    }

    //控制删除消息队列
    msgctl(nMsgId, IPC_RMID, 0);
    exit(0);
}