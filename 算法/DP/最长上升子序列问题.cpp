/*************************************************************************
    > File Name: 最长上升子序列问题.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年06月07日 星期日 14时14分02秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int n;
int a[10010];
int dp[10010];
#define INF 100000
int max(int a, int b){
	return a > b ? a : b;
}
/*
void solve(){
	int i, j;
	int res = 0;
	for(i = 0; i < n; i ++){
		dp[i] = 1;
		for(j = 0; j < i; j ++){
			if(a[i] > a[j])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		res = max(res, dp[i]);
	}
	printf("%d\n", res);
}
*/

void solve(){
	int i;
	fill(dp, dp + n, INF);
	for(i = 0; i < n; i ++)
		*lower_bound(dp, dp + n, a[i]) = a[i];
	printf("%d\n",lower_bound(dp, dp + n, INF) - dp);
}
int main(void){
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i ++)
		scanf("%d",&a[i]);
	solve();
}
