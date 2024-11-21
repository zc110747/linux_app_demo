/**********************************************************
 * 说明: 涉及到Linux基础管理的API
 * 包含文件夹处理
 * opendir/readdir/closedir 打开.读取,关闭文件夹信息(dirent.h)
 * fstat 获取文件信息
 * mkdir 带权限创建文件夹(sys/stat.h)
 * getpid/getuid 获得进程的id和组id
 * perror 测试错误输出
 * strerror 将错误码转换为错误字符串
 * getopt/optarg 解析命令行参数
 * time 获取当前的time信息
************************************************************/
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>

#define TEST_DIR  "test_dir"
#define TEST_DIR1 "test_dir/test_dir2"
#define TEST_FILE "test_dir/test_file"

static char filepath[3][100];

int process_dir(void)
{
    DIR *pDir;
    struct dirent *pdirent;

    printf("------ process_dir test ------\n");

    pDir = opendir(filepath[0]);
    if (pDir == NULL) {
        printf("open %s filed, err:%s\n", filepath[0], strerror(errno));
        return -1;
    }
    while ((pdirent = readdir(pDir)) != NULL) {
        printf("%s\n", pdirent->d_name);
    }
    closedir(pDir);

    pDir = opendir(filepath[1]);
    if (pDir == NULL) {
        mkdir(filepath[1], 0755);
    } else {
        printf("open %s success\n", filepath[1]);
        closedir(pDir);
    }
    return 0;
}

int file_stats_test(void)
{
    int fd;
    int ret;
    struct stat file_stat;

    fd = open(filepath[2], O_RDONLY);
    if (-1 == fd) {
        perror("open error");
        exit(-1);
    }

    ret = fstat(fd, &file_stat);
    if (-1 == ret) {
        perror("fstat error");
        close(fd);
        exit(-1);
    }

    printf("File size: %lld bytes\n", (long long)file_stat.st_size);

    close(fd);
    return 0;
}

int main(int argc, char *argv[])
{
    time_t current_time[2];
    int c;
    
    time(&current_time[0]);

    if (argc == 2) {
        sprintf(filepath[0], "%s/%s", argv[1], TEST_DIR);
        sprintf(filepath[1], "%s/%s", argv[1], TEST_DIR1);
        sprintf(filepath[2], "%s/%s", argv[1], TEST_FILE);
    } else {
        sprintf(filepath[0], "%s", TEST_DIR);
        sprintf(filepath[1], "%s", TEST_DIR1);
        sprintf(filepath[2], "%s", argv[1], TEST_FILE);
    }

    //opt
    //:表示后面必须带参数, ::表示不一定带参数
    while ((c = getopt(argc, argv, "v::h:"))!= -1) {
        switch(c){
            case 'v':
                printf("version 0.0.1\n");
            break;
            case 'h':
                if(optarg != NULL) {
                    printf("input:%s\n", optarg);
                }
            break;
            default:
                printf("no valid flag input\n");
            break;
        }
    }

    //dir
    process_dir();

    //fstat
    file_stats_test();

    //getpid, getuid
    {
        printf("pid:%d, ppid:%d, uid:%d\n", getpid(), getppid(), getuid());
        printf("pgrp:%d\n", getpgrp());
    }

    //perror
    fprintf(stderr, "EACCESS:%s\n", strerror(EACCES));
    errno = ENOENT;
    perror("test error");

    //time
    sleep(1);
    time(&current_time[1]);
    printf("timer is:%ds\n", (int)(current_time[1]-current_time[0]));

    return 0;
}
