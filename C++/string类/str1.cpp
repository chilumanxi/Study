/*************************************************************************
	> File Name: str1.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年08月15日 星期六 14时11分06秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int main(){
    string one("zhr winner!");
    cout << one << endl;               //zhr winner!
    string two(20, '$');
    cout << two << endl;               //$$$$$$$$$$$$$$$$$$$$
    string three (one);
    cout << three << endl;             
    one += " Oops!";
    cout << one << endl;               //zhr winner! Oops
    two = "Sorry! That was";
    three[0] = 'P';
    string four;
    four = two + three;                //Sorry! That wasPhr winner!
    cout << four << endl;
    char alls[] ="All's that ends well haha";
    string five(alls, 20);
    cout << five << "!\n";             //All's that ends well
    string six(alls + 6, alls + 10);  
    cout << six << ", ";              //that, 
    string seven(&five[6], &five[10]);
    cout << seven << "...\n";         //that...


    return 0;
}


/*
 * 运行结果：
 * zhr winner!
 * $$$$$$$$$$$$$$$$$$$$
 * zhr winner!
 * zhr winner! Oops!
 * Sorry! That wasPhr winner!
 * All's that ends well!
 * that, that...
 *
 */


/*
 * string 类的构造函数
 * string(const char *s)                将string对象初始化为s指向的NBTS(传统的C风格字符串)
 * string(size_type n, char c)          创建一个包含n个元素的string对象，其中每个元素都被初始化为字符c
 * string(const string &str, string size_type n = bpos)     将string对象初始化为对象str中从位置pos开始到结尾的字符，或从位置pos开始的n个字符
 * sting()                              创建一个默认的string对象， 长度为0
 * string(const char *s, size_type n)   将string对象初始化为s指向的NBTS中的前n个字符，即使超过了NBTS的结尾
 * template<class Iter>
 * string (Iter begin, Iter end)        将string对象初始化为区间[begin, end]内的字符，其中begin和end的行为就像指针，用于指定位置，范围包括begin在内，但是不包括end
 */



 /*
  * string类输入
  * 对于类，很有帮助的一点是，知道有哪些输入方式可用，对于C-风格字符串，有三种方式
  * char info[100]                          
  * cin >> info;                     //read a word
  * cin.getline(info, 100);          //read a line, discard \n
  * cin.get(info, 100);              //read a line, leave \n in queue
  *
  * 对于string对象
  * string stuff;
  * cin >> stuff;                    //read a word
  * getline(cin, stuff);             //read a line, discard \n
  *
  * 两个版本的getline()都有一个可选的参数，用于指定使用哪个字符来确定输入的边界
  * cin.getline(info, 100, ':');    //read up to :, discard :
  * getline(stuff, ':');      ``      //read up tp :; discard :
  *
  *string版本的getline将自动调整目标string对象的大小，使之能够存储输入的字符
  */
