/*************************************************************************
    > File Name: process_.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月28日 星期四 14时32分30秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
/*
#define ERR_EXIT (m)
	do{
		perror(m);
		exit(EXIT_FAILURE);
	}while(0);
*/

int main(int argc, char *argv[]){
	char *const args[] = {"ls", "-l", NULL};
	printf("Entering main ... \n");
    // execlp("ls", "ls", "-l", NULL);  //带p会搜索PATH
	// execl("/bin/ls", "ls", "-l", NULL); //带l为可变参数
    // execvp("ls",args); //args数组参数传递给main
	// execv("/bin/ls",args);
	
	int ret;
	//ret = fcntl(1, F_SETFD, FD_CLOEXEC);
	/*FD_CLOSEEXEC被置位为1(在打开文件时标志为O_CLOEXEC=也会置位),
	 * 即在执行execve时将标准输出的文件描述关闭,
	 * 即下面替换的pid_env程序不会在屏幕上输出信息
	 */
	//if (ret == -1)
	//	perror("fcntl error");
	
    char *const envp[] = {"AA=11", "BB=22", NULL};
    ret = execle("./pid_env.c", "pid_enV", NULL, envp); // 带e可以自带环境变量
    //  execvpe("ls", args, envp);
    if (ret == -1)
        perror("exec error");
    printf("Exiting main ... n");
     
    return 0;
}

