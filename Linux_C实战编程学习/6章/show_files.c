/*************************************************************************
    > File Name: show_files.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 11时30分51秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

int my_readir(const char *path){
	DIR *dir;
	struct dirent *ptr;

	if((dir = opendir(path)) == NULL){
		perror("opendir");
		return -1;
	}
	while((ptr = readdir(dir)) != NULL){
		printf("file name: %s\n", ptr -> d_name);
	}
	closedir(dir);

	return 0;
}

int main(int argc, char **argv){
	if(argc < 2){
		printf("listfile <target path>\n");
		exit(1);
	}

	if(my_readir(argv[1]) < 0)
		exit(1);

	return 0;
}
