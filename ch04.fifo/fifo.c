/**********************************************************
 * 说明: 用于进程间通讯的FIFO接口
 * FIFO指先进先出的管道，不过FIFO有名称，又被称为named pipe
 * mkfifo 创建FIFO
 * open   根据名称打开FIFO通道
 * write  向FIFO通道内写入数据
 * read   从FIFO通道内读取数据
 * close  关闭FIFO通道
 * unlink 删除FIFO通道
************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define FIFO_NAME "/tmp/1.fifo"
#define FIFO_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[])
{
    pid_t system_pid;
    int readfd, writefd;

    if (mkfifo(FIFO_NAME, FIFO_MODE) < 0) {
        if (errno != EEXIST) {
            printf("create fifo %s error:%s\n", FIFO_NAME, strerror(errno));
        }
    }

    system_pid = fork();
    if (system_pid < 0) {
        printf("system fork error\n");
    }
    else if (system_pid == 0) {
        int bytes_read;

        readfd = open(FIFO_NAME, O_RDONLY, 0);
        if (readfd > 0) {
            char buffer[40] = {0};
            bytes_read = read(readfd, buffer, 40);
            if (bytes_read > 0) {
                printf("fifo read:%s, read size:%d\n", buffer, bytes_read);
                close(readfd);
            } else {
                 printf("fifo read %s error:%s\n", FIFO_NAME, strerror(errno));
            }
        } else {
            printf("open fifo %s error:%s\n", FIFO_NAME, strerror(errno));
        }
    } else {
        int bytes_write;
        writefd = open(FIFO_NAME, O_WRONLY, 0);
        bytes_write = write(writefd, "hello fifo test", strlen("hello fifo test"));
        printf("fifo send:%s, size:%d\n", "hello fifo test", bytes_write);
        close(writefd);
    }

    unlink(FIFO_NAME);
}
