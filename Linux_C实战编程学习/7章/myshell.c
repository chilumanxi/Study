/*************************************************************************
	> File Name: myshell.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月26日 星期日 21时51分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define nomode 0
#define in_redirect 1
#define out_redirect 2
#define pipe 3
int spething = 0;
void print_shell(){
    printf("myshell$$ ");
}

void get_input(char *str){
    char c;
    int i = 0;
    while((c = getchar()) != '\n' && i < 256){
        str[i ++] = c;
    }
    if(i == 256){
        printf("command is too long\n");
        exit(1);
    }
    str[i ++] = '\n';
    str[i] = '\0';
}


void analysis_command(char *str, int *argcount, char arglist[100][256]){
    char *p = str;
    int num = 0;
    int i = 0;
    char flag = 0;
    while(*p != '\n'){
        if(*p == ' ' && flag == 0){
            p ++;
            continue;
        }
        else if(*p == ' ' && *(p + 1) != ' '){
            arglist[num][i] ='\0';
            p ++;
            i = 0;
            num ++;
        }
        else if(*p == ' ' && *(p + 1) == ' '){
            p ++;
            continue;
        }
        arglist[num][i ++] = *(p ++);
        flag = 1;
    }
    arglist[num][i] = '\0';
    *argcount = num + 1;
}

int find_command(char *command){
    DIR *dir;
    int i = 0;
    struct dirent *dirp;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};
    if(!strcmp(command, "./")){
        command += 2;
    }
    while(path[i] != NULL){
        if((dir = opendir(path[i])) == NULL)
            printf("cannot open /bin \n");
        while((dirp = readdir(dir)) != NULL){
            if(strcmp(dirp -> d_name, command) == 0){
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
        i ++;
    }
    return 0;
}


void work_nomode(pid_t pid, char *arg[], char *file){
    int fd;
    if(pid == 0){
        if(!find_command(arg[0])){
            printf("%s : command not found!\n", arg[0]);
            exit(1);
        }
        execvp(arg[0], arg);
        exit(0);
    }
}


void work_inmode(pid_t pid, char *arg[], char *file){
    int fd;
    if(pid == 0){
        if(!find_command(arg[0])){
            printf("%s : command not found!\n", arg[0]);
            exit(1);
        }
        fd = open(file, O_RDONLY);
        dup2(fd, 0);
        execvp(arg[0], arg);
        exit(0);
    }
}

void work_fifo(pid_t pid, char *arg[], char *argnext[]){
    if(pid == 0){
        int pid2;
        int status2;
        int fd2;

        if((pid2 = fork()) < 0){
            printf("fork error");
            spething = 1;
            return ;
        }
        else if(pid2 == 0){
            if(!(find_command(arg[0]))){
                printf("%s : command not found\n", arg[0]);
                spething = 1;
                exit(1);
            }
            fd2 = open("/tmp/tempfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
            dup2(fd2, 1);
            execvp(arg[0], arg);
            exit(0);
        }

        if(spething == 1)
            exit(1);
        if(waitpid(pid2, &status2, 0) == -1){
            printf("wait for child process error!\n");
        }

        if(!(find_command(argnext[0]))){
            printf("%s : command not found\n", arg[0]);
            exit(1);
        }
        fd2 = open("/tmp/tempfile", O_RDONLY);
        dup2(fd2, 0);
        execvp(argnext[0], argnext);

        if(remove("tmp/tempfile"))
            printf("remove error");
        exit(0);

    }
}

void work_outmode(pid_t pid, char *arg[], char *file){
    int fd;
    if(pid == 0){
        if(!find_command(arg[0])){
            printf("%s : command not found!\n", arg[0]);
            exit(1);
        }
        fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
        dup2(fd, 1);
        execvp(arg[0], arg);
        exit(0);
    }
}

void handle(char arglist[100][256], int argcount){
    int check = 0;
    int mode = 0;
    int background = 0;
    int status;
    int i, j;
    int fd;
    char *arg[argcount + 1];
    char *argnext[argcount + 1];
    char *file;
    pid_t pid;
    //取出输入的命令
    for(i = 0; i < argcount; i ++){
            arg[i] = (char *)arglist[i];
    }
    arg[argcount] = NULL;

    //找到后台运行的符号加以处理
    for(i = 0; i < argcount; i ++){
        if(!strcmp(arg[i], "&")){
            if(i == argcount - 1){
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            }
            else{
                printf("wrong command!\n");
                return;
            }
        }
    }

    for(i = 0; arg[i] != NULL; i ++){
        if(!strcmp(arg[i], ">")){
            check ++;
            if(arg[i + 1] == NULL){
                printf("wrong command!\n");
                return ;
            }
            else{
                mode = out_redirect;
            }
        }

        if(!strcmp(arg[i], "<")){
            check ++;
            if(arg[i + 1] == NULL){
                printf("wrong command!\n");
                return ;
            }
            else{
                mode = in_redirect;
            }
        }

        if(!strcmp(arg[i], "|")){
            check ++;
            if(arg[i + 1] == NULL){
                printf("wrong command!\n");
                return ;
            }
            else{
                mode = pipe;
            }
        }
    }

    if(check > 1){
        printf("wrong command!\n");
        return ;
    }

    if(mode == out_redirect || mode == in_redirect){
        for(i = 0; arg[i] != NULL; i ++){
            if(!strcmp(arg[i], "<") || !strcmp(arg[i], ">")){
                file = arg[i + 1];
                arg[i] = NULL;
            }
        }
    }

    if(mode == pipe){
        for(i = 0; arg[i] != NULL; i ++){
            if(!strcmp(arg[i], "|")){
                arg[i] = NULL;
                for(j = i + 1; arg[j] != NULL; j ++){
                    argnext[j - i - 1] = arg[j];
                }
                argnext[j - i - 1] = arg[j];
                break;
            }
        }
    }

    if((pid = fork()) < 0){
        printf("fork error");
        return ;
    }


    switch(mode){
        case nomode:
            work_nomode(pid, arg, file);
            break;
        case in_redirect:
            work_inmode(pid, arg, file);
            break;
        case out_redirect:
            work_outmode(pid, arg, file);
            break;
        case pipe:
            work_fifo(pid ,arg, argnext);
            break;
        default:
            break;
    }

    if(spething == 1)
        return ;

    if(background == 1){
        printf("[Process id %d]\n", pid);
        return ;
    }

    if(waitpid(pid, &status, 0) == -1)
        printf("wait for child process error!\n");
}



int main(int argc, char *argv[]){
    int i;
    char *buf = NULL;
    int  argcount = 0;
    char **arg = NULL;
    char arglist[100][256];

    buf = (char *)malloc(sizeof(char) * 256);
    if(buf == NULL){
        printf("malloc error!\n");
        exit(1);
    }
    while(1){
        memset(buf, 0, sizeof(buf));
        print_shell();
        get_input(buf);
        if(!strcmp(buf, "exit\n") || !strcmp(buf, "logout\n")){
            break;
        }
        for(i = 0; i < 100; i ++){
            arglist[i][0] = '\0';
        }
        argcount = 0;
        analysis_command(buf, &argcount, arglist);
        handle(arglist, argcount);
    }

    if(buf != NULL){
        free(buf);
        buf = NULL;
    }

    exit(0);
}

