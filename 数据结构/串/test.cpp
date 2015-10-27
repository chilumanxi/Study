#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>
 

#define ALPHABET_LEN 256

uint32_t patlen;

#define NOT_FOUND patlen

#define max(a, b) ((a < b) ? b : a)
 
/*构造Bc表*/

void make_delta1(int *delta1, uint8_t *pat, int32_t patlen) {
    int i;
     

    /*初始化整个字符表的shift值为模式串P的长度(即case 2：出现坏字符时，P中无相同的字符)*/

    for (i=0; i < ALPHABET_LEN; i++) {

        delta1[i] = NOT_FOUND;
    }

    /*从左至右更新相同字符离失配位置(即patlen-1)的最近距离(case 1)*/

    for (i=0; i < patlen-1; i++) {

        delta1[pat[i]] = patlen-1 - i;
    }
}
 

/*Gs规则case 2：suffix-prefix对，从已匹配后缀[pos, wordlen)判断word是否存在前缀，

   即word[0, suffixlen) == word[pos, wordlen)
*/

int is_prefix(uint8_t *word, int wordlen, int pos) {
    int i;

    int suffixlen = wordlen - pos;

    // could also use the strncmp() library function here

    for (i = 0; i < suffixlen; i++) {

        if (word[i] != word[pos+i]) {

            return 0;
        }
    }
    return 1;
}
 

/*Gs规则case 1：suffix-suffix对，从pos向←查找与从P末尾（即已匹配后缀）向←查找相等的最长后缀，

   并返回最长后缀的长度
 */

int suffix_length(uint8_t *word, int wordlen, int pos) {
    int i;

    // increment suffix length i to the first mismatch or beginning of the word

    //比较范围[1, pos]与[patlen-pos, patlen-1], 注意:串word[0..pos]的后缀不包含自身

    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}
 
/*构造Gs表*/

void make_delta2(int *delta2, uint8_t *pat, int32_t patlen) {
    int p;

    int last_prefix_index = patlen-1;
 

    /*first loop：Gs规则case 2*/

    for (p=patlen-1; p>=0; p--) {

        if (is_prefix(pat, patlen, p+1)) { //从p+1开始的后缀是否存在前缀(p失配)

            last_prefix_index = p+1;      //last_prefix_index记录从右至左最后一个匹配字符的index(即p的右边)
        }

        //若存在前缀，保存最后一个匹配字符的index；否则，保存上次已匹配字符的index

        delta2[p] = last_prefix_index;                                       //@bug 1: + (patlen-1 - p);
    }
 

    /*second loop：Gs规则case 1，因为case 2是前缀，而中间的子串(可以看做[0,p]的suffix)也可能=P的suffix，

       且有可能不止一个中间子串，故p从左向后进行处理，保存最靠近P的suffix的对应子串前一个字符的shift长度
     */

    for (p=0; p < patlen-1; p++) {

        int slen = suffix_length(pat, patlen, p);         //末尾向左对应的从p向左的最长后缀的长度

        /*若已匹配suffix-suffix对的前导字符不匹配，保存向左的第一个失配字符的shift长度(即suffix-suffix对的起始位置之差)

           若匹配，则为前缀即case 2，无需改变shift值
         */

        if (slen > 0 && pat[p - slen] != pat[patlen-1 - slen]) {   //slen=0, 即case 3：delta2[patlen-1-slen]=delta2[patlen-1]=patlen

            delta2[patlen-1 - slen] = patlen-1 - p ;                    //@bug 2: + slen;
        }
    }
}
 

/*打印预处理得到的Bc表和Gs表*/

void print_pre_table(int *delta1, int *delta2, uint8_t *pat, uint32_t patlen){

      uint32_t i;

      printf("模式串：%s\n", pat);

      printf("坏字符shift表：\n");

      for (i=0; i < patlen-1; i++) {

          printf("(%c, %d)\n", pat[i], delta1[pat[i]]);
      }

      printf("(其他字符, %d)\n", NOT_FOUND);
 

      printf("\n好后缀shift表：\n");

      for (i=0; i < patlen; i++) {

           printf("(%u, %d)\n", i, delta2[i]);
      }
}
 

/*BM算法主框架*/

uint8_t boyer_moore (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen) {

    uint32_t i;

    int delta1[ALPHABET_LEN];

    int *delta2 = (int *)malloc(patlen * sizeof(int));

    make_delta1(delta1, pat, patlen);

    make_delta2(delta2, pat, patlen);

    print_pre_table(delta1, delta2, pat, patlen);
 

    i = patlen-1;

    while (i < stringlen) {

        int j = patlen-1;

        while (j >= 0 && (string[i] == pat[j])) {

            --i;

            --j;
        }

        if (j < 0) {

            free(delta2);

      return i+1;       //返回T中匹配的位置
        }
 

        i += max(delta1[string[i]], delta2[j]);   //j失配（ [j+1, patlen)已匹配 ），i向右移动的距离取主串T中坏字符delta1[string[i]]与模式串P中好后缀delta2[j]的大者
    }

    free(delta2);
return -1;
}
 
int main()
{

uint8_t pat[]="abracadabra";

uint8_t txt[]="abracadabtabradabracadabcadaxbrabbracadabraxxxxxxabracadabracadabra";

patlen = sizeof(pat)/sizeof(pat[0]) - 1;

uint32_t n = sizeof(txt)/sizeof(txt[0]) - 1;
 

uint8_t ans=boyer_moore(txt, n, pat, patlen);

printf("\n匹配位置:%d\n", ans);
return 0;
}

