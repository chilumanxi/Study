/*************************************************************************
	> File Name: strfile.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月15日 星期六 15时08分17秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;


int main(void){
    ifstream fin;
    fin.open("tobuy.txt");
    if(fin.is_open() == false){
        cerr << "Can't open file. Bye.\n";
        exit(EXIT_FAILURE);
    }
    string item;
    int count = 0;

    getline(fin, item, ':');
    while(fin){     //while input is good
        ++ count;
        cout << count << ": " << item << endl;
        getline(fin, item, ':');
    }    
    cout << "   Done\n";
    fin.close();
    return 0;
}

/*
 * 文件内容：
 * sardines:chocolate ice cream:pop corn:leeks:
 * cottage cheese:olive oil:butter:tofu:
 */

/*输出结果
 * 1: sardines
 * 2: chocolate ice cream
 * 3: pop corn
 * 4: leeks
 * 5: 
 * cottage cheese
 * 6: olive oil
 * 7: butter
 * 8: tofuL
 *
 *    Done
 *
 * 需要注意的是，将':'作为分界字符后，换行符被视为常规字符。因此文件第一行中末尾的换行符将称为包含"cottage cheese"的字符串中的第一个字符
 */
