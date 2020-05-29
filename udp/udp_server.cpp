#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h> 
#include<arpa/inet.h>

#define net_port    8000
#define ip_addr     "127.0.0.1"
    
int main(void)
{    
    int sock, result, recv_len;   
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
	
    /*创建socket接口, SOCK_DGRAM表示无连接的udp接口*/
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) 
    {     
        printf("socket error\n");    
        return sock;    
    }

    /*绑定socket接口到指定的ip地址和端口(必须为本机IP或者127.0.0.1循环地址)*/
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;     
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);  
    servaddr.sin_port = htons(net_port);         
    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)  
    {      
        printf("bind error\n");
        return -1;       
    }
    printf("bind ok, server ip:%s, net_port:%d\n",ip_addr, net_port);    

    while (1)    
    {                
        client_sock_len = sizeof(clientaddr);        
        memset(recvbuf, 0, sizeof(recvbuf));     
        /*循环等待Socket UDP的数据接收 返回负值表示接收错误*/   
        recv_len = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&clientaddr, &client_sock_len);        
        if (recv_len <= 0)        
        {                        
            if (errno == EINTR)               
                continue;                       
            printf("recvfrom error\n");       
        }       
        else if(recv_len > 0)        
        {           
            printf("server recv:%s, recv len:%d\n", recvbuf, recv_len);            
            /*将接收数据通过udp发出*/
            sendto(sock, recvbuf, recv_len, 0, (struct sockaddr *)&clientaddr, client_sock_len);            
        }    
    }    
    close(sock);     
    return 0;
}
