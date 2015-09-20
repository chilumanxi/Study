/*************************************************************************
    > File Name: 求一个数二进制有多少个1.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月24日 星期日 15时13分04秒
 ************************************************************************/
#include<stdio.h>

int main(void){
	int x;
	int count = 0;
	scanf("%d", &x);
	while(x){
		x = x&(x - 1);
		count ++;
	}
	printf("%d", count);
	return 0;
}
