/*************************************************************************
    > File Name: myPrim最小生成树.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月25日 星期一 12时10分05秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define INF 1000000
#define vertexes 6

typedef int Graph[vertexes][vertexes];

void Prim(Graph G, int count, int father[]){
	int low[vertexes];
	int closeset[vertexes];
	int used[vertexes];
	int i, j ,k, min;
	for(i = 0; i < count; i ++){
		low[i] = G[0][i];
		used[i] = 0;
		closeset[i] = 0;
		father[i] = -1;
	}
	used[0] = 1;
	for(i = 0; i < count - 1; i ++){
		j = 0;
		min = INF;
		for(k = 1; k < count; k ++)
			if(!used[k] && (low[k] < min)){
 	 			min = low[k];
			 	j = k;
			}
		father[j] = closeset[j];
		printf("%d %d\n", j + 1, closeset[j] + 1);
		used[j] = 1;
		for(k = 0; k < count; k ++)
			if(!used[k] && (G[k][j] < low[k])){
 			 	low[k] = G[j][k];
 				closeset[k] = j;
			}	
	}
}

int main(void){
	int i, j , weight;
	Graph G;
	int father[vertexes];
	for(i = 0; i < vertexes; i++)
		for(j = 0; j < vertexes; j++){
			scanf("%d", &G[i][j]);
			if(G[i][j] == 0)
				G[i][j] = INF;
		}
	Prim(G, vertexes, father);
	return 0;
}

