
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "tcp_server.h"
#include "tcp_client.h"

#define TCP_PORT        8090
#define IPADDRESS       "172.27.83.254"

int main(int argc, char **argv)
{
    int result;
    pid_t system_pid;

    /*后台守护进程*/
    result = daemon(1, 1);
	if (result < 0) {
		printf("daemon\n");
		return result;
	}
	
    system_pid = fork();
    if (system_pid < 0) {
        printf("fork error:%s\n", strerror(errno));
    }
    else if (system_pid == 0) {
        tcp_server_task(IPADDRESS, TCP_PORT);
    } else {
        sleep(1);
        tcp_client_task(IPADDRESS, TCP_PORT);
    }
    
    return 0;
}