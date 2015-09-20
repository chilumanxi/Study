/*************************************************************************
	> File Name: numstr.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月04日 星期五 00时18分17秒
    > following number input with line input
************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    cout << "What year was your house built?\n";
    int year;
    cin >> year;
    cout << "What is its street address?\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year built: " << year << endl;
    cout << "Address: " << address << endl;
    cout << "Done!\n";
    return 0;
}


//运行的结果是用户根本没有输入地址的机会，问题在于，当cin读取年份，将回车键生成的换行符留在了输入队列中。后面的cin.getline()看到换行符后，将认为是一个空行，并将一个空字符串赋给address数组。解决方法是在读取地址之前先丢弃换行符。
