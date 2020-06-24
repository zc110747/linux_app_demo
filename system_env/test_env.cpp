/**********************************************************
 * 说明: 多进程应用的创建和应用
 * getenv 获取系统环境变量的值
************************************************************/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Test Env - TestEnv:%s\n", getenv("TestEnv"));
    
    return 0;
}