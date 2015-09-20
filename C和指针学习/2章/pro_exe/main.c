/*************************************************************************
    > File Name: main.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年06月04日 星期四 14时12分33秒
 ************************************************************************/

#include<stdio.h>

int main(void){
	printf("%d %d\n", increment(10), negate(10));
	printf("%d %d\n", increment(10), negate(0));
	printf("%d %d\n", increment(-10), negate(-10));
	return 0;
}
