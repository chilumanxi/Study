/*************************************************************************
    > File Name: 01背包.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年06月05日 星期五 12时18分28秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define MAX_N 10010


int n, W;
int w[MAX_N];
int v[MAX_N];
int dp[MAX_N + 1][MAX_N + 1];


int max(int a, int b){
	return a > b ? a : b;
}
/*
int rec(int i, int j){
	int res;
	if(i == n){
		res = 0;
	}
	else if(j < w[i]){
		res = rec(i + 1, j);
	}
	else{
		res = max(rec(i + 1, j) , rec(i + 1, j - w[i]) + v[i]);
	}
	return res;
}
*/

/*
int rec(int i, int j){
	int res;
	if( dp[i][j] ){
		return dp[i][j];
	}
	if(i == n)
		res = 0;
	else if(j < w[i])
		res = rec(i + 1, j);
	else{
		res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
	}
	return dp[i][j] = res;
}
*/

int solve(){
	int i, j;
	for(i = n - 1; i >= 0; i --){
		for(j = 0; j <= W; j ++){
			if(j < w[i]){
				dp[i][j] = 0;
			}
			else {
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
			}
		}
	}
}

int main(void){
	int i;
	memset(dp, 0, sizeof(dp));
	scanf("%d", &n);
	getchar();
	for(i = 0; i < n; i ++, getchar()){
		scanf("%d%d", &w[i], &v[i]);
	}
	scanf("%d", &W);
	//printf("%d", rec(0, W));
	solve();
	printf("%d",dp[0][W]);
}
