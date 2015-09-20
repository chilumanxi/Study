/*************************************************************************
    > File Name: Prim最小生成树.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月25日 星期一 10时39分15秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 1000000
#define max_vertexes 6

typedef int Graph[max_vertexes][max_vertexes];

void prim(Graph G, int vcount, int father[]){
	int i, j, k;
	int lowcost[max_vertexes];
	int closeset[max_vertexes];
	int used[max_vertexes];
	int min;
	for(i = 0; i < vcount; i++){
		//最短距离初始化为其他节点到１号节点的距离
		lowcost[i] = G[0][i];
		//标记所有节点的依附点皆为默认的１号节点
		closeset[i] = 0;
		used[i] = 0;
		father[i] = -1;
	}
	used[0] = 1; //第一个节点是在ｓ集合里的
		//vcount个节点至少需要vcount - 1条边构成的最小生成树
	for(i = 1; i < vcount ; i++){
		j = 0;
		min = INF;
		//找满足条件的最小权值边的结点ｋ
		for(k = 1; k < vcount; k ++)
			//边权值较小且不在生成树中
			if(!used[k] && (lowcost[k] < min)){
				min = lowcost[k];
				j = k;
			}
		father[j] = closeset[j];
		printf("%d %d\n", j + 1, closeset[j] + 1); //打印边
		used[j] = 1;  //把第ｊ个顶点并入U中
		for(k = 1; k < vcount; k ++)
			if(!used[k] && G[j][k] < lowcost[k]){
				lowcost[k] = G[j][k];
				closeset[k] = j;    //记录新的依附点
			}
	}
}

int main(void){
	int i, j , weight;
	Graph G;
	int father[max_vertexes];
	for(i = 0; i < max_vertexes; i++)
		for(j = 0; j < max_vertexes; j++){
			scanf("%d", &G[i][j]);
			if(G[i][j] == 0)
				G[i][j] = INF;
		}
	prim(G, max_vertexes, father);
	return 0;
}
