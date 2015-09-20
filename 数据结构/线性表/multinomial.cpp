/*************************************************************************
	> File Name: multinomial.cpp
	> Author: Zhanghaoran0
	> Mail: chiluamnxi@gmail.com
	> Created Time: 2015年09月10日 星期四 12时21分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ERROR 0
#define OK 1
struct LNode{
    int num;
    int index;
    struct LNode *next;
}*Linklist;

struct LNode *phead1;
struct LNode *phead2;
struct LNode *phead3;

void Create_list(){
    phead1 = (LNode *)malloc(sizeof(LNode));
    phead2 = (LNode *)malloc(sizeof(LNode));
    phead3 = (LNode *)malloc(sizeof(LNode));
    phead2 -> next = NULL;
    phead1 -> next = NULL;
    phead3 -> next = NULL;
}

void Insert_list(int x, int y, int flag){
    LNode *p;
    LNode *lastn, *nextn;
    if(flag == 1){
        lastn = phead1;
        nextn = phead1 -> next;
        for(p = phead1 -> next; p != NULL; p = p -> next)
            if(p -> index == y){
                p -> num += x;
                return ;
            }
    }
    else if(flag == 2){
        lastn = phead2;
        nextn = phead2 -> next;
        for(p = phead2 -> next; p != NULL; p = p -> next)
            if(p -> index == y){
                p -> num += x;
                return;
            }
    }
    else if(flag == 3){
        lastn = phead3;
        nextn = phead3 -> next;
        for(p = phead3 -> next; p != NULL; p = p -> next)
        if(p -> index == y){
            p -> num += x;
            return ;
        }
    }

    p = (LNode *)malloc(sizeof(LNode));
    p -> num = x;
    p -> index = y;
    if(nextn != NULL){
            for(; nextn != NULL && nextn -> index < p -> index;){
                nextn = nextn -> next;
                lastn = lastn -> next;
            }
    }
    lastn -> next = p;
    p -> next = nextn;
}


void Delete_list(){
    LNode *p1 = phead1 -> next;
    LNode *p2 = phead2 -> next;
    LNode *temp1 = p1;
    LNode *temp2 = p2;
    while(p1 != NULL){
        p1 = p1 -> next;
        free(temp1);
        temp1 = p1;
    }

    while(p2 != NULL){
        p2 = p2 -> next;
        free(temp2);
        temp2 = p2;
    }
    phead1 -> next = NULL;
    phead2 -> next = NULL;
}


int  Analyze_str(char *str, int  mode){
    int i;
    int sec = 0;
    char num_str[20];
    int temp_num;
    int temp_index;
    int temp = 1;
    int flag = 0;
    for(i = 0; i < strlen(str); i ++)
    if((str[i] < '0' || str[i] > '9') && str[i] != '^' && str[i] != ' ' && str[i] != 'x' && str[i] != '+' && str[i] != '-'){
        printf("Input ERROR! Please input again!\n");
        return ERROR;
    }
//3+x+4+x^4+2x^2
     for(i = 0; i < strlen(str); i ++){
       if(str[i] == '+' || str[i] == '-' || (str[i] <= '9' && str[i] >= '0') || str[i] == 'x'){    //一开始只有这四种情况才能进入判断
            if(str[i] == '+' || str[i] == '-'){                         //'+'和'-'号为第一位的情况,直接将其存入字符串与第一个数字组成一个整体
                num_str[0] = str[i];                                    //跳过'+'和'-'号
                i ++;
                while(str[i] == ' ')                                    //跳过符号后面的空格
                    i ++;
                temp = 1;
                while(str[i] <= '9' && str[i] >= '0'){                  //如果符号后面是数字的情况
                    num_str[temp ++] = str[i ++];                       //将一整个数字存储
                    flag = 1;
                }
                if(flag == 1){
                    num_str[temp] = '\0';
                    flag = 0;
                }
                else{
                    if(num_str[0] == '+'){
                        num_str[0] = '1';
                        num_str[1] = '\0';
                    }
                    else if(num_str[0] == '-'){
                        num_str[0] = '-';
                        num_str[1] = '1';
                        num_str[2] = '\0';
                    }
                }
                if(i >= strlen(str)){
                        temp_num = atoi(num_str);
                        Insert_list(temp_num, 0, mode);
                        return OK;
                    }
                if(str[i] == 'x'){                                      //如果接下数字后面是x的话
                    temp_num = atoi(num_str);                           //将字符串数字转化为整形数字
                    i ++;                                               //自加1处理后面的情况.
                if(i >= strlen(str)){
                        temp_num = atoi(num_str);
                        Insert_list(temp_num, 1, mode);
                        return OK;
                    }
                    if(str[i] == '^'){                                  //如果x后面还有次幂项的话
                        i ++;
                        temp = 0;
                        while(str[i] <= '9' && str[i] >= '0'){
                            num_str[temp ++] = str[i ++];
                        }
                        num_str[temp] = '\0';
                        temp_index = atoi(num_str);
                        Insert_list(temp_num, temp_index, mode);
                        i --;
                        continue;
                    }
                    else if(str[i] == ' ' || str[i] == '+' || str[i] == '-'){
                        Insert_list(temp_num, 1, mode);
                        if(str[i] == ' '){
                            i ++;
                        }
                        i --;
                    }
                }
                else if(str[i] == ' ' || str[i] == '+' || str[i] == '-'){
                    temp_num = atoi(num_str);
                    Insert_list(temp_num, 0, mode);
                    if(str[i] == ' ')
                        i ++;
                    i --;
                    continue;
                }
            }
            else if(str[i] == 'x'){
                i ++;
                if(i >= strlen(str)){
                    Insert_list(1, 1, mode);
                    return OK;
                }
                if(str[i] == ' ' || str[i] == '+' || str[i] == '-'){
                    Insert_list(1, 1, mode);
                    while(str[i] == ' ')
                        i ++;
                    i --;
                    continue;
                }
                else if(str[i] == '^'){
                    i ++;
                    temp = 0;
                    while(str[i] <= '9' || str[i] >= '0'){
                        num_str[temp ++] = str[i ++];
                    }
                    num_str[temp] = '\0';
                    temp_index = atoi(num_str);
                    Insert_list(temp_num, temp_index, mode);
                    while(str[i] == ' ')
                        i ++;
                    i --;
                    continue;
                }
            }
            else if(str[i] <= '9' && str[i] >= '0'){
                temp = 0;
                while(str[i] <= '9' && str[i] >= '0'){
                    num_str[temp ++] = str[i ++];
                }
                num_str[temp] = '\0';
                temp_num = atoi(num_str);
                if(i >= strlen(str)){
                    Insert_list(temp_num, 0, mode);
                    return OK;
                }
                if(str[i] == 'x'){
                    i ++;
                    if(str[i] == '^'){
                        i ++;
                        temp = 0;
                        while(str[i] <= '9' && str[i] >= '0'){
                            num_str[temp ++] = str[i ++];
                        }
                        num_str[temp] = '\0';
                        temp_index = atoi(num_str);
                        Insert_list(temp_num, temp_index, mode);
                        while(str[i] == ' ' && i < strlen(str))
                            i ++;
                        i --;
                        continue;
                    }
                    else{
                        Insert_list(temp_num, 1, mode);
                        while(str[i] == ' ' && i < strlen(str))
                            i ++;
                        i--;
                        continue;
                    }
                }
                else if((str[i] == ' ' || str[i] == '+' || str[i] == '-') && i < strlen(str)){
                    Insert_list(temp_num, 0, mode);
                    while(str[i] == ' ')
                        i++;
                    i --;
                    continue;
                }
            }
        }
    }
}





void Print_list(int mode){
    LNode *p;
    LNode *temp;
    if(mode == 1){
        printf("The first multinomial you input is :\n");
        p = phead1 -> next;
        temp = p;
    }
    else if(mode == 2){
        printf("The third multinomial you input is :\n");
        p = phead2 -> next;
        temp = p;
    }
    else if(mode == 3){
        printf("After caculating, The answer is :\n");
        p = phead1 -> next;
        temp = p;
    }
    else{
        printf("After caculating, the answer is :\n");
        p = phead3 -> next;
        temp = p;
    }
    for(;p != NULL; p = p -> next){
        if(p -> num > 0 && p != temp){
            if(p -> num == 1){
                if(p -> index == 1){
                    printf("+x");
                }
                else if(p -> index == 0){
                    printf("+1");
                }
                else{
                    printf("+x^%d", p -> index);
                }
            }
            else{
                if(p -> index == 1){
                    printf("+%dx", p -> num);
                }
                else if(p -> index == 0){
                    printf("+%d", p -> num);
                }
                else{
                printf("+%dx^%d", p ->num, p ->index);
                }
            }
        }
        else{
            if(p -> num == 1){
                if(p -> index == 1){
                    printf("x");
                }
                else if(p ->index == 0){
                    printf("1");
                }
                else{
                    printf("x^%d", p -> index);
                }
            }
            else if(p -> num == 0){
                if(p -> next == NULL)
                    printf("0");
                else 
                    continue;
            }
            else{
                if(p -> index == 1){
                    printf("%dx", p -> num);
                }
                else if(p -> index == 0){
                    printf("%d", p -> num);
                }
                else{
                printf("%dx^%d", p ->num, p ->index);
                }
            }
        }
    }
    printf("\n");
}


void Add_mul(){
    char str[100];
    LNode *p1;
    LNode *p2;
    LNode *temp1;
    LNode *temp2;
    printf("please input the first multinomial:\n");
    gets(str);
    while(!Analyze_str(str, 1)){
        gets(str);
    }

    printf("Please input the seconde multinomial:\n");
    gets(str);
    while(!Analyze_str(str, 2)){
        gets(str);
    }
    Print_list(1);
    Print_list(2);


    p1 = phead1 -> next;
    p2 = phead2 -> next;
    temp1 = phead1;
    temp2 = phead2;
    while(p2 != NULL){
        if(p1 == NULL){
            temp1 -> next = p2;
            Print_list(3);
            return ;
        }
        if(p2 -> index < p1 -> index){
            temp2 -> next = p2 -> next;
            p2 -> next = temp1 -> next;
            temp1 -> next = p2;
            p2 = temp2 -> next;

        }
        else if(p2 -> index == p1 -> index){
            p1 -> num += p2 -> num;
            if(p1 -> num == 0){
                temp1 -> next = p1 -> next;
                free(p1);
                p1 = temp1 -> next;
                temp2 -> next = p2 -> next;
                free(p2);
                p2 = temp2 -> next;
            }
            else {
                temp2 ->next = p2 -> next;
                free(p2);
                p2 = temp2 ->next;
            }
        }
        else if(p2 -> index > p1 -> index){
            p1 = p1 -> next;
            temp1 = temp1 -> next;
        }
    }
    Print_list(3);
    Delete_list();
}

void Sub_mul(){
    LNode *p1;
    LNode *p2;
    LNode *temp1;
    LNode *temp2;
    char str[100];
    printf("please input the first multinomial\n");
    gets(str);
    while(!Analyze_str(str, 1)){
        gets(str);
    }

    printf("please input the second multinomial\n");
    gets(str);
    while(!Analyze_str(str, 2)){
        gets(str);
    }
    Print_list(1);
    Print_list(2);

    p1 = phead1 -> next;
    p2 = phead2 -> next;
    temp1 = phead1;
    temp2 = phead2;
    while(p2 != NULL){
        if(p1 == NULL){
            temp1 -> next = p2;
            while(p2 != NULL){
                p2 -> num = 0 - p2 -> num;
                p2 = p2 -> next;
            }
            if(phead1 -> next == NULL){
                printf("0\n");
                return ;
            }
            Print_list(3);
            return ;
        }
        if(p2 -> index < p1 -> index){
            temp2 -> next = p2 -> next;
            p2 -> next = temp1 -> next;
            temp1 -> next = p2;
            p2 -> num = 0 - p2 -> num;
            p2 = temp2 -> next;
        }
        else if(p2 -> index == p1 -> index){
            p1 -> num -= p2 -> num;
            if(p1 -> num == 0){
                temp1 -> next = p1 -> next;
                free(p1);
                p1 = temp1 -> next;
                temp2 -> next = p2 -> next;
                free(p2);
                p2 = temp2 -> next;
            }
            else{
                temp2 -> next = p2 -> next;
                free(p2);
                p2 = temp2 -> next;
            }
        }
        else if(p2 -> index > p1 -> index){
            p1 = p1 -> next;
            temp1 = temp1 -> next;
        }
    }
    if(phead1 -> next == NULL){
        printf("0");
        return ;
    }
    Print_list(3);
    Delete_list();
}


void MUL_mul(){
    char str[100];
    LNode *p1;
    LNode *p2;
    LNode *temp1;
    LNode *temp2;
    LNode *temp3;
    int ans_index, ans_num;
    int flag = 0;
    printf("please input the first multinomial\n");
    gets(str);
    while(!Analyze_str(str, 1)){
        gets(str);
    }

    printf("Please input the second multinomial\n");
    gets(str);
    while(!Analyze_str(str, 2)){
        gets(str);
    }

    Print_list(1);
    Print_list(2);
    
    for(p1 = phead1 -> next; p1 != NULL; p1 = p1 -> next){
        for(p2 = phead2 -> next; p2 != NULL; p2 = p2 -> next){
            ans_index = p1 -> index + p2 -> index;
            ans_num = p1 -> num * p2 -> num;
            Insert_list(ans_num, ans_index, 3);
        }
    }
    Print_list(4);
    Delete_list();
}

void Der_mul(){
    char str[100];
    LNode *p1;
    LNode *temp;
    printf("please input your multinomial:\n");
    gets(str);
    while(!Analyze_str(str, 1)){
        gets(str);
    }

    Print_list(1);

    for(p1 = phead1 -> next; p1 != NULL; p1 = p1 -> next){
        p1 -> num *= p1 -> index;
        p1 -> index --;
        if(p1 -> index == -1){
            p1 -> index = 0;
            p1 -> num = 0;
        }   
    }

    Print_list(3);
    Delete_list();

}

void Eva_mul(){
    char str[100];
    int x;
    long long sum = 0;
    LNode *p1;
    printf("please input your multinomial:\n");
    gets(str);
    while(!Analyze_str(str, 1)){
        gets(str);
    }

    Print_list(1);
    
    printf("please input the value of x:\n");
    scanf("%d", &x);
    for(p1 = phead1 -> next; p1 != NULL; p1 = p1 -> next){
        sum += pow(x, p1 -> index) * p1 -> num;
    }

    printf("After caculating, the answer is :%llu\n", sum);
    Delete_list();
}


//3+x+2x^3
//4-x+x^4
int main(void){
    int choose;
    Create_list();
    while(1){
        printf("Please choose the operation:\n");
        printf("-----------① ADD--------------\n");
        printf("-----------② SUB--------------\n");
        printf("-----------③ MUL--------------\n");
        printf("-----------④ DER--------------\n");
        printf("-----------⑤ EVA--------------\n");
        printf("-----------⑥ Quit-------------\n");

        scanf("%d", &choose);
        getchar();
        switch(choose){
            case 1:
                Add_mul();
                break;
            case 2:
                Sub_mul();
                break;
            case 3:
                MUL_mul();
                break;
            case 4:
                Der_mul();
                break;
            case 5:
                Eva_mul();
                break;
            case 6:
                return 0;
        }
    }


    return 0;
}

