# linux c/c++ demo
用于保存Linux应用层接口和STL应用接口demo的仓库方便后续查询和使用  
仅提供相关的应用demo, 除必要的注释外不会讲解相关说明，如果有需要更深入了解，建议自行搜索以及推荐以下书籍查找
《UNIX环境高级编程》
《UNIX网络编程 卷2：进程间通信》
具体例程应用demo可查看相应的路径文件夹, 部分代码在WSL或WSL2可能执行不正常，在注释中会有相关说明。
另外，因为个人精力和时间关系，可能有遗漏不全或者错误的部分, 如果发现可以及时反馈。

## base_api Linux基础API相关接口
```cpp
//打开文件夹路径
DIR *opendir (const char *__name);
//读取路径信息
struct dirent *readdir (DIR *__dirp);
//关闭文件夹
int closedir (DIR *__dirp);
//创建文件夹
int mkdir (const char *__path, __mode_t __mode);
//获取进程ID
__pid_t getpid (void);
//获取组ID
__uid_t getuid (void);
//输出错误信息
void perror (const char *__s);
//获取当前时间信息
time_t time (time_t *__timer);
//根据解析值获取变量
int getopt (int ___argc, char *const *___argv, const char *__shortopts);
```

## cplusplus/ 和C++相关的demo例程，包含常用C++库以及STL等  
目前包含vector, list, string,
后续计划添加map, set, deque, tree等。  
stl的具体接口说明在下级目录完善  

## fifo/ Linux命名先入先出管道通讯  
用于Linux进程间通讯的命名先入先出管道
```cpp
//用于创建fifo管道的应用实现
int mkfifo (const char *__path, __mode_t __mode);
//打开FIFO管道,获取后续使用的描述符
int open(const char *pathname, int oflag,...);  
//从FIFO管道中读取数据  
ssize_t read(int fd, void * buf, size_t count);  
//向FIFO管道写入数据  
ssize_t write (int fd, const void * buf, size_t count);  
//关闭FIFO管道
int close(int fd);  
//移除FIFO管道
int unlink (const char *__name);
```  

## file_io/ Linux文件I/O操作  
Linux中设备的访问也以一切皆文件的思想存在，所以文件I/O是最常用的接口。 
```cpp
//打开文件,获得文件描述符
int open(const char *pathname, int oflag,...);  
//从文件中读取数据  
ssize_t read(int fd, void * buf, size_t count);  
//向文件中写入数据  
ssize_t write (int fd, const void * buf, size_t count);  
//关闭文件描述符  
int close(int fd);  
//移动文件指针偏移地址,和read配合使用从指定起始地址读取数据  
off_t lseek(int fildes, off_t offset, int whence);
```  

## fork/ 进程创建和应用
Linux通过fork创建进程，复制资源
```cpp
//系统调用创建和原进程资源一致的的新进程(会复制资源重新分配)
__pid_t fork(void);
//获得当前进程的pid值
__pid_t getpid(void);
//获得当前进程的父进程pid值
__pid_t getppid(void);
```

## msg_queue/ Linux进程间消息队列处理
对于任何满足权限的线程，都允许从消息队列里读取和写入消息
```cpp
//创建消息队列
int msgget(key_t key, int oflg);
//从消息队列里读取数据
ssize_t msgrcv(int msqid, void *ptr, size_t length, long type, int flag);
//创建一个新的消息队列或访问一个已存在的消息队列
int msgsnd(int msqid, const void *ptr, size_t length, int flag);
//提供在一个消息队列上的各种控制操作
int msgctl(int msqid, int cmd, struct msqid_ds *buff);
```

## pthread/ Linux多线程接口  
多线程编译需要添加-lpthread
```c
//线程的创建  
int pthread_create(pthread_t *tid, const pthread_arrt_t* attr,  
                    void*(*start_routine)(void *), void* arg);  
//等待线程的结束,非分离的线程在结束后只有执行join才会释放全部资源  
int pthread_join(pthread_t thread, void **retval);
//线程离开时的返回值(必须为malloc或者全局变量)  
void pthread_exit(void * retval);
//分离线程,被分离的线程在结束后自动释放所有资源  
int pthread_detach(pthread_t tid);
//多线程的交互--互斥量和自旋锁  
//互斥量 
pthread_mutex_t m_lock;  
pthread_mutex_destroy(&m_lock);  
thread_mutex_lock(&m_lock)  
pthread_mutex_unlock(&m_lock);  
//自旋锁  
pthread_spinlock_t m_spinlock;  
pthread_spin_destroy(&m_spinlock);  
pthread_spin_lock(&m_spinlock);  
pthread_spin_trylock(&m_spinlock);  
pthread_spin_unlock(&m_spinlock);  
```  

## pipe/ 用于进程间通讯的管道
```c
//创建pipe通道, 其中fd[0]为数据读管道描述符，fd[1]为数据写管道描述符
int pipe(int fd[2]);
//通过管道描述符从管道中读取数据  
ssize_t read(int fd, void * buf, size_t count);  
//通过管道描述符向管道中写入数据
ssize_t write (int fd, const void *buf, size_t count);  
//关闭通道的接口应用
int close(int fd);
```  

## posix_mq/ 基于posix接口的消息队列
```cpp
//删除已经存在的消息队列
int mq_unlink(const char *name);    
//打开或者创建一个消息队列
mqd_t mq_open(const char *name, int oflag, ... 
/*mode_t mode, struct mq_attr *attr*/);
//关闭消息队列  
int mq_close(mqd_t mqdes);
//获取消息队列的具体参数信息
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
//投递数据给消息队列
int mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);
//等待消息队列有消息接收
ssize_t mq_receive(mqd_t mqdes, const char *ptr, size_t len, unsigned int *prio);   
```

## system_env 系统环境变量访问
```cpp
//获取系统环境变量
char *getenv(const char *name);
//添加和修改环境变量
int setenv(const char *name, const char *value, int rewrite);
//删除环境变量
int unsetenv(const char *name);
//写入环境变量，覆盖或者添加, 和setenv功能类似，实现上格式为name=string
char *putenv(char *str); 
//执行调用其它程序或者指令
int system (const char *__command);
```

## tcp/ 用于TCP客户端和服务器的demo  
TCP客户端接口
```c
//创建网络套接字    
int socket(int domain, int type, int protocol)    
//TCP握手连接到指定IP地址和端口  
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);   
//向连接的服务器通过TCP发送数据  
ssize_t write(int fd, const void *buf, size_t count);  
//从连接的服务器读取TCP数据  
ssize_t read(int fd, void *buf, size_t count);  
//关闭Socke通讯
int close(int fd);
```
TCP服务器接口  
在包含上述客户端接口外，额外需要服务器绑定的接口和等待连接的接口  
```c
//TCP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);  
//TCP等待客户端的连接  
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  
```

## timer
Linux软件定时器
```c
//用于连接信号和处理函数的实现
sighandler_t signal(int signum, sighandler_t handler);
//创建软件定时器的函数
int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue));
```

## udp/ 用于UDP客户端和服务器的demo  
UDP客户端接口
```c
//创建网络套接字  
int socket(int domain, int type, int protocol)  
//UDP数据发送  
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,  
              const struct sockaddr *dest_addr, socklen_t addrlen);   
//UDP数据接收  
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,  
                struct sockaddr *src_addr, socklen_t *addrlen);  
//关闭Socket通讯  
int close(int fd); 
```
UDP服务器接口  
在包含上述客户端接口外，额外需要服务器绑定的接口  
```c
//UDP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);  
```

