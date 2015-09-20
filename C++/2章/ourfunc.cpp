/*************************************************************************
	> File Name: ourfunc.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月02日 星期三 21时10分04秒
    > defining your own function
************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
void simon(int);    // function protototype for simon


int main(){
    simon(3);       // call the simon() function
    cout << "Pick an integer :";
    int count;
    cin >> count;
    simon(count);   // call it again
    cout << "Done!" << endl;
    return 0;
}

void simon(int n)   //define the simon() function
{
    cout << "Simon says touch your toes " << n << " times." << endl;
}   //void functions don't need return statements
