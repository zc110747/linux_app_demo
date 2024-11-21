/**********************************************************
 * 说明: 文件读写接口
 * 文件I/O主要涉及接口包含
 * open 打开文件描述符
 *      int open(const char *pathname, int flags);
 *      int open(const char *pathname, int flags, mode_t mode);
 *          flags:表示文件打开方式，常用的O_RDONLY, O_WRONLY, O_RDWR，另外
 *                O_NONBLOCK、O_NDELAY指定非堵塞，O_TRUNC指定文件重新写入，原数据丢弃。
 *          mode:指定文件的权限位，受umask的影响
 * close 关闭文件描述符
 * lseek 移动文件指针位置,进行偏移
 * ioctl 操作硬件设备的命令
 * read  读取文件数据或者设备内数据
 * write 将数据写入文件缓冲区或者设备中
************************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define FILE_NAME       "files/test.xml"
#define FILE_DEST_NAME  "files/test_dest.xml"
#define CACHE_BUF_SIZE  1024

static unsigned char buffer[CACHE_BUF_SIZE];
static char path_list[2][200];

int file_open_demo(void)
{
    int nFileFdSrc, nFileFdDst;
    int nLen;

    printf("------ file_open_demo ------\n");

    //打开文件，获得文件句柄 分别指文件名，
    nFileFdSrc = open(path_list[0], O_RDONLY, 0666);
    if (nFileFdSrc < 0) {
        printf("open file %s failed\n", FILE_NAME);
        return nFileFdSrc;
    }
    printf("open file %s successed\n", FILE_NAME);

    //读写打开
    nFileFdDst = open(path_list[1], O_RDWR | O_CREAT, 0666);
    if (nFileFdSrc < 0) {
        printf("open file %s failed\n", FILE_DEST_NAME);
        return nFileFdSrc;
    }
    printf("open file %s successed\n", FILE_DEST_NAME);

    //移动文件指针位置,进行后续操作
    lseek(nFileFdSrc, 0, SEEK_SET);
    lseek(nFileFdDst, 0, SEEK_SET);
    
    //从源文件读取数据，并写入到目的文件中
    while ((nLen = read(nFileFdSrc, buffer , sizeof(buffer ))) > 0) {   
        buffer [nLen] = '\0';
        printf("recv buf:\n%s\n", buffer );
        write(nFileFdDst, buffer , nLen);
    }

    lseek(nFileFdDst, 0, SEEK_SET);
    while ((nLen = read(nFileFdDst, buffer , sizeof(buffer ))) > 0) {   
        buffer [nLen] = '\0';
        printf("recv buf:\n%s\n", buffer );
    }

    close(nFileFdSrc);
    close(nFileFdDst);

    return 0;
}

int file_fopen_demo(void)
{
    FILE *file;
    int len;

    printf("------ file_fopen_demo ------\n");

    file = fopen(path_list[0], "r");
    if (file == NULL) {
        printf("fopen can't open file!");
        return -1;
    }
    
    fseek(file, 0, SEEK_SET);
    while ((len = fread(buffer , 1, sizeof(buffer), file)) > 0) {   
        buffer[len] = '\0';
        printf("recv buf:\n%s\n", buffer );
    }
    fclose(file);
}

int main(int argc, char* argv[])
{
    if(argc == 2) {
        sprintf(path_list[0], "%s/../executables/%s", argv[1], FILE_NAME);
        sprintf(path_list[1], "%s/../executables/%s", argv[1], FILE_DEST_NAME);
    } else {
        sprintf(path_list[0], "%s", FILE_NAME);
        sprintf(path_list[1], "%s", FILE_DEST_NAME);
    }

    file_open_demo();

    file_fopen_demo();

    return 0;
}

