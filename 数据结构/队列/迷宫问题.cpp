/*************************************************************************
	> File Name: 迷宫问题.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月17日 星期一 16时23分14秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int row, column;
int map[1000][1000];
int sx, sy, ex, ey;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0 ,-1, 1};
struct node{
    int x;
    int y;
    int lastn;
}q[1000001];

bool flag[1000][1000];

void print(int x){
    if(q[x].lastn != -1){
        print(q[x].lastn);
    }
    printf("(%d, %d)\n", q[x].x, q[x].y);
}

void bfs(){
    memset(flag, 0, sizeof(flag));
    int head = 0;
    int tail = 1;
    q[head].x = sx;
    q[head].y = sy;
    q[head].lastn = -1;
    while(head < tail){
        for(int i = 0; i < 4; i ++){
            int tempx = q[head].x + dx[i];
            int tempy = q[head].y + dy[i];
            if(flag[tempx][tempy] || tempx < 0 || tempx >= row || tempy < 0 || tempy >= column || map[tempx][tempy] == 1)
                continue;
            q[tail].x = tempx;
            q[tail].y = tempy;
            q[tail].lastn = head;
            flag[tempx][tempy] = true;
            if(tempx == ex && tempy == ey){
                print(tail);
            }
            tail ++;
        }
        head ++;
    }
}

int main(void){
    cout << "Please input the row and the column:" << endl;
    cin >> row >> column;
    cout << "Please input the Start pos :" << endl;
    cin >> sx >> sy;
    sx --;
    sy --;
    cout << "Please input the End pos :" << endl;
    cin >> ex >> ey;
    ex --;
    ey --;
    cout << "Please input the Maze :(0 for barry and 1 for road)" << endl;
    for(int i = 0; i < row; i ++){
        for(int j = 0; j < column; j ++){
            cin >> map[i][j];
        }
    }
    bfs();
    return 0;
}
