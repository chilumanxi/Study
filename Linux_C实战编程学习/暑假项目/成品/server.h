#ifndef __SERVER_H
#define __SERVER_H

#include"lib.h"
#include<pthread.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<termios.h>
#define BACKLOG 100
#define MAXPEOPLE 100

#define PWDLEN 20               
#define SAVEMOST 1024           
#define PATHLEN 128             
#define MAXGROUP 256    //最多有多少个群组
#define MAXFILE 1024    //最多有多少个文件
#define FD_ADDR_CLR(a) ((a)->fd) = -2;\
		(a)->addr.sin_addr.s_addr = 0;\
		 memset((a)->user_name, 0, 10);\
		(a)->room_flag = 0;
		//处理退出以后的用户信息
#define DEBUG_VERSION




struct info{                //用户信息结构体，有姓名，密码，性别年龄电话，好友，加入的群组，在内存中以链表形式维护
	char name[NAMELEN];
	char pwd[PWDLEN];
    char age[3];
    char phonenum[PWDLEN];
    char friends[MAXPEOPLE][NAMELEN];
    char groups[MAXGROUP][NAMELEN];
	struct info* next;
};

struct group{               //群信息结构体，有群名，群成员，群文件名。在内存中以链表形式维护
    char group_name[NAMELEN];
    char member[MAXPEOPLE][NAMELEN];
    char filename[MAXFILE][NAMELEN];
    struct group *next;
};

struct log{                 //日志信息结构体
    char logbuf[BUFLEN];
    int len;
};

fd_addr client[MAXPEOPLE];  //在线的所有用户的
struct info* file_info;     //全局的用户信息链表的头结点
struct group* file_group;   //全局的群信息链表的头结点
struct log errlog;          //错误日志结构体
struct log dailylog;        //日常日志结构体


pthread_mutex_t sock_mutex = PTHREAD_MUTEX_INITIALIZER;   //各种锁
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void server();
void* msg_processor(void*);
int login(fd_addr*);
void chat_with_all(fd_addr*);
//void chat_with_one(fd_addr*);
void send_to_all(char* ,fd_addr*);
void send_to_group(char *, fd_addr*, struct group *);
void load_info();
void load_group();
void save_info(struct info*);
void save_group(struct group*);
void add_in_list(struct info *, const char *, const char *, const char *, const char *);
void add_group_list(struct group *, const char *, const char *);
void update_info(struct info*);
void update_group(struct group*);
void add_friend(fd_addr *);
void send_invatation(fd_addr*, const char *);
void chat_with_one(fd_addr *, struct info *);
void chat_with_group(fd_addr *, struct info *);
void add_group(fd_addr *, struct info *);
void quit_from_group(fd_addr *, struct info *);
void change_information(fd_addr *, struct info* );
void deal_dailylog(char *);
void deal_errlog(char *);
void file_of_the_group(fd_addr*, struct info *);
void *get_file_from_ser(void *);
void *send_file_to_ser(void *);

#endif
