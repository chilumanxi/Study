/*************************************************************************
	> File Name: Sunday.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Thu 15 Oct 2015 10:54:18 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;
int next[256];

void Sunday(char *Str, char *pattern){
    int len_p = strlen(pattern);
    int len_s = strlen(Str);
    for(int i = 0; i < 256; i ++)
        next[i] = len_p + 1;
    for(int i = 0; i < len_p - 1; i ++)
        next[pattern[i]] = len_p - i;
    int pos = 0;
    while(pos < len_s){
        int i = 0;
        while(Str[pos + i] == pattern[i]){
            i ++;
            continue;
        }
        if(i == len_p){
            cout << "occure at the pos of :" << pos << endl;
            return ;
        }
        pos += next[Str[pos + len_p]];   
    }

    cout << "can not occure!" << endl;
}

int main(void){
    char pattern[] = "abracadabra";
    char Str[] = "abracadabtabradabracadabcadaxbrabbracadabraxxxxxxabracadabracadabra";
    Sunday(Str, pattern);

    return 0;
}
