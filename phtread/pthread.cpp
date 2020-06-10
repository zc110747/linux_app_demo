/**********************************************************
 * 说明: 多线程的处理实现
 * 在Linux平台下，使用多线程需要在链接时加上-lpthread
 * 线程相关接口
 * pthread_create(tread:标识符, arr:传递属性, start_routie:函数, arg:线程说明)
************************************************************/
#include <pthread.h>
#include <vector>
#include <string>

struct SAppConfig
{
    std::vector<int> vector_val0;
    std::string string_val0;
};


void *thread_loop_func0(void *arg);

int main(int argc, char* argv[])
{
    pthread_t tid;
    int ret;
    struct SAppConfig pSAppConfig{{1, 2, 3, 4}, {"11", "22", "33"}}; 

    ret = pthread_create(&tid, )
    return 0;
}

void *thread_loop_func0(void *arg)
{
    pthread_detach(pthread_self());
    return (void *)0;
}
