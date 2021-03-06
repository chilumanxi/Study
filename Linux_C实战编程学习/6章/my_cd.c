/*************************************************************************
    > File Name: my_cd.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 11时05分16秒
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
void my_err(const char *err_string, int line){
	fprintf(stderr, "line : %d  ", line);
	perror(err_string);
	exit(1);
}

int main(int argc, char **argv){
	char buf[PATH_MAX + 1];

	if(argc < 2){
		printf("my_cd <targe path>\n");
		exit(1);
	}
	if(chdir(argv[1]) < 0){
		my_err("chdir", __LINE__);
	}
	if(getcwd(buf, 512) < 0){
		my_err("getcwd", __LINE__);
	}

	printf("%s\n", buf);

	return 0;
	

}
