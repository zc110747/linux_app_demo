//文件的读写操作
//涉及接口open, close, read, write, lseek
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
