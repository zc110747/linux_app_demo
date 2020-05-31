#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h> 
#include<arpa/inet.h>

#define net_port            8000
#define ip_addr             "127.0.0.1"
#define socket_max_listen   32

int main(void)
{    
    int socket_fd, result, recv_len;   
    char recvbuf[1024] = {0};  
    struct sockaddr_in servaddr, clientaddr;  
    socklen_t client_sock_len;      

    /*后台守护进程*/
    result = daemon(1, 1);
	if(result < 0)
	{
		printf("daemon\n");
		return result;
	}
	
    /*创建socket接口, SOCK_STREAM表示TCP连接*/
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
    {     
        printf("socket init error\n");    
        return socket_fd;    
    }

    /*绑定socket接口到指定的ip地址和端口(必须为本机IP或者127.0.0.1循环地址)*/
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;     
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);  
    servaddr.sin_port = htons(net_port);         
    if (bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)  
    {      
        printf("socket bind error\n");
        return -1;       
    }
    printf("bind ok, server ip:%s, net_port:%d\n",ip_addr, net_port);    

    //监听socket通讯
    listen(socket_fd, socket_max_listen);
    while (1)    
    {       
        int client_fd;
        uint32_t client_size; 

        client_size = sizeof(clientaddr);
        //等待客户端的TCP进行三次握手连接
        client_fd = accept(socket_fd, (struct sockaddr *)&clientaddr, &client_size);
        if(client_fd < 0)
        {
            printf("socket accept failed\n");
            continue;
        }
        else
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
