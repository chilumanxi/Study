/*************************************************************************
	> File Name: Operator_crosslist.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Tue 27 Oct 2015 11:04:06 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define ElemType int
using namespace std;

typedef struct cnode{
    int row, col;
    ElemType value;
    struct cnode *right, *down;
}CNode, *CLink;

typedef struct{
    CLink *rowhead, *colhead;
    int rows, cols, nums;
}CrossList;

void Init_crosslist(CrossList &CL){
    CL.rows = 0;
    CL.cols = 0;
    CL.nums = 0;
    CL.rowhead = NULL;
    CL.colhead = NULL;
    return ;
}

void Creat_crosslist(CrossList &CL){
    CLink p, q;

    scanf("%d%d", &CL.rows, &CL.cols);
    
    CL.rowhead = (CLink *)malloc(sizeof(CLink) * (CL.rows + 1));
    if(CL.rowhead == NULL){
        printf("malloc the row's array failed!\n");
        return ;
    }
    for(int i = 1; i <= CL.rows; i ++)
        CL.rowhead[i] = NULL;
    CL.colhead = (CLink *)malloc(sizeof(CLink) * (CL.cols + 1));
    if(CL.colhead == NULL){
        printf("malloc the col's array failed!\n");
        return ;
    }
    for(int i = 1; i <= CL.cols; i ++)
        CL.colhead[i] = NULL;

    for(int i = 1; i <= CL.rows; i ++){
        for(int j = 1; j <= CL.cols; j++){
            int temp;
            scanf("%d", &temp);
            if(temp){
                p = (CLink)malloc(sizeof(CNode));
                if(p == NULL){
                    printf("malloc the node failed!\n");
                    return ;
                }
                p -> row = i;
                p -> col = j;
                p -> value = temp;
                if(!CL.rowhead[p -> row]){
                    p -> right = NULL;
                    CL.rowhead[p -> row] = p;
                }
                else{
                    for(q = CL.rowhead[p -> row]; q -> right != NULL && q -> right -> col < j; q = q -> right);
                    p -> right = q -> right;
                    q -> right = p;

                }

                if(!CL.colhead[p -> col]){
                    p -> down = NULL;
                    CL.colhead[p -> col] = p;
                }
                else{
                    for(q = CL.colhead[p -> col]; q -> down != NULL && q -> down -> col < i; q = q -> down);
                    p -> down = q -> down;
                    q -> down = p;
                }

                CL.nums ++;
            }
        }
    }

    return ;
}

void Add_matrix(CrossList a, CrossList b, CrossList &c, int flag){
    if(!(a.rows == b.rows && a.cols == b.cols)){
        printf("wrong size!\n");
        return ;
    }

    CLink insert;
    CLink p, q;
    CLink pr, *pc;

    c.rows = a.rows;
    c.cols = a.cols;
    c.nums = a.nums;

    c.rowhead = (CLink*)malloc(sizeof(CLink) * (c.rows + 1));
    if(c.rowhead == NULL){
        printf("malloc the third crosslist's row array failed!\n");
        return ;
    }
    for(int i = 1; i<= c.rows; i ++)
        c.rowhead[i] = NULL;

    c.colhead = (CLink *)malloc(sizeof(CLink) * (c.cols + 1));
    if(c.colhead == NULL){
        printf("malloc the third crosslist's col array failed!\n");
        return ;
    }
    for(int i = 1; i <= c.cols; i ++)
        c.colhead[i] = NULL;
    
    pc = (CLink *)malloc(sizeof(CLink) * (c.cols + 1));
    if(pc == NULL){
        printf("malloc the array of cols' last failed!\n");
        return ;
    }
    for(int i = 1; i <= c.cols; i ++)
        pc[i] = NULL;

    for(int i = 1; i <= a.rows; i ++){
        p = a.rowhead[i];
        q = b.rowhead[i];
        while(p != NULL && q != NULL){
            if(p -> col < q -> col){
                insert = (CLink)malloc(sizeof(CNode));
                if(insert == NULL){
                    printf("malloc the node of insert1 failed!\n");
                    return ;
                }

                insert -> row = i;
                insert -> col = p -> col;
                insert -> value = p -> value;
                insert -> right = NULL;
                p = p -> right;
                c.nums ++;
            }
            else{
                if(p -> col > q -> col){
                    insert = (CLink)malloc(sizeof(CNode));
                    if(insert == NULL){
                        printf("malloc the node of insert2 failed!\n");
                        return ;
                    }
                    insert -> row = i;
                    insert -> col = q -> col;
                    if(flag == 1)
                        insert -> value = q -> value;
                    else 
                        insert -> value = (-1) * q -> value;
                    insert -> right = NULL;
                    q = q -> right;
                    c.nums ++;
                }
                else{
                    int temp;
                    if(flag == 1){
                        temp = p -> value + q -> value;
                    }
                    else
                        temp = p -> value - q -> value;
                    if(temp != 0){
                        insert = (CLink)malloc(sizeof(CNode));
                        if(insert == NULL){
                            printf("malloc the node of insert3 failed!\n");
                            return ;
                        }

                        insert -> row = i;
                        insert -> col = p -> col;
                        insert -> value = temp;
                        insert -> right = NULL;

                        p = p -> right;
                        q = q -> right;

                        c.nums ++;
                    }
                    else{
                        p = p -> right;
                        q = q -> right;
                        continue;
                    }
                }
            }
            if(c.rowhead[i] == NULL){
                c.rowhead[i] = insert;
                pr = insert;
            }
            else{
                pr -> right = insert;
                pr = insert;
            }

            if(c.colhead[insert -> col] == NULL){
                c.colhead[insert -> col] = insert;
                pc[insert -> col] = insert;
            }
            else{
               pc[insert -> col] -> down = insert;
               pc[insert -> col] = insert;
            }
        }

        while(p != NULL){
            insert = (CLink)malloc(sizeof(CNode));
            if(insert == NULL){
                printf("malloc the node of insert failed!\n");
                return ;
            }
            insert -> row = i;
            insert -> col = p -> col;
            insert -> value = p -> value;
            insert -> right = NULL;
            p = p -> right;
            c.nums ++;

            if(c.rowhead[i] == NULL){
                c.rowhead[i] = insert;
                pr = insert;
            }
            else{
                pr -> right = insert;
                pr = insert;
            }

            if(c.colhead[insert -> col] == NULL){
                c.colhead[insert -> col] = insert;
                pc[insert -> col] = insert;
            }
            else{
                pc[insert -> col] -> down = insert;
                pc[insert -> col] = insert;
            }
        }
        
        while(q != NULL){
            insert =(CLink)malloc(sizeof(CNode));
            if(insert == NULL){
                printf("malloc the node of insert failed!\n");
                return ;
            }
            insert -> row = i;
            insert -> col = q -> col;
            if(flag == 1)
                insert -> value = q -> value;
            else 
                insert -> value = (-1) * q -> value;
            insert -> right = NULL;
            q = q -> right;
            c.nums ++;

            if(c.rowhead[i] == NULL){
                c.rowhead[i] = insert;
                pr = insert;
            }
            else{
                pr -> right = insert;
                pr = insert;
            }

            if(c.colhead[insert -> col] == NULL){
                c.colhead[insert -> col] = insert;
                pc[insert -> col] = insert;
            }
            else{
                pc[insert -> col] -> down = insert;
                pc[insert -> col] = insert;
            }
        }
    }

    //for(int j = 1; j <= c.nums; j ++){
    //    if(pc[j] != NULL)
    //        pc[j] -> down = NULL;
    //}

    free(pc);
    return ;

}

void print_crosslist(CrossList &CL){
    CLink p;
    int res;
    for(res = 1; res <= CL.rows; res ++){
        if(!CL.rowhead){
            for(int i = 1; i <= CL.cols; i ++){
                printf("0 ");
            }
            printf("\n");
            continue;
        }
        else{
            p = CL.rowhead[res];
            for(int i = 1; i <= CL.cols; i ++){
                if(p != NULL && i == p -> col){
                    printf("%d ", p -> value);
                    p = p -> right;
                }
                else 
                    printf("0 ");
            }
            printf("\n");
        }
    }
    return ;
}

int main(void){
    CrossList CLa, CLb, CLc;
    int choose;
    Init_crosslist(CLa);
    Init_crosslist(CLb);
    Creat_crosslist(CLa);
    Creat_crosslist(CLb);
    print_crosslist(CLa);
    scanf("%d", &choose);
    puts("");
    print_crosslist(CLb);
    puts("");
    Add_matrix(CLa, CLb, CLc, choose);
    print_crosslist(CLc);
    return 0;
}
