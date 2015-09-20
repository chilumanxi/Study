/*************************************************************************
	> File Name: jointhread.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月28日 星期二 09时43分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *assistthread(void *arg){
    printf("I am helping test!\n");
    sleep(3);
    pthread_exit(0);
}

int main(void){
    pthread_t assistthid;
    int status;
    pthread_create(&assistthid, NULL, (void *)assistthread, NULL);
    pthread_join(assistthid, (void *)&status);
    printf("assistthread's exit is caused %d\n", status);

    return 0;
}
