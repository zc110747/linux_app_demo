/**********************************************************
 * 说明: 多线程的处理实现
 * 在Linux平台下，使用多线程需要在链接时加上-lpthread
 * 线程相关接口
 * 线程创建接口
 * pthread_create(tread:标识符, arr:传递属性, start_routie:函数, arg:传递线程的变量)
 * 其中arr为定义线程的默认状态,需要更大的堆栈这一类处理时需要修改
 * typedef struct
 * {
 *    int                     detachstate;     线程的分离状态 
 *    int                     schedpolicy;     线程调度策略
 *    struct sched_param      schedparam;      线程的调度参数
 *    int                     inheritsched;    线程的继承性
 *    int                     scope;           线程的作用域
 *    size_t                  guardsize;       线程栈末尾的警戒缓冲区大小
 *    int                     stackaddr_set;
 *    void *                  stackaddr;       线程栈的位置
 *    size_t                  stacksize;       线程栈的大小
 * }pthread_attr_t;
 * 设置线程的属性: pthread_attr_init
 * 等待线程的结束: pthread_join(pthread_t thread, void **retval)
 *                retval用来存储线程的返回值
 * 获取线程本身的标识符: pthread_self
 * 分离线程, 此时与主线程无关: pthread_detach
 * 线程同步机制
 * 互斥量 pthread_mutex_t m_lock;
 * pthread_mutex_destroy(&m_lock);
 * pthread_mutex_lock(&m_lock)
 * pthread_mutex_unlock(&m_lock);
 * 自旋锁
 * pthread_spinlock_t m_spinlock;
 * pthread_spin_destroy(&m_spinlock);
 * pthread_spin_lock(&m_spinlock);
 * pthread_spin_trylock(&m_spinlock);
 * pthread_spin_unlock(&m_spinlock);
************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

class CAppConfig
{
public:
    CAppConfig(std::vector<int> &vi_val, std::vector<std::string> &vs_val)
    {
        m_vi_val = std::move(vi_val);
        m_vs_val = std::move(vs_val);
        if(pthread_mutex_init(&m_lock, NULL) != 0)
        {
            cout<<"mutex init failed"<<endl;
        }
    }   
    ~CAppConfig(){
        pthread_mutex_destroy(&m_lock);
    }

    void ShowAppVal()
    {
        //互斥量加锁
        pthread_mutex_lock(&m_lock);
        cout<<"vector int:";
        for(auto &x:m_vi_val)
        {
            cout<<x<<" ";
        }
        cout<<endl;

        cout<<"vector string:";
        for(auto iter=m_vs_val.begin(); iter!=m_vs_val.end(); iter++)
        {
            cout<<*iter<<" ";
        }
        cout<<endl;
        pthread_mutex_unlock(&m_lock);
    }
 
    void ModifyVal(std::vector<int> &vi_val, std::vector<std::string> &vs_val)
    {
        pthread_mutex_lock(&m_lock);
        m_vi_val = std::move(vi_val);
        m_vs_val = std::move(vs_val);
        pthread_mutex_unlock(&m_lock);
    }
private:
    std::vector<int> m_vi_val;
    std::vector<std::string> m_vs_val;
    pthread_mutex_t m_lock;
};


void *thread_loop_func0(void *arg);

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    int ret;
    std::vector<int> vi_val = {1, 2, 3, 4};
    std::vector<std::string> vs_val = {"11", "22", "33"};
    CAppConfig pSAppConfig(vi_val, vs_val);

    //修改Pthread的启动属性
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&tid, &attr, thread_loop_func0, &pSAppConfig);
    if(ret == 0) {
        
        sleep(1);
        
        //等待线程返回
        int ret = pthread_join(tid, NULL);
        if(ret == 0) {
            cout<<"thread join success"<<endl;
        } else {
            cout<<"thread join failed:"<<ret<<endl;
        }
        
    } else {
        cout<<"thread create failed, id:"<<ret<<endl;
        return ret;
    }
    
    return 0;
}

void *thread_loop_func0(void *arg)
{
    class CAppConfig* pSAppCofig = (class CAppConfig *)arg;

    pSAppCofig->ShowAppVal();
    cout<<"thread pid:"<<std::hex<<pthread_self()<<endl;

    pthread_detach(pthread_self()); //分离线程, 此时线程与创建的进程无关，后续执行join返回值22
    pthread_exit((void *)0);
}
