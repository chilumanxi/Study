/*************************************************************************
    > File Name: HASH表操作.cpp
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 09时11分17秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

//对HASH表和数据节点的定义
typedef struct _NODE{
	int data;
	struct _NODE *next;
}NODE;

typedef struct _HASH_TABLE{
	NODE *value[10];
}HASH_TABLE;


//创建哈希表
HASH_TABLE *create_hash_table(){
	HASH_TABLE *pHashTbl = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	memset(pHshTbl, 0, sizeof(HASH_TABLE));
	return pHashTble;
}

//在HASH表当中寻找数据
NODE* find_data_in_hash(HASH_TABLE *pHashTbl, int data){
	NODE *pNode;
	if(pHashTbl == NULL)
		return NULL;
	if((pNode = pHashTbl -> value[data % 10]) == NULL){
		return NULL;
	}
	while(pNode){
		if(data == pNode -> data)
			return pNode;
		pNode = pNode -> next;
	}
	return NULL;
}

//在hash表中插入数据
STATUS insert_data_into_hash(HASH_TABLE* pHshTbl, int data){
	NODE *pNode;
	if(pHashTbl == NULL)
		return FALSE;

	if(pHashTbl -> value[data % 10] == NULL){
		pNode = (NODE *)malloc(sizeof(NODE));
		memset(pNode, 0, sizeof(NODE));
		pNode -> data = data;
		pHashTbl -> value[data % 10] = pNode;
		return 1;
	}
	if(find_data_in_hash(pHashTbl, data) != NULL){
		return 0;
	}

	pNode = pHashTble -> value[data % 10];
	while(pNode -> next != NULL)
		pNode = pNode -> next;
	pNode -> next = (NODE*)malloc(sizeof(NODE));
	memset(pNode -> next, 0, sizeof(NODE));
	pNode -> next -> data = data;
	return 1;
}

//从hash表中删除数据
STATUS delete_data_from_hash(HASH_TABLE* pHashTbl, int data){
	NODE* pHead;
	NODE* pNode;
	if(pHashTbl == NULL || pHashTbl -> value[data % 10] == NULL)
		return 0;
	if((pNode = find_data_in_hash(pHashTbl, data)) == NULL)
		return 0;
	if(pNode == pHashTbl -> value[data % 10]){
		pHashTbl -> value[data % 10] = pNode -> next;
		goto final;
	}

	pHead = pHashTbl -> value[data % 10];
	while(pNode != pHead -> next){
		pHead = pHead -> next;
	}
	pHead -> next = pNode -> next;
	
final:
	free(pNode);
	return 1;
}
