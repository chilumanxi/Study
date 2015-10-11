/*************************************************************************
	> File Name: board_character.c
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Sat 03 Oct 2015 10:42:05 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "show_bytes.h"
typedef unsigned char *byte_pointer; 
int main(void){
    short sx = -12345;
    unsigned short usx = sx;
    int x = sx;
    unsigned ux = usx;

    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    printf("usx = %u\t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    printf("x = %d\t", x);
    show_bytes((byte_pointer) &x, sizeof(int));
    printf("ux = %d\t", ux);
    show_bytes((byte_pointer) &ux, sizeof(unsigned));

}
