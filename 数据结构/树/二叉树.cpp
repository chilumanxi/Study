/*************************************************************************
	> File Name: 二叉树.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年07月29日 星期三 00时34分32秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#define END '#'

using namespace std;

typedef char ElemType;

typedef struct BNode{
    ElemType data;
    struct BNode *leftchild;
    struct BNode *rightchild;
}*Tree;
//创建一个及结点
BNode * Buy_node(){
    BNode * s = (BNode *)malloc(sizeof(BNode));
    if(s == NULL)
        exit(1);
    s -> leftchild = s -> rightchild = NULL;
    return s;
}
//释放结点
void Free_node(BNode *p){
    free(p);
}
//前序遍历
void Preorder(BNode *p){
    if(p != NULL){
        cout << p -> data << "  ";
        Preorder(p -> leftchild);
        Preorder(p -> rightchild);
    }
}
//中序遍历
void Inorder(BNode *p){
    if(p != NULL){
        Inorder(p -> leftchild);
        cout << p -> data << "  ";
        Inorder(p -> rightchild);
    }
}

//后序遍历
void Pastorder(BNode *p){
    if(p != NULL){
        Pastorder(p -> leftchild);
        Pastorder(p -> rightchild);
        cout << p -> data << "  ";
    }
}

//创建一棵树，以#作为结束方案
BNode *CreateTree(){
    ElemType item;
    cin >> item;
    if(item == END)
        return NULL;
    else{
        BNode *s = Buy_node();
        s -> data = item;
        s -> leftchild = CreateTree();
        s -> rightchild = CreateTree();
        return s;
    }
}
//通过二级指针来创建树
void *CreateTree2(BNode **s){
    ElemType item;
    cin >> item;
    if(item == END)
        *s = NULL;
    else{
        *s = Buy_node();
        (*s) -> data = item;
        CreateTree2(&(*s) -> leftchild);
        CreateTree2(&(*s) -> rightchild);
    }
}

//通过指针和引用来创建树
void CreateTree3(BNode *&s){
    ElemType item;
    cin >> item;
    if(item == END)
        s = NULL;
    else{
        s = Buy_node();
        s -> data = item;
        CreateTree3(s -> leftchild);
        CreateTree3(s -> rightchild);
    }
}

//一次性读入参数字符串str
BNode *CreateTree4(ElemType *str){
    BNode *s = NULL;
    if(*str != END){
        s = Buy_node();
        s -> data = *str;
        s -> leftchild = CreateTree4(++ str);
        s -> rightchild = CreateTree4(++ str);
    }
    return s;
}
//在一个长度为n的子符串中找到一个元素,返回其位置
int findis(char *is, char x, int n){
    for(int i = 0; i < n; i ++){
        if(is[i] == x)
            return i;
    }
    return -1;
}

BNode *CreateTreePI(char *ps ,char *is ,int n){
    BNode *s = NULL;
    if(n > 0){
        s = Buy_node();
        s -> data = *ps;
        int pos = findis(is, *ps, n);
        if(pos == -1)
            exit(1);
        s -> leftchild = CreateTreePI(ps + 1, is, pos);
        s -> rightchild = CreateTreePI(ps + 1 + pos, is + 1 + pos, n - pos - 1);
    }
}
/*
int  main(void){
    Tree root = NULL;
    ElemType *ps = "ABCDEFGH";
    ElemType *is = "CBEDFAGH";
    int n = strlen(ps);
    root = CreateTreePI(ps, is, n);
    Preorder(root);
    cout << endl;
    Inorder(root);
    cout << endl;
    Pastorder(root);
    cout << endl;
    return 0;
}
*/

int main(void){
    Tree root = NULL;
    root = CreateTree();
    //CreateTree2(&root);
    //CreateTree3(root);
    /*ElemType *br = "ABC##DE##F##G#H##";
    int n = strlen(br);
    root = CreateTree4(br);
    */
    Preorder(root);
    cout << endl;
    Inorder(root);
    cout << endl;
    Pastorder(root);
    cout << endl;
    return 0;
}
