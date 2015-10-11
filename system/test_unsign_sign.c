/*************************************************************************
	> File Name: test_unsign_sign.c
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Sat 03 Oct 2015 09:53:56 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    printf("0 == 0U is %d\n-1 < 0 is %d\n-1 < 0U is %d\n2147483647 > -2147483647-1 is %d\n2147483647 > -2147483647-1 is %d\n2147483647U > (int)2147483648U is %d\n -1 > -2 is %d\n(unsigned) -1 > -2 is %d\n", 0 == 0U, -1 < 0, -1 < 0U, 2147483647 > -2147483647-1, 2147483647U > -2147483647-1, 2147483647 > (int)2147483648U, -1 > -2, (unsigned) -1 > -2);
    return 0;
}
