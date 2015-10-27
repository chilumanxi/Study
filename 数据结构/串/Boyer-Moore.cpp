/*************************************************************************
	> File Name: Boyer-Moore.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Thu 15 Oct 2015 08:30:32 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define max(a, b) ((a < b) ? b : a)
using namespace std;
int len_p;

void Creat_BC(int *bc, char *pattern, int len){
    for(int i = 0; i < 256; i  ++)
        bc[i] = len;
    for(int i = 0; i < len - 1; i ++)
        bc[pattern[i]] = len - 1 - i;
}

bool GS_judge(char *pattern, int len, int pos){
    int len_suff = len - pos;

    for(int i = 0; i < len_suff; i ++){
        if(pattern[i] != pattern[pos + i])
            return false;
    }
    return true;
}

int suffix_len(char *pattern, int len, int pos){
    int i;
    for(i = 0; (pattern[pos - i] == pattern[len - 1 - i]) && (i < pos); i ++);
    return i;
}

void Creat_GS(int *gs, char *pattern, int len){
    int last_index = len - 1;
    for(int i = len - 1; i >= 0; i --){
        if(GS_judge(pattern, len, i + 1))
            last_index = i + 1;
        gs[i] = last_index;
    }

    for(int i = 0; i < len - 1; i ++){
        int slen = suffix_len(pattern, len, i);
        if(slen > 0 && pattern[i - slen] != pattern[len - 1 - slen]){
            gs[len - 1 - slen] = len - 1 - i;
        }
    }
}

char boyer_moore(char *Str, int len_s, char *pattern, int len_p){
    int i;
    int bc[256];
    int *gs = (int *)malloc(len_p * sizeof(int));
    Creat_BC(bc, pattern, len_p);
    Creat_GS(gs, pattern, len_p);

    i = len_p - 1;
    while(i < len_s){
        int j = len_p - 1;
        while(j >= 0 && (Str[i] == pattern[j])){
            -- i;
            -- j;
        }
        if(j < 0){
            free(gs);
            return i + 1;
        }

        i += max(bc[Str[i]], gs[j]);
    }
    free(gs);
    return -1;
}

int main(void){
    char pattern[] = "abracadabra";
    char Str[] = "abracadabtabradabracadabcadaxbrabbracadabraxxxxxxabracadabracadabra";

    len_p = strlen(pattern);
    int len_s = strlen(Str);

    int ans = boyer_moore(Str, len_s, pattern, len_p);

    cout << "匹配位置：" << ans << endl;

    return 0;
}
