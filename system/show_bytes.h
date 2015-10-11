/*************************************************************************
	> File Name: show_bytes.h
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Sat 03 Oct 2015 10:10:37 PM CST
 ************************************************************************/

#ifndef _SHOW_BYTES_H
#define _SHOW_BYTES_H
#define show_bytes(a, b){\
    int i;\
    for(i = 0; i < b; i ++)\
        printf("%.2x", a[i]);\
    printf(" ");\
}
#endif

