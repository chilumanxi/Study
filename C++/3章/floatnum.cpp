/*************************************************************************
	> File Name: floatnum.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月03日 星期四 12时51分51秒
    > floating-point types
************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>


int main(){
    using namespace std;
    cout.setf(ios_base::fixed, ios_base::floatfield);   //fixed-point
    float tub = 10.0 / 3.0;
    double mint = 10.0 / 3.0;
    const float million = 1.0e6;

    cout << "tub = " << tub;
    cout << ", a million tubs = " << million * tub;
    cout << ", \nand ten million tubs = ";
    cout << 10 * million *tub << endl;

    cout << "mint = " << mint << " and a million mints = ";
    cout << million * mint << endl;
    return 0;
}
