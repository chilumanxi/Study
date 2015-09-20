/*************************************************************************
    > File Name: 堆分配基本操作.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年06月02日 星期二 22时01分34秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define Status int
#define ERROR 0
#define OK 1
#define OVERFLOW -2


typedef struct{
	char *ch;
	int length;
}HString;


//------------堆分配基本操作--------------------
Status StrAssign(HString &T, char *chars){
	//生成一个其值等于串常量chars的串T
	int i, j;
	char *c;
	if(T.ch) 
		free(T.ch);      //释放T原有空间
	for(i = 0, c = chars; *c ; ++ i, ++ c);        //计算chars长度 
	if(!i){
			T.ch = NULL;
			T.length = 0;
	}
	else {
		if(!(T.ch = (char *)malloc(i * sizeof(char))))
			exit(OVERFLOW);
		for(j = 0; j <= i - 1; j ++)
			T.ch[j] = chars[j];
		T.length = i;
	}
	return OK;
}//StrAssign

int StrLength(HString S){
	//返回S的元素个数
	return S.length;
}// StrLength

int StrCompare(HString S, HString T){
	//若S > T则返回值大于0，若相等返回0，否则返回小于0
	int i;
	for(i = 0; i < S.length && i < T.length; i ++){
		if(S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}//StrCompare

Status ClearString(HString &S){
	//将S清为空串
	if(S.ch){
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}//ClearString

Status Concat(HString &T, HString S1, HString S2){
	//用T返回由S1和S2联结而成的新串
	int i;
	if(T.ch)
		free(T.ch);
	if(!(T.ch = (char *)malloc((S1.length + S2.length) * sizeof(char))))
		exit(OVERFLOW);
	for(i = 0; i <= S1.length - 1; i ++)
		T.ch[i] = S1.ch[i];
	for(i = S1.length; i <= S1.length + S2.length -1; i ++)
		T.ch[i] = S2.ch[i - S1.length];
	return OK;
}//Concat

Status SubString(HString &Sub, HString S, int pos, int len){
	//用Sub返回串S的第pos个字符起长度为len的子串
	//其中1 <= pos <= StrLength(S) - pos + 1
	int i;
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
		return ERROR;
	if(Sub.ch) 
		free(Sub.ch);
	if(!len){
		Sub.ch = NULL;
		Sub.length = 0;
	}
	else{
		Sub.ch = (char *)malloc(sizeof(char) * len);
		for(i = 0; i < len; i ++){
			Sub.ch[i] = S.ch[pos - 1 + i];
		}
		Sub.length = len;
	}
	return OK;
}//SubString

int main(void){
	char chars[20] = "i love linux";
	char Coms[20] = "i love C";
	HString S;
	HString T;
	HString L;
	L.ch = NULL;
	S.ch = NULL;
	T.ch = NULL;
	StrAssign(T, Coms);
	StrAssign(S, chars);
	printf("%s\n%d\n", S.ch, StrLength(S));
	printf("After comparing : %d\n", StrCompare(S, T));
	Concat(L, S, T);
	printf("After concat : %s\n", L.ch);
	SubString(L, S, 8, 5);
	printf("After substring : %s\n", L.ch);
	ClearString(S);
	ClearString(T);
	ClearString(L);
	return 0;
}
