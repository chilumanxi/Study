/*************************************************************************
	> File Name: client2.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月04日 星期二 09时11分36秒
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
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXLINE 100
void *thread_send(void *arg);
void *thread_recv(void *arg);

int main(){
    int *conn_fd;
    struct sockaddr_in serv_addr;
    conn_fd = (int *)malloc(sizeof(int));
    *conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5256);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(*conn_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("connect error\n");
        exit(1);
    }

    pthread_t tid1, tid2;
    printf("connected\n");
    while(1){
        pthread_create(&tid1, NULL, thread_send, conn_fd);
        pthread_create(&tid2, NULL, thread_recv, conn_fd);
    }

    exit(0);
}

void *thread_send(void *arg){
    int conn_fd = (*(int *)arg);
    int idata;
    char send_buf[100];
    while(1){
        fgets(send_buf, 100, stdin);
        send(conn_fd, send_buf, sizeof(send_buf), 0);
        printf("client send ok\n");
    }
    return ;
}

void *thread_recv(void *arg){
    int conn_fd = (*(int *)arg);
    char recv_buf[100];
    while(1){
        int idata = 0;
        idata = recv(conn_fd, recv_buf, 100, 0);
        if(idata > 0){
            printf("server : \n%s\n", recv_buf);
        }
    }
    return ;
}


