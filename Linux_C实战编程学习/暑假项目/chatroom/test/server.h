#ifndef __SERVER_H
#define __SERVER_H

#include"lib.h"
#include<pthread.h>

#define BACKLOG 10
#define MAXPEOPLE 10
#define FD_ADDR_CLR(a) ((a)->fd) = -1;\
		((a)->addr.sin_addr.s_addr)
#define DEBUG_VERSION

typedef struct 
{
	struct sockaddr_in addr;
	int fd;
}fd_addr;

fd_addr client[MAXPEOPLE];


void server();
void* msg_processor(void*);
void sendto_all_user(fd_addr*);
void sendto_a_user(fd_addr*, fd_addr*);

#endif
