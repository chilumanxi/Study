/*************************************************************************
    > File Name: 变参与其数据结构.c
    > Author: zhanghaoran
    > Mail: 467908670@qq.com 
    > Created Time: 2015年05月30日 星期六 09时30分10秒
 ************************************************************************/
 /*
 *va_arg返回参数列表中的当前参数并使argp指向参数列表的下一个参数
 * va_copy(dest,src) dest和src的类型都是va_list,va_copy()用于复制参数列表指针，将dest初始化位src
 * va_end把argp指针清为NULL，函数体内可以多次遍历这些参数，但是都必须以va_start开始，并以va_end结尾．
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
/*
 * stdarg.h头文件中有如下几个宏定义:
 * #define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
 * #define va_start(ap,v) (ap = (va_list) &v + _INTSIZEOF(v)) //第一个可选参数的地址
 * #define va_arg(ap,t) (*(t*)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t))) // 下一个参数地址
 * #define va_end(ap)(ap =(va_list)0) //将指针置为无效
*/
int demo(char *msg, ...);
//函数声明，至少一个确定的参数，注意括号内的省略号

int main(){
	demo("DEMO", "This", "is", "a", "demo!", "");
	return 0;
}//ANSI标准形式的声明方式，括号内的省略号表示可选参数

int demo(char *msg, ...){
	va_list argp;
	int argno = 0;
	char *para = NULL;  //argp指向传入第一个可选参数，msg是最后一个确定的参数，因为是用栈来存储，msg实际上是在最上面(从右至左)压入栈
	va_start(argp, msg);
	printf("msg is %s\n", msg);
	while(1){
		para = va_arg(argp, char*); //每次指向下一个char *
		if(strcmp(para, "") == 0){
			break;
		}
		printf("parameter #%d is %s\n", argno, para);
		argno++;
	}
	va_end(argp);  //将argp置为NULL
	return 0;
}


/*va_list的用法
 * (1)首先在函数里定义一具VA_LIST型的变量,这个变量是指向参数的指针
 * (2)然后用VA_START宏初始变量刚定义的VA_LIST变量.这个宏的第二个参数是第一个可变参数的钱一个参数,是一个固定的参数
 * (3)然后用VA_ARG返回可变的参数,VA_ARG的第二个参数是你要返回的参数的类型
 * (4)最后用VA_END宏解数可变参数的获取.然后你就可以在函数里使用第二个参数了.如果函数有多个可变参数,依次调用VA_ARG获取各个参数
 *
 * VA_LIST在编译器中的处理:
 * (1)在运行VA_START(ap,v)以后,ap指向第一个可变参数在堆栈的地址
 * (2)VA_arg()取得类型t的可变参数值,在这步操作中首先apt = sizeof(t类型),让ap指向下一个参数的地址,然后返回ap-sizeof(t类型)的t类型*指针,这正是第一个可变参数在堆栈里的地址.然后用*取得这个地址的内容.
 * (3)VA_END(),x86平台定义为ap = ((char*)0),使ap不再指向堆栈,而是跟NULL奕扬,有些直接定义为((void*)0).这样编译器不会为VA_END产生代码,例如gcc在linux的x86平台上就是这么定义的
 * 要注意的是:由于参数的地址用于VA_START宏,所以参数不能声明位寄存器变量,或作为函数或数组类型.使用VA_LIST应该注意的问题:
 * (1)因为va_start,va_arg,va_end等定义为宏,所以它显得很愚蠢,可变参数的类型和个数完全在该函数中由程序代码控制,它并不能智能识别不同参数的个数和类型,也就说,你想智能识别可变参数的话要是通过在自己的程序里作判断实现的.
 * 另外有一个问题,因为编译器对可变参数的原型检查不够严格,对编程查错不利,不利于我们写出高质量的代码.
 *
 * 小结:可变参数的函数原理其实很简单,,而VA系列是以宏定义来定义的,实现跟堆栈相关,我们写一个可变函数的C函数时,有利也有弊,所以在不必要的场合我们无需用到可变参数,如果在C++中,我们应该用多态性来实现可变参数的功能,尽量避免用C语言的方式来实现.
