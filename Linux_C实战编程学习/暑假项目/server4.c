/*************************************************************************
	> File Name: server4.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月04日 星期二 18时56分54秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <limits.h>
#include <time.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>


#define SERV_PORT 5256

char temp[100];
int flag = 0;
char flag_f = 0;
int who;

void *thread_recv(void *arg);
void *thread_send(void *arg);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(void){
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERV_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(socket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
        perror("bind");
        exit(1);
    }
    if(listen(socket_fd, 10) < 0){
        perror("listen");
        exit(1);
    }

    struct sockaddr_in clientaddr;
    int clientlen;
    int connfd[10];
    int j;
    char temp[100];
    for(j = 0; j < 10; j ++){
        connfd[j] = -1;
    }

    clientlen = sizeof(clientaddr);
    int i = 0;
    pthread_t tid, tid1, tid2;

    while(1){
        connfd[i] = accept(socket_fd, (struct sockaddr *)&clientaddr, &clientlen);
        pthread_create(&tid, NULL, thread_recv, &connfd[i]);
        i ++;
        printf("在线人数:%d", i);
        printf("Accepted!\n");
        pthread_create(&tid1, NULL, thread_send, connfd);
    }
}

void *thread_recv(void *arg){
    while(1){
        int num = 0;
        num = recv(*((int *)arg), temp, 100, 0);
        if(strcmp("\n", temp) == 0)
            continue;
        if(num > 0){
            who = *((int *)arg);
            printf("接受客户端信息:%s\n", temp);
            flag = 1;
            pthread_cond_signal(&cond);
            
        }
    }
    return ;
}

void *thread_send(void *arg){
    int i;
    while(1){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond ,&mutex);
        pthread_mutex_unlock(&mutex);
        if(flag == 1){
            for(i = 0; ((int *)arg)[i] != -1; i ++){
                if(((int *)arg)[i] == who){
                    continue;
                }
                else
                    send(((int *)arg)[i], temp, 100, 0);
                    printf("消息转发成功!\n");
                }
            flag = 0;
        }         
    }
    return ;
        
}
