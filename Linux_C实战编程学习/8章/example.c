/*************************************************************************
	> File Name: example.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月03日 星期一 10时04分40秒
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
#include <pthread.h>

int flag = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *arg){
    printf("this is thread1, flag: %d, thread id is %u\n", flag, (unsigned)pthread_self());
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    flag = 1;
    printf("this is thread1, flag: %d, thread id is %u\n", flag, (unsigned)pthread_self());
    pthread_mutex_unlock(&mutex);
    pthread_join(*(pthread_t*)arg, NULL);
    printf("thread1 ends!\n");;
    pthread_exit(0);
}

void thread2(void *arg){
    printf("this is thread2, flag: %d, thread id is %u\n", flag, (unsigned)pthread_self());
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    flag = 2;
    printf("this is thread2, flag: %d, thread id is %u\n", flag, (unsigned)pthread_self());
    pthread_mutex_unlock(&mutex);
    printf("thread2 ends!\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    int i = 0;
    printf("this is main function!\n");
    pthread_t thid1, thid2;
    if((pthread_create(&thid2, NULL, (void *)thread2, NULL)) != 0)
        perror("pthread_create");
    if((pthread_create(&thid1, NULL, (void *)thread1, &thid2)) != 0)
        perror("pthread_create");
    while(i ++ < 3){
        pthread_cond_signal(&cond);
        sleep(1);
    }
    printf("main function ends!\n");
    exit(0);
}
    
