/*************************************************************************
    > File Name: Fence_Repair.cpp
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年06月16日 星期二 17时43分48秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
#define MAX_N 200001
using namespace std;

typedef long long ll;

int N, L[MAX_N];

void solve(){
	ll ans = 0;
	while(N > 1){
		int minest = 0;
		int minles = 1;
		if(L[minest] > L[minles])
			swap(minest, minles);
		for(int i = 2; i < N; i ++){
			if(L[i] < L[minest]){
				minles = minest;
				minest = i;
			}
			else if(L[i] < L[minles]){
				minles = i;
			}
		}

		int t = L[minest] + L[minles];
		ans += t;

		if(minest == N - 1)
			swap(minest, minles);
		L[minest] = t;
		L[minles] = L[N - 1];
		N --;
	}
	cout << ans << endl;
}


int main(void){
	cin >> N;
	for(int i = 0; i < N; i ++){
		cin >> L[i];
	}
	solve();
	return 0;
}
