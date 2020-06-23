/**********************************************************
 * 说明: 涉及到Linux基础管理的API
 * 包含文件夹处理
 * opendir/readdir/closedir 打开.读取,关闭文件夹信息(dirent.h)
 * mkdir 带权限创建文件夹(sys/stat.h)
 * getpid/getuid 获得进程的id和组id
 * perror 测试错误输出
 * getopt/optarg 解析命令行参数
 * time 获取当前的time信息
************************************************************/
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#define TEST_DIR  "test_dir"
#define TEST_DIR1 "test_dir/test_dir2"

int process_dir(void)
{
    DIR *pDir;
    struct dirent *pdirent;

    pDir = opendir(TEST_DIR);
    if(pDir == NULL){
        printf("open %s filed, error:%s\n", TEST_DIR, strerror(errno));
        return -1;
    } 

    while((pdirent = readdir(pDir)) != NULL){
        printf("%s\n", pdirent->d_name);
    }
    closedir(pDir);

    pDir = opendir(TEST_DIR1);
    if(pDir == NULL){
        mkdir(TEST_DIR1, 0755);
    }else{
        printf("open %s succes\n", TEST_DIR1);
        closedir(pDir);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    time_t current_time[2];
    int c;
    
    time(&current_time[0]);

    //opt
    //:表示后面必须带参数, ::表示不一定带参数
    while((c = getopt(argc, argv, "v::h:"))!= -1){
        switch(c){
            case 'v':
                printf("version 0.0.1\n");
            break;
            case 'h':
                if(optarg != NULL){
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

    //getpid, getuid
    printf("pid:%d, uid:%d\n", getpid(), getuid());
    
    //perror
    fprintf(stderr, "EACCESS:%s\n", strerror(EACCES));
    errno = ENOENT;
    perror("test error:");

    time(&current_time[1]);
    printf("timer is:%ds\n", (int)(current_time[1]-current_time[0]));

    return 0;
}
