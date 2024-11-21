# linux应用层接口和应用

本项目主要用于整理Linux C语言接口，并基于接口实现简单的demo应用。例程demo大部分未考虑异常处理情况，可以当作快速查看API接口和使用方法的总结库，不建议在商业产品中使用。本例程参考相关书籍如下所示。

1. 《UNIX环境高级编程》
2. 《UNIX网络编程 卷2：进程间通信》

因为个人能力和时间关系，可能有遗漏不全或者错误的部分, 如果发现可以及时反馈。

- [基础API接口](#base)
- [字符和基础类型判断处理接口](#character)
- [fork多进程应用](#fork)
- [多进程fifo通讯](#fifo)
- [文件I/O处理接口](#file_io)
- [进程间msq_queue通讯接口](#msg_queue)
- [pthread多线程应用](#pthread)
- [进程间pipe通讯接口应用](#pipe)
- [进程间posix_mq通讯接口](#posix_mq)
- [Linux平台信号触发](#signal)
- [系统环境变量处理](#system_env)
- [系统时间管理接口](#time)
- [udp客户端和服务器实现](#udp)
- [tcp客户端和服务器实现](#tcp)
- [epoll实现tcp服务器应用](#epoll)

## base

Linux基础API相关接口，例程地址：[ch01.base_api](./ch01.base_api/)

```c
// 打开文件夹路径
DIR *opendir (const char *__name);

// 读取路径信息
struct dirent *readdir (DIR *__dirp);

// 关闭文件夹
int closedir (DIR *__dirp);

// 创建文件夹
int mkdir (const char *__path, __mode_t __mode);

// 获取文件的状态信息
struct stat {
    dev_t     st_dev;     // 文件所在设备的ID
    ino_t     st_ino;     // 文件的inode号
    mode_t    st_mode;    // 文件的类型和访问权限
    nlink_t   st_nlink;   // 文件的硬链接数
    uid_t     st_uid;     // 文件所有者的用户ID
    gid_t     st_gid;     // 文件所有者所属的组ID
    dev_t     st_rdev;    // 设备类型（如果是设备文件）
    off_t     st_size;    // 文件大小，以字节为单位
    blksize_t st_blksize; // 文件系统的I/O缓冲区优化大小
    blkcnt_t  st_blocks;  // 分配给文件的块数
    time_t    st_atime;   // 文件的最后访问时间
    time_t    st_mtime;   // 文件的最后修改时间
    time_t    st_ctime;   // 文件的最后状态更改时间
};
int fstat(int fd, struct stat *buf);

// 获取进程ID
__pid_t getpid (void);

// 获取组ID
__uid_t getuid (void);

// 输出错误信息
void perror (const char *__s);

// 将错误代码转换为对应的错误信息字符串
char *strerror(int errnum);

// 获取当前时间信息
time_t time (time_t *__timer);

// 根据解析值获取变量
int getopt (int ___argc, char *const *___argv, const char *__shortopts);
```

## character

Linux字符处理接口，例程地址：[ch02.character_api](./ch02.character_api/)

```c
// 是否是数字
int isalnum(int c)

// 是否是ASCII
int isascii(int c)
```

## fork

进程创建和应用, Linux通过fork创建进程，复制资源。

```c
// 系统调用创建和原进程资源一致的的新进程(会复制资源重新分配)
__pid_t fork(void);

// 获得当前进程的pid值
__pid_t getpid(void);

// 获得当前进程的父进程pid值
__pid_t getppid(void);
```

## fifo

用于Linux进程间通讯的命名先入先出管道

```c
// 用于创建fifo管道的应用实现
int mkfifo (const char *__path, __mode_t __mode);

// 打开FIFO管道,获取后续使用的描述符
int open(const char *pathname, int oflag,...); 

// 从FIFO管道中读取数据  
ssize_t read(int fd, void * buf, size_t count);

// 向FIFO管道写入数据  
ssize_t write (int fd, const void * buf, size_t count);

// 关闭FIFO管道
int close(int fd);

// 移除FIFO管道
int unlink (const char *__name);
```  

## file_io

文件访问I/O接口。

```c
// 打开文件,获得文件描述符
int open(const char *pathname, int oflag,...);

// 从文件中读取数据  
ssize_t read(int fd, void * buf, size_t count);

// 向文件中写入数据  
ssize_t write (int fd, const void * buf, size_t count);

// 关闭文件描述符  
int close(int fd);

// 移动文件指针偏移地址,和read配合使用从指定起始地址读取数据  
off_t lseek(int fildes, off_t offset, int whence);

// 打开文件，获得文件指针，其中mode类型
// r:只读，w:只写，"a":追加模式，"w+":读写模式，不存在则创建，"b":二进制模式
FILE *fopen(char *filename, char *mode);

// 关闭文件并释放与文件相关的资源
int fclose(FILE *stream);

// 移动文件指针到指定位置，其中whence
// SEEK_SET: 文件开头，SEEK_CUR: 当前文件指针位置 SEEK_END: 文件末尾
int fseek(FILE *stream, long offset, int whence)

// 从文件中读取数据
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

//从文件中读取一个字符和将一个字符写入文件
int fgetc(FILE *stream)
int fputc(int c, FILE *stream)

//分别用于从文件中读取一行字符串和将字符串写入文件
char *fgets(char *str, int n, FILE *stream)
int fputs(const char *str, FILE *stream);
```  

## msg_queue

Linux进程间消息队列处理。

```c
// 创建消息队列
int msgget(key_t key, int oflg);

// 从消息队列里读取数据
ssize_t msgrcv(int msqid, void *ptr, size_t length, long type, int flag);

// 创建一个新的消息队列或访问一个已存在的消息队列
int msgsnd(int msqid, const void *ptr, size_t length, int flag);

// 提供在一个消息队列上的各种控制操作
int msgctl(int msqid, int cmd, struct msqid_ds *buff);
```

## pthread

 Linux多线程接口，多线程编译需要添加-lpthread

```c
// 线程的创建  
int pthread_create(pthread_t *tid, const pthread_arrt_t* attr,  
                    void*(*start_routine)(void *), void* arg);

// 等待线程的结束,非分离的线程在结束后只有执行join才会释放全部资源  
int pthread_join(pthread_t thread, void **retval);

// 线程离开时的返回值(必须为malloc或者全局变量)  
void pthread_exit(void * retval);

// 分离线程,被分离的线程在结束后自动释放所有资源  
int pthread_detach(pthread_t tid);

// 多线程的交互--互斥量和自旋锁
// 互斥量 
pthread_mutex_t m_lock;  
pthread_mutex_destroy(&m_lock);  
thread_mutex_lock(&m_lock)  
pthread_mutex_unlock(&m_lock);

// 自旋锁  
pthread_spinlock_t m_spinlock;  
pthread_spin_destroy(&m_spinlock);  
pthread_spin_lock(&m_spinlock);  
pthread_spin_trylock(&m_spinlock);  
pthread_spin_unlock(&m_spinlock);  
```

## pipe

用于进程间通讯的管道。

```c
// 创建pipe通道, 其中fd[0]为数据读管道描述符，fd[1]为数据写管道描述符
int pipe(int fd[2]);

// 通过管道描述符从管道中读取数据  
ssize_t read(int fd, void * buf, size_t count);

// 通过管道描述符向管道中写入数据
ssize_t write (int fd, const void *buf, size_t count);

// 关闭通道的接口应用
int close(int fd);
```  

## posix_mq

基于posix接口的消息队列。

```c
// 删除已经存在的消息队列
int mq_unlink(const char *name); 

// 打开或者创建一个消息队列
mqd_t mq_open(const char *name, int oflag, ... /*mode_t mode, struct mq_attr *attr*/);

// 关闭消息队列  
int mq_close(mqd_t mqdes);

// 获取消息队列的具体参数信息
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);

// 投递数据给消息队列
int mq_send(mqd_t mqdes, const char *ptr, size_t len, unsigned int prio);

// 等待消息队列有消息接收
ssize_t mq_receive(mqd_t mqdes, const char *ptr, size_t len, unsigned int *prio);   
```

## signal

Linux软件定时器和信号触发。

```c
// 用于连接信号和处理函数的实现
sighandler_t signal(int signum, sighandler_t handler);

// 创建软件定时器的函数
int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue);
```

## system_env

系统环境变量访问。

```c
// 获取系统环境变量
char *getenv(const char *name);

// 添加和修改环境变量
int setenv(const char *name, const char *value, int rewrite);

// 删除环境变量
int unsetenv(const char *name);

// 写入环境变量，覆盖或者添加, 和setenv功能类似，实现上格式为name=string
char *putenv(char *str);

// 执行调用其它程序或者指令
int system (const char *__command);
```

## time

系统时间处理的接口。

```c
// 获取系统的日历时间，以1970-1-1, 00:00:00开始
time_t time (time_t *__timer);

// 根据日历时间获取GMT时间的函数
struct tm *gmtime (const time_t *__timer);
struct tm *gmtime_r (const time_t *__restrict __timer,  struct tm *__restrict __tp)

// 获取本地时间的函数
struct tm *localtime (const time_t *__timer);
struct tm *localtime_r (const time_t *__restrict __timer, struct tm *__restrict __tp)

// 根据本地时间生成时间字符串
char *asctime (const struct tm *__tp);
char *asctime_r (const struct tm *__restrict __tp, char *__restrict __buf);

// 根据日历时间生成时间字符串
char *ctime (const time_t *__timer);
char *ctime_r (const time_t *__restrict __timer, char *__restrict __buf);

// 将带时区的时间转换成秒数
time_t mktime (struct tm *__tp);
```

## udp

用于UDP客户端和服务器的demo。

```c
///////////////// udp共用端口 /////////////////
// 创建网络套接字  
int socket(int domain, int type, int protocol)

// UDP数据发送  
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,  
              const struct sockaddr *dest_addr, socklen_t addrlen)
   
// UDP数据接收  
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,  
                struct sockaddr *src_addr, socklen_t *addrlen)
  
// 关闭Socket通讯  
int close(int fd);

///////////////// udp服务端端口 /////////////////
// UDP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen); 
```

## tcp

用于TCP客户端和服务器的demo

```cpp
///////////////// tcp共用端口 /////////////////
// 创建网络套接字    
int socket(int domain, int type, int protocol)

// 向连接的服务器通过TCP发送数据  
ssize_t write(int fd, const void *buf, size_t count);

// 从连接的服务器读取TCP数据  
ssize_t read(int fd, void *buf, size_t count);

// 关闭Socke通讯
int close(int fd);

///////////////// tcp客户端接口 /////////////////
// tcp握手连接到指定IP地址和端口  
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);   

///////////////// tcp服务端接口 /////////////////
// TCP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);

// TCP等待客户端的连接  
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  
```

## epoll

事件触发驱动接口。

```c
// 创建epoll事件句柄
int epoll_create (int __size)

// 操作epoll事件的应用接口
int epoll_ctl (int __epfd, int __op, int __fd, struct epoll_event *__event)

// 等待epoll事件触发的接口
int epoll_wait (int __epfd, struct epoll_event *__events, int __maxevents, int __timeout)

// 关闭epoll事件描述符,释放资源
int close (int __fd)
```
