/*************************************************************************
    > File Name: Best_Cow_Line.cpp
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com
    > Created Time: 2015年06月16日 星期二 11时28分45秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#define MAX_N 2001

using namespace std;

int N;
char S[MAX_N + 1];

void solve(){
	int a = 0, b = N - 1;
	int count = 0;
	while(a <= b){
		bool left = false;
		for(int i = 0; a + i <= b; i ++){
			if(S[a + i] < S[b - i]){
				left = true;
				count ++;
				break;
			}
			else if(S[a + i] > S[b - i]){
                left = false;
                count ++;
                break;
			}
		}
		if(left == true)
			putchar(S[a ++]);
		else
			putchar(S[b --]);
        if(count % 80 == 0)
            cout << endl;
		}
		cout << endl;
}

int main(void){
	cin >> N;
	for(int i = 0; i < N; i ++)
		cin >> S[i];
	solve();
}

