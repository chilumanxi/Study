/*************************************************************************
	> File Name: pthread_exit_test.c
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月03日 星期一 07时56分06秒
 ************************************************************************/
#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
struct foo{
        int a,b,c,d;

};

void printfoo(const char *s,const struct foo *fp)
{
        printf("s is %s\n",s);
        printf("structure at 0x%x\n",(unsigned)fp);
        printf("foo.a=%d\n",fp->a);
        printf("foo.b=%d\n",fp->b);
        printf("foo.c=%d\n",fp->c);
        printf("foo.d=%d\n",fp->d);

}
void *thr_fn1(void *arg)
{
        struct foo foo={1,2,3,4};
        printfoo("thread 1:\n",&foo);
        pthread_exit((void *)&foo);

}
void * thr_fn2(void *arg)
{
        struct foo foo={4,5,6,7};
        printf("thread 2:ID is %d\n",pthread_self());
        printfoo("thread 2\n",&foo);
        pthread_exit((void *)0);

}
int main(void)
{
        
        int err;
        pthread_t tid1,tid2;
        struct foo *fp;
        err=pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0){
                printf("create thread 1 is failed\n",strerror(err));
                exit(1);
            
    }
        err=pthread_join(tid1,(void *)&foo);
        if(err!=0)
                printf("can't join thread1\n");
        sleep(1);
        err=pthread_create(&tid2,NULL,thr_fn2,NULL);
        if(err!=0)
    {
                printf("create thread 2 is failed\n");
                 exit(1);
            
    }
        sleep(1);
        printfoo("parent :\n",&fp);
        exit(0);

}
