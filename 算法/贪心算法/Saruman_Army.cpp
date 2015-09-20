/*************************************************************************
    > File Name: Saruman_Army.cpp
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年06月16日 星期二 16时50分09秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#define MAX_N 1001

using namespace std;
/*
int N, R;
int pos[MAX_N];
bool flag[2*MAX_N];
void solve(){
	sort(pos, pos + N);
	int ans = 0;
	for(int i = 0; i < N; i ++){
		if(!flag[pos[i]]){
			memset(flag + pos[i], true, sizeof(bool) * 2 * R);
			ans ++;
		}
	}
	cout << ans << endl;
}
*/


int N, R;
int pos[MAX_N];

void solve(){
	sort(pos, pos + N);
	int i = 0, ans = 0;
	while(i < N){
		int s = pos[i ++];
		while(i < N && pos[i] <= s + R) 
			i ++;
		int p = pos[i - 1];
		while(i < N && pos[i] <= p + R)
			i ++;
		ans ++;
	}
	cout << ans << endl;
}

int main(void){
	while(1){
		cin >> R;
		cin >> N;
		if(R == -1 && N == -1)
			break;
		for(int i = 0; i < N; i ++){
			cin >> pos[i];
		}
		solve();
	}
}
