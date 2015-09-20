/*************************************************************************
	> File Name: test_signal.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月31日 星期五 11时30分10秒
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
int a = 0;


void *thread1(void *arg){
    pthread_mutex_lock(&mutex);
    printf("thread1 is starting!\n");
    a ++;
    printf("thread1 a's value is %d\n", a);
    pthread_cond_wait(&cond, &mutex);
    a ++;
    printf("thread1 a's value is %d\n", a);
    pthread_mutex_unlock(&mutex);
}

int main(void){
    pthread_t tid1;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&tid1, NULL, thread1, NULL);
    sleep(2);
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond);
    printf("main a's value is %d\n", a);
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}
