#ifndef __LIB_H
#define __LIB_h

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<sys/stat.h>
#define SERVPORT 5256                   //设置端口号
#define BUFLEN 1024                     //信息发送的统一缓存大小
#define NAMELEN 10
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef struct{                         //此结构体存储登录的用户的信息，包括姓名，fd号以及套接字文件信息
	struct sockaddr_in addr;
	char user_name[NAMELEN];
	int fd;
	int room_flag;   //flag=1:in chatroom; flag=2:in private chat
}fd_addr;


struct node{                            //通过此结构体给线程函数传输结构体和一个字符串的信息
    fd_addr * client_pa;
    char str[BUFLEN];
};

#endif

