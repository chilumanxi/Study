/*************************************************************************
	> File Name: RK.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Thu 15 Oct 2015 05:06:57 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int radix = 26;
const int prime = 3733799;
bool Match(const char *Str, const char *pattern, const int curs, const int len){
    for(int i = curs, j = 0; j != len; i ++, j ++)
        if(Str[i] != pattern[j])
            return false;
    
    return true;
}

int Rk(const char *Str, const char *pattern){
    int len_s = strlen(Str);
    int len_p = strlen(pattern);
    
    unsigned long Max_num = 1, Hash_p = 0, Hash_s = 0;
    for(int i = 0; i < len_p - 1; i ++)
        Max_num = (Max_num * radix) % prime;
    for(int i = 0; i < len_p; i ++){
        Hash_p = (radix * Hash_p + pattern[i] - 'a') % prime;
        Hash_s = (radix * Hash_s + Str[i] - 'a') % prime;
    }

    for(int i = 0; i < len_s - len_p + 1; i ++){
        if(Hash_p == Hash_s)
            if(Match(Str, pattern, i, len_p))
                return i;
        Hash_s = (radix * (Hash_s - Max_num * (Str[i] - 'a')) + Str[i + len_p] - 'a') % prime;
    }

    return -1;
        
}

int main(void){
    char pattern[] = "ababa";
    char Str[] = "abaababa";

    int ans = Rk(Str, pattern);

    if(ans != -1)
        cout << "occured at the pos of :" << ans << endl;
    else 
        cout << "can't occure !" << endl;

    return 0;
}

