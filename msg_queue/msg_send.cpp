/**********************************************************
 * 说明: 消息队列的运用(客户端)
 * 消息队列可以用于所有进程间的数据通讯，即使是非公共祖先，
 * 消息队列是消息的列表，存储在内核中
 * msgget 创建消息队列
 * msgrcv 从消息队列中读取数据
 * msgsnd  向消息队列中写入数据
 * msgctrl 操作消息队列的实现
************************************************************/
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

    //申请消息队列
    nMsgId = msgget((key_t)MESSAGE_QUEUE_ID, 0666 | IPC_CREAT);
    if(nMsgId == -1)
    {
        printf("msg queue create failed");
        return result;
    }

    nMsgSys.mtype = 1;
    nMsgSys.size = strlen("client send queue msg");
    memcpy((char *)nMsgSys.text,"client send queue msg", nMsgSys.size);

    //消息数据发送  
    msgsnd(nMsgId, (void *)&nMsgSys, nMsgSys.size+8, 0);
    if ((nSize = msgrcv(nMsgId, (void *)&nMsgSys, BUFSIZ, 0, 0)) != -1)
    {
        printf("client recv data: %s, size:%d\n", nMsgSys.text, nSize);
    }

    exit(0);
}