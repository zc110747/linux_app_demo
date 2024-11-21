
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "udp_server.h"
#include "udp_client.h"

#define UDP_PORT        8000
#define IPADDRESS       "127.0.0.1"

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
        udp_server_task(IPADDRESS, UDP_PORT);
    } else {
        sleep(1);
        udp_client_task(IPADDRESS, UDP_PORT);
    }
    
    return 0;
}