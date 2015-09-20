/*************************************************************************
    > File Name: test.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月21日 星期四 19时59分50秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

struct bit_data{
	int a: 6;
	int b: 4;
	int  : 8;
	int c: 4;
	int d;
};

int main(void){
	struct bit_data data;
	printf("HEllo World!\n");
	return 0;
}
