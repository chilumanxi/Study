/*************************************************************************
    > File Name: my_pwd.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 10时56分27秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(){
	char buf[100];
	if(getcwd(buf, 100) == NULL){
		fprintf(stderr, "line : %d  ", __LINE__);
		perror("getcwd");
		exit(1);
	}
	printf("%s\n", buf);
	return 0;
}
