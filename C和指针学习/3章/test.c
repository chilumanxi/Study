/*************************************************************************
    > File Name: test.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年06月11日 星期四 14时05分43秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

enum Liquid {
	OUNCE = 1, CUP = 8, PINT = 16, QUART = 32, GALLON = 128
};
int main(void){
	enum Liquid jar;
	jar = QUART;
	printf("%d\n", jar);
	jar = jar + PINT;
	printf("%d\n", jar);
	return 0;
}
