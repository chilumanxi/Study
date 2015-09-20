/*************************************************************************
    > File Name: 区间调度问题.cpp
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com
    > Created Time: 2015年06月16日 星期二 10时55分54秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
#define MAX_N 100000

using namespace std;

void solve();

int N, S[MAX_N], T[MAX_N];

pair<int, int> itv[MAX_N];

void solve(){
	for(int i  = 0; i < N; i ++){
		itv[i].first = T[i];
		itv[i].second = S[i];
	}
	sort(itv, itv + N);

	int ans = 0, t = 0;

	for(int i = 0; i < N; i ++){
		if(t < itv[i]. second){
			ans ++;
			t = itv[i].first;
		}
	}
	cout << ans;
}

int main(void){
	cin >> N;
	for(int i = 0; i < N; i ++){
		cin >> S[i];
	}
	for(int i = 0 ; i < N; i ++){
		cin >> T[i];
	}
	solve();
	return 0;
}

