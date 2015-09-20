/*************************************************************************
	> File Name: Joseph_ring.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月20日 星期日 21时07分19秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int first_passwd;
int num_pe;

struct LNode{
    int num;
    int passwd;
    struct LNode *next;
}*Linklist;

struct LNode *phead1;

void Creat_list(){
    phead1 = (LNode *)malloc(sizeof(LNode));
    phead1 -> next = phead1;
}

void Insert_list(int x, int y){
    LNode *lastn = phead1;
    LNode *nextn = phead1 -> next;

    LNode *p = (LNode *)malloc(sizeof(LNode));
    p -> num = x;
    p -> passwd = y;

    if(nextn != NULL){
        for(; nextn != phead1; nextn = nextn -> next, lastn = lastn -> next);
    }
    lastn -> next = p;
    p -> next = nextn;
}

void Joseph_work(){
    LNode *movep = phead1 -> next;
    LNode *lastn = phead1;
    int flag = 0;
    int step = first_passwd;
    int temp = num_pe;
    while(temp --){
        if(flag == 0){
            flag = 1;
            for(int i = 1; i < step; i ++){
                movep = movep -> next;
                lastn = lastn -> next;
                if(movep == phead1)
                    i --;
            }
            step = movep -> passwd;
            printf("The number of %d is out of line, his passwd is %d\n", movep -> num, movep -> passwd);
            lastn -> next = movep -> next;
            free(movep);
            movep = lastn -> next;
            if(movep == phead1)
                movep = movep -> next;
        }
        else{ 
            for(int i = 1; i < step; i ++){
                movep = movep -> next;
                lastn = lastn -> next;

                if(movep == phead1)
                    i --;
            }
            step = movep -> passwd;
            printf("The number of %d is out of line, his passwd is %d\n", movep -> num, movep -> passwd);   
            lastn -> next = movep -> next;
            free(movep);
            movep = lastn -> next;
            if(movep == phead1)
                movep = movep -> next;
        }
    }
}

void Print_list(){
    LNode *p = phead1 -> next;
    int i  = 0;
    printf("I will show you all the persons and their passwd:\n");
    for(; p != phead1; p = p -> next){
        i ++;
        printf("the number of %d person's passwd is %d\n", p -> num, p -> passwd);
    }
}

int main(void){
    int temp_passwd;
    Creat_list();
    printf("please input the number of persons:\n");
    scanf("%d", &num_pe);
    printf("please input the first passwd:\n");
    scanf("%d", &first_passwd);
    printf("please input the passwd in order:\n");
    for(int i = 0; i < num_pe; i ++){
        scanf("%d", &temp_passwd);
        Insert_list(i + 1, temp_passwd);
    }
    Print_list();
    Joseph_work();

}
