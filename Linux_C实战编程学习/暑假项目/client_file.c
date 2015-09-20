/*************************************************************************
	> File Name: client_file.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月05日 星期三 14时38分24秒
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
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 5256
#define BUFFER_SIZE 1024
#define FILE_NAME 512

int main(void){
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htonl(SERV_PORT);
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0){
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    if(inet_aton("127.0.0.1", &server_addr.sin_addr) == INADDR_NONE){
        perror("inet_pton");
        exit(1);
    }
    server_addr.sin_port = htons(SERV_PORT);
    socklen_t server_add_length = sizeof(server_addr);

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
        perror("connect");
        exit(1);
    }   

    char filename[FILE_NAME + 1];
    memset(filename, 0, sizeof(filename));
    printf("please input Filename");
    scanf("%s", filename);
    
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, filename, strlen(filename) > BUFFER_SIZE ? BUFFER_SIZE : strlen(filename));

    if(send(client_fd, buffer, BUFFER_SIZE, 0) < 0){
        perror("send");
        exit(1);
    }

    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("open File %s wrong\n", filename);
        exit(1);
    }

    memset(buffer, 0, sizeof(buffer));
    int len = 0;
    while((len = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0){
        if(fwrite(buffer, sizeof(char), len, fp) < len){
            printf("file write error!\n");
            break;
        }
        memset(buffer, 0, sizeof(buffer));
    }

    printf("receive file :%s from server ip successfully!\n", filename);
    fclose(fp);
    close(client_fd);
    return 0;
}

