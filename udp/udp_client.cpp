/**********************************************************
 * 说明: udp客户端应用
 * udp主要涉及接口包含
 * socket 创建socket接口的实现
 * sendto UDP数据发送
 * recvfrom UDP数据接收
 * close socket连接关闭
 * 注意:默认配置下recvfrom读取会清除接收缓存，分多次接收需要修改
 * flag
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
    struct sockaddr_in servaddr;
    int recv_len;
    char sendbuf[1024] = "udp send hello world!";
    char recvbuf[1024] = {0};

    /*创建socket接口, SOCK_DGRAM表示无连接的udp接口*/
    if ((socket_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket init err\n");
        return socket_fd;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(net_port);
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);        

    /*通过udp通道发送数据到服务器*/
    printf("client send:%s, len:%d\n",sendbuf, (int)strlen(sendbuf));
    sendto(socket_fd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));  
    
    /*等待服务器返回数据*/
    recv_len = recvfrom(socket_fd, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
    if (recv_len == -1)
    {
        printf("socket receive error\n");
    }
    else
    {
        printf("client recv:%s, len:%d\n", recvbuf, recv_len);
    }
    close(socket_fd);
    return 0;
}
