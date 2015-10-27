/*************************************************************************
	> File Name: KMP.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Wed 14 Oct 2015 08:04:22 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;
/*
void Next(const char pattern[], int next[]){
    int x, y;
    int len = strlen(pattern);

    next[0] = 0;
    for(x = 1, y = 0; x < len; x ++){
        while(y > 0 && pattern[x] != pattern[y])
            y = next[y - 1];
        if(pattern[x] == pattern[y])
            y ++;
        next[x] = y;
    }
}

int Kmp(const char Str[], const char pattern[], int next[]){
    int len_s = strlen(Str);
    int len_p = strlen(pattern);
    int temp;
    Next(pattern, next);
    for(int i = 0, temp = 0; i < len_s; i ++){
        while(temp > 0 && pattern[temp] != Str[i])
            temp = next[temp - 1];
        if(pattern[temp] == Str[i])
            temp ++;
        if(temp == len_p)
            cout << "Occure with the pos at : " << i - len_p + 1 << endl;
    }
}

int main(void){
    int next[100] = {0};
    char Str[] = "abaabacacababa";
    char pattern[] = "ababa";
    cout << Str << endl << pattern << endl;
    Kmp(Str, pattern, next);
    for(int i = 0; i < strlen(pattern); i ++){
        cout << next[i];
    }
    cout << endl;

    return 0;
}
*/

void getNext(const char *pattern, int *next){
    int i = 0, j = -1;
    next[0] = -1;
    while(i < strlen(pattern) - 1){
        if(j == -1 || pattern[i] == pattern[j])
            next[++ i] = ++ j;
        else 
            j = next[j];
    }
}

void getNext_opt(const char *pattern, int *next){
    int i = 0, j = -1;
    next[0] = -1;
    while(i < strlen(pattern) - 1){
        if(j == -1 || pattern[i] == pattern[j]){
            ++ i;
            ++ j;
            if(pattern[i] != pattern[j])
                next[i] = j;
            else 
                next[i] = next[j];
        }
        else j = next[j];
    }
}

int Kmp(const char *Str, const char *pattern, const int *next){
    int len_s = strlen(Str);
    int len_p = strlen(pattern);
    for(int i = 0, j = 0; i < len_s; i ++){
        while(j > 0 && pattern[j] != Str[i])
            j = next[j];
        if(pattern[j] == Str[i])
            j ++;
        if(j == len_p)
            cout << "Occure with the pos at : " << i - len_p + 1 << endl;
    }
}

int main(void){
    char Str[] = "ababvadcacbabcaca";
    char pattern[] = "abcac";
    int next[100] = {0};
    getNext(pattern, next);
    for(int i = 0; i < strlen(pattern); i ++)
        cout << next[i];
    cout << endl;
    memset(next, 0, sizeof(next));
    getNext_opt(pattern, next);
    for(int i = 0; i < strlen(pattern); i ++)
        cout << next[i];
    cout << endl;

    Kmp(Str, pattern, next);


    return 0;
}
