/**********************************************************
 * 说明: udp服务器应用
 * udp主要涉及接口包含
 * socket 创建socket接口的实现
 * bind 绑定UDP通讯到指定的网络端口
 * recvfrom UDP数据接收
 * sendto UDP数据发送
 * close socket连接关闭
 * 注意:默认配置下recvfrom读取会清除接收缓存，需要多次读取需要修改读取flag
************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h> 
#include<arpa/inet.h>

int udp_server_task(char *ipaddr, int port)
{    
    int socket_fd, result, recv_len;   
    char recvbuf[1024] = {0};  
    struct sockaddr_in servaddr, clientaddr;  
    socklen_t client_sock_len;      

    /*创建socket接口, SOCK_DGRAM表示无连接的udp接口*/
    if ((socket_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {     
        printf("socket init error\n");    
        return socket_fd;    
    }

    /*绑定到指定端口*/
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;     
    servaddr.sin_addr.s_addr = inet_addr(ipaddr);  
    servaddr.sin_port = htons(port);         
    if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {      
        printf("socket bind error\n");
        return -1;       
    }
    printf("bind ok, server ip:%s, net_port:%d\n", ipaddr, port);  
      
    while (1) {

        client_sock_len = sizeof(clientaddr);        
        memset(recvbuf, 0, sizeof(recvbuf));     

        //接收客户端UDP的数据 
        recv_len = recvfrom(socket_fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&clientaddr, &client_sock_len);        
        if (recv_len <= 0) {                                                      
            printf("socket recvfrom error\n");  
            continue;          
        } else if (recv_len > 0)        
        {           
            printf("server recv:%s, recv len:%d\n", recvbuf, recv_len); 
            //返回数据给客户端           
            sendto(socket_fd, recvbuf, recv_len, 0, (struct sockaddr *)&clientaddr, client_sock_len);            
        }    
    }    
    close(socket_fd);     
    
    return 0;
}
