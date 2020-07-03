/**********************************************************
 * 说明: epoll服务器端应用
 * 涉及接口有
 * epoll_create  创建epoll句柄
 * epoll_ctrl   对epoll句柄进行数据处理
 * epoll_wait   等待epoll事件触发信息，进行后续处理
 * close        关闭epoll句柄，释放资源
************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h> 
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<poll.h>
#include <sys/epoll.h>

#define net_port            8000
#define ip_addr             "127.0.0.1"
#define socket_max_listen   32
#define MAX_BUFSIZE         512
#define EPOLL_MAX_WAIT      128

char recvbuf[MAX_BUFSIZE] = {0};  
int main(void)
{    
    int result, recv_len;   
    int server_fd, epoll_fd;
    int event_fd;
    socklen_t client_sock_len;      
    struct sockaddr_in server_addr, client_addr;  
    struct epoll_event ep_event, ep_event_arr[socket_max_listen];

    /*后台守护进程*/
    result = daemon(1, 1);
	if(result < 0)
	{
		printf("daemon\n");
		return result;
	}
	
    /*创建socket接口, SOCK_STREAM表示TCP连接*/
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
    {     
        printf("socket init error\n");    
        return server_fd;    
    }

    /*绑定socket接口到指定的ip地址和端口(必须为本机IP或者127.0.0.1循环地址)*/
    memset(&server_addr, 0, sizeof(server_addr));    
    server_addr.sin_family = AF_INET;     
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);  
    server_addr.sin_port = htons(net_port);         
    
    ep_event.data.fd = server_fd;
    ep_event.events = EPOLLIN | EPOLLET;
    epoll_fd = epoll_create(10);
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ep_event);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)  
    {      
        printf("Socket Bind Error, %s\n", strerror(errno));
        return -1;       
    }
    listen(server_fd, socket_max_listen);

    for(;;)
    {
        event_fd = epoll_wait(epoll_fd, ep_event_arr, EPOLL_MAX_WAIT, -1);
        for(int index=0; index<event_fd; index++)
        {
            if(ep_event_arr[index].data.fd == server_fd)
            {
                int client_fd;
                socklen_t client_size = sizeof(client_addr);
                client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_size);
                if(client_fd < 0)
                {
                    printf("Socket Accept Error, error:%s\n", strerror(errno));
                    continue;
                }
                ep_event.data.fd = client_fd;
                ep_event.events =  EPOLLIN|EPOLLET;
                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ep_event) < 0)
                {
                    printf("Epoll Ctl Error, Error:%s\n", strerror(errno));
                    result = -1;
                    return result;
                }
            }
            else
            {
                int nSize;
                int client_fd;
                
                client_fd = ep_event_arr[index].data.fd;
                if(ep_event_arr[index].events & EPOLLIN)
                {
                    bzero(recvbuf, MAX_BUFSIZE);
                    nSize = read(client_fd, recvbuf, MAX_BUFSIZE);
                    if(nSize < 0)
                    {
                        close(client_fd);
                        printf("Socket Read Error, error:%s\n", strerror(errno));
                        result = -1;
                        return result;
                    }
                    else if(nSize == 0)
                    {
                        close(client_fd);
                        printf("Socket Close By Client\n");
                    }
                    else
                    {
                        printf("Server Recv Val:%s, Size:%d\n", recvbuf, nSize);
                        ep_event.data.fd = client_fd;
						ep_event.events = EPOLLOUT|EPOLLET;
						epoll_ctl(epoll_fd, EPOLL_CTL_MOD, client_fd, &ep_event);
                    }
                }
                if(ep_event_arr[index].events & EPOLLOUT)
                {
                    printf("Server Send Val:%s, size:%d\n", "server send test", (int)strlen("server send test"));
                    nSize = write(client_fd, "server send test", strlen("server send test")); 
                    if(nSize < 0)
                    {
                        close(client_fd);
                        printf("Socket Read Error, error:%s\n", strerror(errno));
                        result = -1;
                        return result;
                    }
                    else if(nSize == 0)
                    {
                        close(client_fd);
                        printf("Socket Close By Client\n");
                    }
                    else
                    {
                        ep_event.data.fd = client_fd;
						ep_event.events = EPOLLIN|EPOLLET;
						epoll_ctl(epoll_fd, EPOLL_CTL_MOD, client_fd, &ep_event);
                    }            
                }
            }
            
        }
    }

    close(server_fd);
    close(epoll_fd);
    return result;
}
