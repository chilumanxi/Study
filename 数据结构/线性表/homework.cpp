/*************************************************************************
	> File Name: homework.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月07日 星期一 15时13分32秒
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#define Elemtype int
#define MAXLEN 512
#define INF 2>>14 
using namespace std;

struct Arrlist{
    Elemtype Data[MAXLEN];
    int Len;
};

struct node{
    Elemtype data;
    struct node *next;
}LNode, *LinkList;

LinkList head;
Arrlist array;

LNode *creatlist(LinkList p){
    p = (Elemtype *)malloc(sizeof(Elemtype));
    return p;
}

void Change_Arrlist(){
    int i;
    for(i = 0; i < n; i ++);
    int j = 0;
    int t;
    while(i < j){
        t = array.Data[i];
        array.Data[i] = array.Data[j];
        array.Data[j] = t;
        i --;
        j ++;
    } 
    return ;
}


void Change_Linlist(){
    LNode *p = head -> next;
    LNode *q = p;
    head -> next = NULL;
    while(p != NULL){
        p = p -> next;
        q -> next = head -> next;
        head -> next = q;
    }
    return ;
}

Elemtype Getmin_Arrlist(){
    Elemtype Min = INF;
mZ            Min = array.Data[i];
    }
    return Min;
}


