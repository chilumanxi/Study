#ifndef __SERVER_H
#define __SERVER_H

#include"lib.h"
#include<pthread.h>

#define BACKLOG 10
#define MAXPEOPLE 10
#define NAMELEN 10
#define PWDLEN 20
#define FD_ADDR_CLR(a) ((a)->fd) = -1;\
		(a)->addr.sin_addr.s_addr = 0;\
		 memset((a)->user_name, 0, 10);\
		(a)->room_flag = 0;
		
#define DEBUG_VERSION

typedef struct 
{
	struct sockaddr_in addr;
	char user_name[NAMELEN];
	int fd;
	int room_flag;   //flag=1:in chatroom; flag=2:in private chat
}fd_addr;

struct info
{
	char name[NAMELEN];
	char pwd[PWDLEN];
	struct info* next;
};

fd_addr client[MAXPEOPLE];
struct info* file_info;

pthread_mutex_t sock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void server();
void* msg_processor(void*);
int login(fd_addr*);
void chat_with_all(fd_addr*);
void chat_with_one(fd_addr*);
void sendto_all(char* ,fd_addr*);
void load_info();
void save_info(struct info*);

#endif
