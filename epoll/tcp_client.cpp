/**********************************************************
 * 说明: tcp客户端应用
 * tcp应用主要涉及接口包含
 * socket 创建socket接口的实现
 * connect 连接到指定的网络端口
 * send TCP数据发送
 * recv TCP数据接收
 * close socket连接关闭
************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define net_port 	8000
#define ip_addr     "127.0.0.1"

int main(int argc, char* argv[])
{
    int socket_fd;
    struct sockaddr_in server_addr;
    int ret, recv_len;
    char sendbuf[1024] = "no copy tcp send hello world!";
    char recvbuf[1024] = {0};

    /*创建socket接口, SOCK_STREAM表示TCP连接*/
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket Init Err, Error:%s\n", strerror(errno));
        return socket_fd;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(net_port);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);        

    //连接到服务器
    ret = connect(socket_fd,(struct sockaddr*)(&server_addr), sizeof(server_addr));
    if(ret < 0)
    {
        printf("Copy Socket Connect Err, Error:%s\n", strerror(errno));
        return ret;
    }
    
    //发送数据到服务器
    //for(int index=1; index<100; index++)
    {
        printf("Client Send:%s, Size:%d\n",sendbuf, (int)strlen(sendbuf));
        send(socket_fd, sendbuf, strlen(sendbuf), 0);

        //读取从服务器返回的数据
        recv_len = recv(socket_fd, recvbuf, sizeof(recvbuf), 0);
        if (recv_len <= 0)        
        {        
            printf("Client Recv Failed, Error:%s\n", strerror(errno));
        }
        else
        {
            printf("Client Recv:%s, Recv Size:%d\n", recvbuf, recv_len);
        }
        sleep(5);
    }

    //关闭连接
    close(socket_fd);
    return 0;
}
