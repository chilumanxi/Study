/*************************************************************************
	> File Name: test_order.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月28日 星期二 10时29分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

static void thread_one(char *arg);
static void thread_two(char *arg);

int main(int argc, char *argv[]){
    pthread_t thid1, thid2;

    char *arg = "thread";
    printf("thread_one starts!\n");
    if(pthread_create(&thid1, NULL, (void *)thread_one, arg) != 0){
        exit(EXIT_FAILURE);
    }
    //sleep(1);   //注释1
    printf("thread_two starts!\n");
    if(pthread_create(&thid2, NULL, (void *)thread_two, arg) != 0){
        exit(EXIT_FAILURE);
    }
    printf("Main thread will sleep 1 second!\n");
    //sleep(1);   //注释2
    return 0;
}

static void thread_one(char *arg){
    int i = 0;
    while(i < 6){
        printf("I am one. loop = %d\n", i);
        ++i ;
        //sleep(1);   //注释3
    }
}

static void thread_two(char *arg){
    int i = 0;
    while(i  < 6){
        printf("I an two. loop = %d\n", i);
        ++i;
        //sleep(1);  //注释4
    }
}


