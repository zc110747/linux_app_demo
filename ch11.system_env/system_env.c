/**********************************************************
 * 说明: 多进程应用的创建和应用
 * getenv 获取系统环境变量的值
 * setenv 添加和修改环境变量
 * unsetenv 删除环境变量
 * putenv 写入环境变量，覆盖或者添加
 * system 执行调用其它程序
************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    //读取系统环境变量
    printf("PATH:%s\n", getenv("PATH"));

    //设置系统环境变量
    setenv("TestEnv", "Test Set Env", 1);
    printf("TestEnv:%s\n", getenv("TestEnv"));

    //删除环境变量
    unsetenv("TestEnv");
    printf("TestEnv:%s\n", getenv("TestEnv"));

    //写入环境变量
    putenv((char *)"TestEnv=Test Put Env");
    printf("System Env - TestEnv:%s\n", getenv("TestEnv"));

    return 0;
}


