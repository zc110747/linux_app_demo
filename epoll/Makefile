#编译工具和编译选项
CC = g++
CFLAGS  := -O3 -std=c++11 -lpthread

#头文件路径
LOWERAPP_INC_ROOT = ../

OBJS_1 = tcp_client.o 
APP_1 = tcp_client
OBJS_2 = epoll_server.o 
APP_2 = epoll_server
LIB = 

LOWERAPP_INC= -I $(LOWERAPP_INC_ROOT)
INCLUDE_PATH = $(LOWERAPP_INC)

all : $(APP_1) $(APP_2)

#生成.o文件 
%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_PATH)

#生成文件
$(APP_1) : $(OBJS_1)
	$(CC) -o $(APP_1) $(OBJS_1) $(LIB) $(CFLAGS)
	rm -f $(OBJS_1)

$(APP_2) : $(OBJS_2)
	$(CC) -o $(APP_2) $(OBJS_2) $(LIB) $(CFLAGS)
	rm -f $(OBJS_2)

tags :
	ctags -R *

clean:
	rm -f $(OBJS_1) $(APP_1) $(OBJS_2) $(APP_2)
