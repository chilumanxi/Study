/*************************************************************************
	> File Name: MATAQ_Greedy.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月25日 星期五 10时38分33秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define OK 1
#define ERROR 0
using namespace std;

struct Pos{
    int x;
    int y;
};
Pos Move_Pos(Pos , int &);

Pos dir[8]={{-1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {2, 1}, {2, -1}};

int Map[8][8];

struct Elemtype{
    Pos seat;
   // int step;
};

struct Elemtype S[65];
int top;

void Push_Stack(Elemtype e){
    S[top ++] = e;
 }

bool Empty_Stack(){
    return top == 0;
}

bool Pop_Stack(){
    top --;
}

Elemtype Top_Stack(){
    return S[top - 1];
}

bool Path_map(Pos start){
    top = 0;
    Pos cur_pos;
    Elemtype e;
    int flag_dir;
    cur_pos = start;
    int cur_step = 1;
    do{
        if(cur_pos.x >= 0 && cur_pos.y >= 0 && cur_pos.x < 8 && cur_pos.y < 8 && Map[cur_pos.x][cur_pos.y] == 0){
            Map[cur_pos.x][cur_pos.y] = cur_step;
            e.seat.x = cur_pos.x;
            e.seat.y = cur_pos.y;
          //  e.step = 0;
            Push_Stack(e);
            cur_step ++;
            printf("%d\n",cur_step);
            if(cur_step == 65)
                return true;
            flag_dir = 10;
            cur_pos = Move_Pos(cur_pos, flag_dir);
        }
      /*  else{
            if(!Empty_Stack()){
                e = Top_Stack();
                Pop_Stack();
                cur_step --;
                while(e.step == 7 && !Empty_Stack()){
                    Map[e.seat.x][e.seat.y] = 0;
                    e = Top_Stack();
                    Pop_Stack();
                    cur_step --;
                }
                if(e.step < 7){
                    e.step ++;
                    Push_Stack(e);
                    cur_step ++;
                    cur_pos = Move_Pos(e.seat, flag_dir);
                }
            }
        }
	*/
    }while(!Empty_Stack());
    return false;
}

void print_map(){
    int i, j;
    for(i = 0; i < 8; i ++){
        for(j = 0; j < 8; j ++)
            printf("%d\t", Map[i][j]);
    printf("\n");
    }
}

int Num_Next(Pos e){
    int icount = 0;
    for(int i = 0 ;i < 8; i ++){
        int tempx = e.x + dir[i].x;
        int tempy = e.y + dir[i].y;
        if(tempx < 0 || tempy < 0 || tempx > 7 || tempy > 7 || Map[tempx][tempy])
            continue;
        icount ++;
    }
    return icount;
}

Pos Move_Pos(Pos e, int &flag){
    Pos temp;
    int d = 0;
    int mina = 9;
    for(int i = 0; i < 8; i ++){
        if(i == flag)
            continue;
        temp.x = e.x + dir[i].x;
        temp.y = e.y + dir[i].y;
        if(temp.x < 0 || temp.y < 0 || temp.x > 7 || temp.y > 7 || Map[temp.x][temp.y])
            continue;
        int icount = Num_Next(temp);
        if(icount < mina){
            d = i;
            mina = icount;
        }
    }
    flag = d;
    e.x += dir[d].x;
    e.y += dir[d].y;
    return e;
}


int main(void){
    Pos start;
    for(int i = 0; i < 8; i ++)
        for(int j = 0; j <8; j ++)
            Map[i][j] = 0;
    printf("Please input the first pos:\n");
    printf("x:");
    scanf("%d", &start.x);
    printf("y:");
    scanf("%d", &start.y);
    start.x --;
    start.y --;
    if(Path_map(start)){
        printf("the MATAQ's path is below:\n");
        print_map();
    }
    else
        printf("can not find the path\n");
    return 0;
}

