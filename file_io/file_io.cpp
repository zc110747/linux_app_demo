/**********************************************************
 * 说明: 文件读写接口
 * 文件I/O主要涉及接口包含
 * open 打开文件描述符
 * lseek 移动文件指针位置,进行偏移
 * ioctl 操作硬件设备的命令
 * read  读取文件数据或者设备内数据
 * write 将数据写入文件缓冲区或者设备中
 * close 关闭文件
************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define FILE_NAME       "test.xml"
#define FILE_DEST_NAME  "test_dest.xml"
#define CACHE_BUF_SIZE  1024
unsigned char Cachebuf[CACHE_BUF_SIZE];

int main(int argc, char* argv[])
{
    int nFileFdSrc, nFileFdDst;
    int nLen;

    //打开文件，获得文件句柄 分别指文件名，
    nFileFdSrc = open(FILE_NAME, O_RDONLY, 0666);
    if(nFileFdSrc < 0){
        printf("open file %s failed\n", FILE_NAME);
        return nFileFdSrc;
    }
    printf("open file %s successed\n", FILE_NAME);

    //读写打开
    nFileFdDst = open(FILE_DEST_NAME, O_RDWR | O_CREAT, 0666);
    if(nFileFdSrc < 0){
        printf("open file %s failed\n", FILE_DEST_NAME);
        return nFileFdSrc;
    }
    printf("open file %s successed\n", FILE_DEST_NAME);

    //移动文件指针位置,进行后续操作
    lseek(nFileFdSrc, 0, SEEK_SET);
    lseek(nFileFdDst, 0, SEEK_SET);
    //从源文件读取数据，并写入到目的文件中
    while((nLen = read(nFileFdSrc, Cachebuf, sizeof(Cachebuf)))>0)
    {   
        Cachebuf[nLen] = '\0';
        printf("recv buf:\n%s\n", Cachebuf);
        write(nFileFdDst, Cachebuf, nLen);
    }

    lseek(nFileFdDst, 0, SEEK_SET);
    while((nLen = read(nFileFdDst, Cachebuf, sizeof(Cachebuf)))>0)
    {   
        Cachebuf[nLen] = '\0';
        printf("recv buf:\n%s\n", Cachebuf);
    }

    close(nFileFdSrc);
    close(nFileFdDst);
}
