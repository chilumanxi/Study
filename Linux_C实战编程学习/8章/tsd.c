/*************************************************************************
	> File Name: tsd.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月28日 星期二 10时02分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_key_t key;
int tsd = 5;
void *thread2(void *arg){
    printf("thread %u is running\n", pthread_self());
    pthread_setspecific(key, (void *)tsd);
    printf("global variable does not change : %d\n", pthread_getspecific(key));
    tsd = 6;
    printf("thread %u returns %d\n", pthread_self(), pthread_getspecific(key));
}

void *thread1(void *arg){
    pthread_t thid2;
    printf("thread %u is running\n", pthread_self());
    pthread_setspecific(key, (void *)tsd);
    printf("global variable does not change : %d\n", pthread_getspecific(key));
    tsd = 7;
    pthread_create(&thid2, NULL, thread2, NULL);
    pthread_join(thid2, NULL);
    printf("thread %u returns %d\n", pthread_self(), pthread_getspecific(key));
}

int main(void){
    pthread_t thid1;
    int status;
    printf("main thread begins running\n");
    pthread_key_create(&key, NULL);
    pthread_create(&thid1, NULL, (void *)thread1, NULL);
    pthread_join(thid1, (void *)&status);
    printf("thid1's exit is caused %d\n");
    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}
