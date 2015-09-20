/*************************************************************************
	> File Name: typecast.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月03日 星期四 20时49分03秒
    > forcing type changes
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    int auks, bats, coots;

    //the following statement adds the values as double, then converts the result to int
    auks = 19.99 + 11.99;

    //these statements add values as int
    bats = (int)19.99 + (int) 11.99;    //old C suntax
    coots = int (19.99) + int (11.99);  //new C++ suntax
    cout << "auks = " << auks << ", bats = " << bats;
    cout << ", coots = " << coots << endl;

    char ch = 'Z';
    cout << "The code for " << ch << " is ";
    cout << int(ch) << endl;
    cout << "Yes, the code is ";
    cout << static_cast<int>(ch) << endl;   //using static_cast
    return 0;
}
