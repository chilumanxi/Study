/*************************************************************************
    > File Name: coin_problem.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年06月16日 星期二 10时28分20秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>


const int v[6] ={1, 5, 10, 50, 100, 500};
int num[6];
int A;

int min(int a, int b){
	return a < b ? a : b;
}

void solve(){
	int i, t;
	int ans = 0;
	for(i = 5; i >= 0; i --){
		t = min(A / v[i], num[i]);
		A -= t * v[i];
		ans += t;
	}
	printf("%d\n", ans);
}

int main(void){
	int i;
	for(i = 0; i < 6; i ++){
		scanf("%d", &num[i]);
	}
	scanf("%d", &A);
	solve();
}
