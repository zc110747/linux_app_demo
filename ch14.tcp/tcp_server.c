﻿/**********************************************************
 * 说明: tcp客户端应用
 * tcp应用主要涉及接口包含
 * socket 创建socket接口的实现
 * bind 绑定网络通讯到指定的网络端口
 * accept 等待客户端的网络连接
 * send TCP数据发送
 * recv TCP数据接收
 * close socket连接关闭
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

#define socket_max_listen   32

int tcp_server_task(char *ipaddr, int port)
{    
    int socket_fd, result, recv_len;   
    char recvbuf[1024] = {0};  
    struct sockaddr_in servaddr, clientaddr;  
    socklen_t client_sock_len;
	
    // 创建socket接口, SOCK_STREAM表示TCP连接
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {     
        printf("socket init error\n");    
        return socket_fd;    
    }

    // 绑定socket接口到指定的ip地址和端口(必须为本机IP或者127.0.0.1循环地址)
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;     
    servaddr.sin_addr.s_addr = inet_addr(ipaddr);  
    servaddr.sin_port = htons(port);

    // 配置运行绑定在TIME_WAIT的接口
    int flag = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1) {
        printf("setsockopt failed.\n");
        return -1;
    }

    do 
    {
        if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {      
            printf("socket bind error\n");
            sleep(5);
            return -1;       
        } else {
            printf("bind ok, server ip:%s, net_port:%d\n", ipaddr, port);
            break;  
        }
    }while(1);

    //监听socket通讯
    listen(socket_fd, socket_max_listen);

    while (1) {       
        int client_fd;
        uint32_t client_size; 

        client_size = sizeof(clientaddr);
        //等待客户端的TCP进行三次握手连接
        client_fd = accept(socket_fd, (struct sockaddr *)&clientaddr, &client_size);
        if (client_fd < 0) {
            printf("socket accept failed\n");
            continue;
        } else
        {
            memset(recvbuf, 0, sizeof(recvbuf));
            //接收客户端发送的数据
            recv_len = recv(client_fd, recvbuf, sizeof(recvbuf), 0);
            if (recv_len <= 0)        
            {        
                printf("server recv failed\n");
            }
            else
            {
                printf("server recv:%s, recv len:%d\n", recvbuf, recv_len);
                //将数据返回给客户端
                send(client_fd, recvbuf, recv_len, 0);
            }
            printf("socket process success\r\n");
            //TCP四次握手断开
            close(client_fd);
        }         
    }    
    close(socket_fd);     
    return 0;
}
