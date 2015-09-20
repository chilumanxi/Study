/*************************************************************************
	> File Name: test.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月03日 星期四 22时13分59秒
    > test the cin.get()
************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    const int SIZE = 10;
    char buf[SIZE];
    cin.get(buf, SIZE);
    cout << buf;
    cin.get();
    //cin.clear();
    if(!cin){
        cout << "cin object error" << endl;
    }
    cin >> buf;
    cout << buf;
    return 0;
}
