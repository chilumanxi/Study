/*************************************************************************
	> File Name: matrix.cpp
	> Author: Zhanghaoran
	> Mail: chilumanxi@xiyoulinux.org
	> Created Time: Fri 16 Oct 2015 10:51:24 AM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int di[4][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
int ex, ey;
bool Suc = false;
bool vis[5][5];
int matrix[5][5];
bool check(int x, int y){
    if(x >= 0 && x < 5 && y >= 0 && y < 5 && matrix[x][y] != 1 && vis[x][y] != 1)
        return true;
    else 
        return false;
}

void dfs(int step, int tx, int ty){
    if(tx == ex && ty == ey){
        Suc = true;
        cout << "(" << tx << "," << ty << ")" << endl;
        cout << step << endl;
        return ;
    }

    for(int i = 0; i < 4; i ++){
        int tempx = tx + di[i][0];
        int tempy = ty + di[i][1];

        if(check(tempx, tempy)){
            vis[tempx][tempy] = true;
            dfs(step + 1, tempx, tempy);
            if(Suc){
                printf("(%d,%d)\n", tx, ty);
                return;
            }
            vis[tempx][tempy] = false;
        }
    }
}

int main(void){
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < 5; j ++)
            cin >> matrix[i][j];
    }
    ex = 4;
    ey = 4;

    dfs(0, 0, 0);

    return 0;
}
