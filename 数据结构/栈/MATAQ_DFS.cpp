/*************************************************************************
	> File Name: 马踏棋盘.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月23日 星期三 12时32分35秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
const int OK = 1;
const int ERROR = 0;
const int N = 8;
const int STACK_SIZE = 1000;
const int STACKINCREMENT = 10;


int dx[8] = {2, 1, -1, -2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int Path[N + 1][N + 1];
int n = 1;
int count;
bool flag[N +1][N + 1];
bool ans = false;

typedef struct{
    int x;
    int y;
}POS;

typedef struct{
    POS *base;
    POS *top;
    int stacksize;
}SqStack;

SqStack stack;

bool Init_Stack(){
    stack.base = (POS*)malloc(sizeof(POS) * STACK_SIZE);
    if(stack.base == NULL)
        return ERROR;
    stack.top = stack.base;
    stack.stacksize = STACK_SIZE;
    return OK;
}

POS GetTop_Stack(){
    if(stack.top == stack.base)
        exit(0);
    else
        return *(stack.top - 1);
}

bool Push_Stack(POS e){
    if(stack.top - stack.base  >= stack.stacksize){
        stack.base = (POS*)realloc(stack.base, (stack.stacksize + STACKINCREMENT) * sizeof(POS));
        if(stack.base == NULL){
            exit(0);
        }
        stack.top = stack.base + stack.stacksize;
        stack.stacksize += STACKINCREMENT;
    }
    *stack.top++ = e;
    return OK;
}

bool Empty_Stack(){
    if(stack.top == stack.base)
        return OK;
    else return ERROR;
}

bool Pop_Stack(){
    if(Empty_Stack()){
        return ERROR;
    }
    else
        --stack.top;
    return OK;
}


bool Pass(int x, int y){
    if(x <= N && x > 0 && y <= N && y > 0 && !flag[x][y])
        return OK;
    else
        return ERROR;
}

void Print_stack(){
    POS e;
    int i = N * N;
    while(stack.top != stack.base){
        e = GetTop_Stack();
        Path[e.x][e.y] = i --;
        Pop_Stack();
    }
    Path[stack.base -> x][stack.base -> y] = 1;
    for(int i = 1; i <= N; i ++){
        printf("\n");
        for(int j = 1; j <= N; j ++){
            printf("%d\t", Path[i][j]);
        }
    }
}

bool DFS(int x, int y, int step){
    if(step == N * N){
        Print_stack();
        ans = true;
        return OK;
    }
    for(int i = 0; i < 8; i ++){
        if(Pass(x + dx[i], y + dy[i])){
            POS e;
            e.x = x + dx[i];
            e.y = y + dy[i];
            flag[e.x][e.y] = true;
            Push_Stack(e);
            printf("%d\n",step);
            DFS(e.x, e.y, step + 1);
            if(ans) 
                return OK;
            flag[e.x][e.y] = false;
            Pop_Stack();
        }
    }
}

int main(void){
    int sx, sy;
    Init_Stack();
    memset(flag, false, sizeof(flag));
    printf("Pleease input the start pos:\n");
    printf("x:");
    scanf("%d", &sx);
    printf("y:");
    scanf("%d", &sy);
    POS e;
    e.x = sx;
    e.y = sy;
    Push_Stack(e);
    flag[sx][sy] = true;
    DFS(sx, sy, 1);
    if(!ans)
        printf("no answer!\n");
    return 0;
}

