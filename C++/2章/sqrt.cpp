/*************************************************************************
	> File Name: sqrt.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月02日 星期三 20时51分00秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int main(){
    using namespace std;

    double area;
    cout << "Enter the floor area, in square feet, of your home: ";
    cin >> area;
    double side;
    side = sqrt(area);
    cout << "Thar's the equivalent of a square " << side 
         << " feet to the side" << endl;
    cout <<  "How fascinating!" << endl;
    return 0;
}

