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

int main(void)
{
    int socket_fd;
    struct sockaddr_in server_addr;
    int ret, recv_len;
    char sendbuf[1024] = "tcp send hello world!";
    char recvbuf[1024] = {0};

    /*创建socket接口, SOCK_STREAM表示TCP连接*/
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket init err\n");
        return socket_fd;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(net_port);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);        

    //连接到服务器
    printf("client send:%s, len:%d\n",sendbuf, (int)strlen(sendbuf));
    ret = connect(socket_fd,(struct sockaddr*)(&server_addr), sizeof(server_addr));
    if(ret < 0)
    {
        printf("socket connect err\n");
        return ret;
    }
    
    //发送数据到服务器
    send(socket_fd, sendbuf, strlen(sendbuf), 0);

    //读取从服务器返回的数据
    recv_len = recv(socket_fd, recvbuf, sizeof(recvbuf), 0);
    if (recv_len <= 0)        
    {        
        printf("client recv failed\n");
    }
    else
    {
        printf("client recv:%s, recv len:%d\n", recvbuf, recv_len);
    }

    //关闭连接
    close(socket_fd);
    return 0;
}
