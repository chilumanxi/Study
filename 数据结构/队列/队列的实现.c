/*************************************************************************
    > File Name: 队列的实现.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月22日 星期三 20时35分35秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
//链表
typedef struct cQueue{
	int data;
	struct cQueue *next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(Q.front == NULL)
		exit(OVERFLOW);
	Q.front -> next = NULL;
	return OK;
}

int DestroyQueue(LinkQueue &Q){
	while(Q.front != NULL){
		Q.rear = Q.front -> next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

int EnQueue(LinkQueue &Q, int e){
	QueuePtr q;
	q = (QueuePtr)malloc(sizeof(QNode));
	q -> data = e;
	q -> next = NULL;
	Q.rear -> next = q;
	Q.rear = q;
	return OK;
}

int DeQueue(LinkQueue &Q){
	QueuePtr q;
	int e;
	if(Q.front == Q.rear)
		return ERROR;
	q = Q.front -> next;
	e = q -> data;
	Q.front -> next = q -> next;
	if(Q.rear == q)
		Q.rear = Q.front;
	free(q);
	return e;
}

int ClearQueue(LinkQueue &Q){
	QueuePtr q;
	q = Q.front;
	while(q -> next != NULL){
		Q.front = Q.front -> next;
		free(q);
		q = Q.front;
	}
	Q.rear = NULL;
	return OK;
}

int QueueEmpty(LinkQueue Q){
	if(Q.front -> next == NULL)
		return OK;
	else 
		return ERROR;
}

int GetHead(LinkQueue Q){
	if(!QueueEmpty(Q))
		return Q.front -> next -> data;
	else 
		return ERROR;
}

int main(void){
	LinkQueue Queue;
	int a[8] = {3, 8, 5, 17, 9, 30, 15, 22};
	int i;
	InitQueue(Queue);
	for(i = 0; i < 8; i ++){
		EnQueue(Queue, a[i]);
	}
	printf("%d ", DeQueue(Queue));
	printf("%d ", DeQueue(Queue));
	EnQueue(Queue, 68);
	printf("%d ", GetHead(Queue));
	printf("%d ", GetHead(Queue));
	while(!QueueEmpty(Queue)){
		printf("%d ", DeQueue(Queue));
	}
	printf(" ");
	ClearQueue(Queue);
	return 0;
}
