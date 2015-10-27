/*************************************************************************
	> File Name: operator_triple.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Tue 27 Oct 2015 08:04:22 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 1000
#define ElemType int
using namespace std;

typedef struct{
    int row, col;
    ElemType value;
}Triple;

typedef struct{
    Triple data[MAX_SIZE];
    int rows, cols, nums;
}TSMatrix;
int N, M;

TSMatrix matrixa;
TSMatrix matrixb;
TSMatrix matrixc;

void Create_matrix(TSMatrix *matrix){
    int k = 1;
    int temp;
    scanf("%d%d", &N, &M);
    matrix -> rows = N;
    matrix -> cols = M;
    for(int i = 1; i <= N; i ++){
        for(int j = 1; j <= M; j ++){
            scanf("%d", &temp);
            if(!temp)
                continue;
            matrix -> data[k].value = temp;
            matrix -> data[k].row = i;
            matrix -> data[k].col = j;
            k ++;
        }
    }
    matrix -> nums = k - 1;
}

void print_matrix(TSMatrix m){
    int temp = 1;
    for(int i = 1; i <= N; i ++){
        for(int j = 1; j <= M; j ++){
            if(m.data[temp].row == i && m.data[temp].col == j){
                printf("%d ", m.data[temp].value);
                temp ++;
            }
            else 
                printf("0 ");
        }
        printf("\n");
    }
    return ;
}

void Add_matrix(TSMatrix *a, TSMatrix *b, TSMatrix *c, int flag){
    int resa = 1, resb = 1;
    c -> nums = 1;
    while(resa <= a -> nums && resb <= b -> nums){
        if((a -> data[resa].row == b -> data[resb].row) && (a -> data[resa].col == b -> data[resb].col)){
            int temp;
            if(flag == 1)
                temp = a -> data[resa].value + b -> data[resb].value;
            else 
                temp = a -> data[resa].value - b -> data[resb].value;
            if(temp){
                c -> data[c -> nums].value = temp;
                c -> data[c -> nums].row = a -> data[resa].row;
                c -> data[c -> nums ++].col = a -> data[resa].col;
            }
            resa ++;
            resb ++;
        }

        if(((a -> data[resa].row == b -> data[resb].row) && (a -> data[resa].col < b -> data[resb].col)) || (a -> data[resa].row < b -> data[resb].row)){
            c -> data[c -> nums].value = a -> data[resa].value;
            c -> data[c -> nums].row = a -> data[resa].row;
            c -> data[c -> nums ++].col = a -> data[resa].col;
            resa ++;
        }

        if(((a -> data[resa].row == b -> data[resb].row) && (a -> data[resa].col > b -> data[resb].col)) || (a -> data[resa].row > b -> data[resb].row)){
            if(flag == 1)
                c -> data[c -> nums].value = b -> data[resb].value;
            else 
                c -> data[c -> nums].value = (-1) * b -> data[resb].value;
            c -> data[c -> nums].row = b -> data[resb].row;
            c -> data[c -> nums ++].col = b -> data[resb].col;
            resb ++;
        }
    }

    while(resa <= a -> nums){
        c -> data[c -> nums].value = a -> data[resa].value;
        c -> data[c -> nums].row = a -> data[resa].row;
        c -> data[c -> nums ++].col = a -> data[resa].row;
        resa ++;
    }

    while(resb <= b -> nums){
        c -> data[c -> nums].value = b -> data[resb].value;
        c -> data[c -> nums].row = b -> data[resb].row;
        c -> data[c -> nums ++].col = b -> data[resb].col;
        resb ++;
    }
    return ;

}

int main(void){
    int choose;
    Create_matrix(&matrixa);
    print_matrix(matrixa);
    puts("");
    Create_matrix(&matrixb);
    print_matrix(matrixb);
    puts("");
    scanf("%d", &choose);
    Add_matrix(&matrixa, &matrixb, &matrixc, choose);
    print_matrix(matrixc);
    return 0;
}
