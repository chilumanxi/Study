/*************************************************************************
	> File Name: errshow.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月30日 星期四 10时36分19秒
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

FILE *open_file(char *filename){
    FILE *stream;
    errno = 0;

    stream = fopen(filename, "r");
    if(stream == NULL){
        printf("can not open the file %s. reason: %s\n", filename, strerror(errno));
        perror("stream");
        exit(-1);
    }
    else 
        return stream;
}

int main(void){
    char *filename = "test";

    open_file(filename);
    return 0;
}
