/*************************************************************************
    > File Name: pid_env.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月28日 星期四 14时03分19秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(void){
	printf("hello pid = %d\n", getpid());
	int i;
	for(i = 0; environ[i] != NULL; i ++)
		printf("%s\n", environ[i]);
	return 0;
}
