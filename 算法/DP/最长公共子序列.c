/*************************************************************************
    > File Name: 最长公共子序列.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年06月07日 星期日 10时35分08秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int m, n;
char s[1001];
char t[1001];
int dp[1001][1001];

int max(int a, int b){	
	return a > b ? a : b;
}
void solve(){
	int i, j;
	for(i = 0; i < n; i ++){
		for(j = 0; j < m; j ++){
			if(s[i] == t[j])
				dp[i + 1][j + 1] = max(dp[i][j] + 1, max(dp[i + 1][j], dp[i][j + 1]));
			else {
				dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
			}
		}
	}
}
int main(void){
	int i, j;
	memset(dp, 0, sizeof(dp));
	scanf("%s", s);
	scanf("%s", t);
	n = strlen(s);
	m = strlen(t);
	solve();
	printf("%d\n", dp[n][m]);
}
