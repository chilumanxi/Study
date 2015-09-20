/*************************************************************************
	> File Name: checkerrno.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月30日 星期四 10时30分37秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(){
    FILE *stream;
    char *filename = "test";
    errno = 0;

    stream = fopen(filename, "r");
    if(stream == NULL){
        printf("open file %s failed, errno is %d\n", filename, errno);
    }
    else 
        printf("open file %s successfully\n", filename);
    return 0;
}
