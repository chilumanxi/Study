/*************************************************************************
	> File Name: 8.7.2.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月30日 星期四 10时54分15秒
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

pthread_mutex_t mutex;
pthread_cond_t cond;
int x = 0;
void *thread1(void *arg){
    while(1){
        printf("thread1 will change ans!\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        x += 1;
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
}

void *thread2(void *arg){
    while(1){
        printf("thread2 will change ans!\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        x += 1;     
        pthread_mutex_unlock(&mutex);
      

        sleep(4);
    }
}

void *thread3(void *arg){
    while(1){
        printf("thread3 will change ans!\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        x += 1;
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
}

int main(void){
    pthread_t tid1, tid2, tid3;

    printf("condition variable study!\n");
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&tid1, NULL, (void*)thread1, NULL);
    pthread_create(&tid2, NULL, (void*)thread2, NULL);
    pthread_create(&tid3, NULL, (void*)thread3, NULL);

    do{
        pthread_cond_signal(&cond);
        printf("%d\n", x);
        sleep(1);
    }while(1);

    //sleep(50);
    pthread_exit(0);
}
