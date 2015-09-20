/*************************************************************************
    > File Name: link.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月06日 星期一 22时04分21秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node *next;
}Link;

int count = 1;

Link *create(){
	Link *head;
	Link *p1, *p2;
	p1 = p2 = (Link*)malloc(sizeof(Link));
	scanf("%d", &p1 -> data);
	while(p1 -> data != 0){
		if(count == 1){
			head = p1;
			p2 = p1;
			p1 -> next = NULL;
		}
		else{
			p2 -> next = p1;
			p2 = p1;
			p1 -> next = NULL;
		}
		scanf("%d", &p1 -> data);
	}
	free(p1);
	return head;
}

Link *insert(Link *head, int n){
	Link *p;
	Link *temp = head;
	int i;
	p = (Link*)malloc(sizeof(Link));
	for(i = 1; i < n; i ++){
		temp = temp -> next;	
	}
	scanf("%d", &p -> data);
	p -> next = temp -> next;
	temp -> next = p;	
	return head;
}

Link *del(Link *head, int n){
	Link *p1 = head -> next, *p2 = head;
	int i;
	if(n == 1){
		p1 = head;
		head = head -> next;
		free(p1);
	}
	else {
		for(i = 2; i < n; i ++){
			p1 = p1 -> next;
			p2 = p2 -> next;
		}
		p2 -> next = p1 -> next;
		free(p1);
	}
}

void print(Link *head){
	Link *temp;
	for(temp = head; temp != NULL; temp = temp -> next){
		printf("%d\t", temp -> data);
	}
	return ;
}

int main(void){
	Link *head;
	head = create();
	head =insert(head, 2);
	head =del(head, 5);
	print(head);
	return 0;
}

