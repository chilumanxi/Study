/*************************************************************************
	> File Name: server_file.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月05日 星期三 08时41分06秒
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
#include <netinet/in.h>
#include <sys/socket.h>

#define SERV_PORT 5256
#define LENGTH_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME 512

void my_err(const char *string, int line){
    printf("line : %d\n", line);
    perror(string);
    exit(1);
}

int main(void){
    struct sockaddr_in serve_addr;
    memset(&serve_addr, 0, sizeof(struct sockaddr_in));
    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(SERV_PORT);
    serve_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
        my_err("socket", __LINE__);
    
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(socket_fd, (struct sockaddr*)&serve_addr, sizeof(struct sockaddr_in)) < 0)
        my_err("bind", __LINE__);

    if(listen(socket_fd, LENGTH_QUEUE) == -1)
        my_err("listen", __LINE__);

    while(1){
        struct sockaddr_in cli_addr;
        socklen_t cli_addr_len = sizeof(struct sockaddr_in);

        int conn_fd = accept(socket_fd, (struct sockaddr*)&cli_addr, &cli_addr_len);
        if(conn_fd < 0){
            perror("accept");
            break;
        }
        char buffer[BUFFER_SIZE];
        memset(buffer, 0 , sizeof(buffer));
        if(recv(conn_fd, buffer, BUFFER_SIZE, 0) < 0){
            perror("recv");
            break;
        }

        char file_name[FILE_NAME + 1];
        memset(file_name, 0, sizeof(file_name));
        strncpy(file_name, buffer, strlen(buffer) > FILE_NAME ? FILE_NAME : strlen(buffer));
        printf("%s\n", file_name);

        FILE *fp = fopen(file_name, "r");
        if(fp == NULL){
            printf("File :%s not found\n", file_name);
        }
        else{
            memset(buffer, 0, sizeof(buffer));
            int len = 0;
            while((len = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0){
                if(send(conn_fd, buffer,len, 0) < 0){
                    printf("Send File:%s Failed\n", file_name);
                    break;
                }
                memset(buffer, 0, sizeof(buffer));
            }

            fclose(fp);
            printf("File:%s Transfer Successfully!\n", file_name);
        }
        close(conn_fd);
        
    }
    close(socket_fd);
    return 0;

}


