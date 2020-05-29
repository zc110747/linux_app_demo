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

 
void echo_cli(int sock)
{

}

int main(void)
{
    int sock;
    struct sockaddr_in servaddr;
    int ret;
    char sendbuf[1024] = "udp send hello world!";
    char recvbuf[1024] = {0};

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket err\n");
        return sock;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(net_port);
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);        

    /*通过udp通道发送数据到服务器*/
    printf("client send:%s, len:%d\n",sendbuf, (int)strlen(sendbuf));
    sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));  
    
    /*等待服务器返回数据*/
    ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
    if (ret == -1)
    {
        printf("socket receive error\n");
        close(sock);
        return -1;
    }
    else
    {
        printf("client recv:%s\n",recvbuf);
    }
    close(sock);
    return 0;
}
