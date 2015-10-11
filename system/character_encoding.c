/*************************************************************************
	> File Name: character_encoding.c
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Sat 03 Oct 2015 04:45:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len){
    int i;
    for(i = 0; i < len; i ++)
        printf("%.2x", start[i]);
    printf(" ");
}
int main(void){
    short x = 12345;
    short mx = -x;

    show_bytes((byte_pointer) &x, sizeof(short));
    show_bytes((byte_pointer) &mx, sizeof(short));
    
    return 0;
}


//As a Little Endian, output 3930 cfc7
