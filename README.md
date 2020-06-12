# embed_linux_demo
用于保存Linux应用层接口和STL应用接口demo的仓库  
方便后续查询和使用    
内部所有代码在Ubuntu16.04或WSL-Ubuntu20.04上测试    

## file_io/ Linux文件I/O操作  
Linux中设备的访问也以一切皆文件的思想存在，所以文件I/O是最常用的接口。 
```c
//打开文件,获得文件描述符
int open(const char *pathname, int oflag,...);  
//从文件中读取数据  
ssize_t read(int fd,void * buf ,size_t count);  
//向文件中写入数据  
ssize_t write (int fd,const void * buf,size_t count);  
//关闭文件描述符  
int close(int fd);  
//移动文件指针偏移地址,和read配合使用从指定起始地址读取数据  
off_t lseek(int fildes,off_t offset ,int whence);
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

## stl/ C++标准模板库  
目前包含vector, list, 后续计划添加map, set, deque, tree等  
stl的具体接口说明在下级目录完善  


## tcp/ 用于TCP客户端和服务器的demo  
### TCP客户端接口
```c
//创建网络套接字    
int socket(int domain, int type, int protocol)    
//TCP握手连接到指定IP地址和端口  
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);   
//向连接的服务器通过TCP发送数据  
ssize_t write(int fd, const void *buf, size_t count);  
//从连接的服务器读取TCP数据  
ssize_t read(int fd, void *buf, size_t count);  
```
### TCP服务器接口  
在包含上述客户端接口外，额外需要服务器绑定的接口和等待连接的接口  
```c
//TCP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);  
//TCP等待客户端的连接  
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);  
```


## udp/ 用于UDP客户端和服务器的demo  
### UDP客户端接口
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
### UDP服务器接口  
在包含上述客户端接口外，额外需要服务器绑定的接口  
```c
//UDP服务器绑定到指定的IP地址和客户端  
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);  
```
