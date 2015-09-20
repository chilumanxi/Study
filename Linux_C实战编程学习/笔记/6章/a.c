/*************************************************************************
    > File Name: a.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 21时04分42秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

char path[40] = "haha.txt";

int main(void){
	struct stat buf;
	if(stat(path, &buf) < 0)
		perror("stat");
	printf("%d\n", buf.st_ctime);
	printf("%d\n", buf.st_mtime);
	return 0;
}
