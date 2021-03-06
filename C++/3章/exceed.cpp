/*************************************************************************
	> File Name: exceed.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月02日 星期三 22时07分45秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#define ZERO 0

using namespace std;

int main(){
    short sam = SHRT_MAX;   //initialize a variable to max value
    unsigned short sue = sam;   //okay if variable sam already defined

    cout << "Sam has " << sam << " dollars and Sue has " << sue;
    cout << " dollars deposited." << endl
         << "Add $1 to each account." << endl << "Now ";
    sam = sam + 1;
    sue = sue + 1;
    cout << "Sam has " << sam << " dollars and Sue has " << sue;
    cout << " dollars deposited.\nPoor Sam!" << endl;

    sam = ZERO;
    sue = ZERO;
    cout << "Sam has " << sam << " dollars and Sue has " << sue;
    cout << " dollars deposited." << endl;
    cout << "Take $1 from each account." << endl << "Now ";
    sam = sam - 1;
    sue = sue - 1;
    cout << "Sam has " << sam << " dollars and Sue has " << sue;
    cout << " dollars deposited." << endl << "Lucky Sue!" << endl;
    return 0;
}
