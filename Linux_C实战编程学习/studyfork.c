/*************************************************************************
    > File Name: studyfork.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月27日 星期三 21时41分35秒
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glob=6;

char buf[]="a write to stdout\n";

 

int main(void)

{

       int var=88;

       pid_t pid;

 

       if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1)

                printf("writeerror");

 

       printf("before fork with  换行符\n");

       printf("before fork without换行符");   

       //printf("\n");

 

       if((pid=fork())<0){

                printf("fork error");

 

       }else if(pid==0){

                printf("I am is  child process,pid=%d\n",getpid());

                printf("my parentprocess's pid=%d\n",getppid());

                glob++;

                var++;

       }else{

                printf("this is parentprocess,pid=%d\n",getpid());

                //var++;

       }

 

       printf("pid=%d,glob=%d,var=%d\n",getpid(),glob,var);

       exit(0);

}

