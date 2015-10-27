/*************************************************************************
	> File Name: Horspool.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Thu 15 Oct 2015 09:51:45 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int Horspool(char *Str, int len_s, char *pattern, int len_p){
    if(len_s < len_p){
        cout << "ocuure failed!" << endl;
        return -1;
    }

    int next[256];
    for(int i = 0;i < 256; i ++)
        next[i] = len_p;
    for(int i = 0; i < len_p - 1; i ++)
        next[pattern[i]] = len_p - i - 1;

    int pos = 0;
    while(pos < len_s - len_p){
        int j = len_p - 1;
        while(j >= 0 && Str[pos + j] == pattern[j])
            j --;

        if(j < 0)
            break;
        pos = pos + next[Str[pos + len_p - 1]];
    }
    return pos;
}

int main(void){
    char pattern[] = "ATATA";
    char Str[] = "AGATACGATATATAC";

    int ans = Horspool(Str, strlen(Str), pattern, strlen(pattern));

    if(ans != -1)
        cout << "occure at the pos of :" << ans << endl;
    else 
        cout << "can not occure!" << endl;

    return 0;
}

