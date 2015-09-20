#include <stdio.h>
#include <malloc.h>
//定义结构体
typedef struct node
{  
    float coef; 
    int exp;//coef系数域,exp指数域
    struct node *next;
}SZ;
//建立单链表
SZ *creat() /*表尾插入*/
{
   SZ *h=NULL,*p,*t=NULL;
   int y; float x;
   t=h=(SZ *)malloc(sizeof(SZ));
   printf("停止输入时系数为0,指数0.\n");
   printf("按X的升幂输入系数和幂数:\n");
	scanf("%f",&x);
    scanf("%d",&y);
  while (x!=0)
  {
   p=(SZ *)malloc(sizeof(SZ));
   p->coef=x;
   p->exp=y; //p->next=NULL;
   t->next=p;
   t=p;
   scanf("%f",&x);
   scanf("%d",&y);
  }
  if(t!=NULL)  t->next=NULL;
   
    return(h);

}
//加法
void paixu(SZ *ha,SZ *hb)
{
            SZ *p,*q,*r,*pre;
            float x;                        // 临时存放系数
            p=ha->next;                           /*p和q志向多项式A，B第一个结点*/
            q=hb->next;
            pre=ha;                                       /*pre指向A头结点*/
         while((p!=NULL)&&(q!=NULL))
		 {
            if (p->exp==q->exp)               /*p,q的指数域相等*/
			{
               x=p->coef+q->coef;                             /*系数相加*/
               if (x!=0)                         /* 和不为0,修改p系数域*/
			   {
                p->coef=x;
                pre=p;
			   }
               else 
			   {
                 pre->next=p->next;
                 free(p);
			   }                            /*为0,删除A结点p*/
             
			   p=pre->next;
             
			   r=q;             //同时删除结点r.
             
			   q=q->next;   //wangxiazoujiedian
             
			   free(r);         
			}
            else 
             if (p->exp>q->exp)           /*将q插在p之前,q后移,p不动*/
			 {
                r=q->next;
                q->next=p;
                pre->next=q;
                pre=q;                 //neng zhi xiang xia yi xin jiedian
                q=r;
			 }
             else 
			 {
                 pre=p;
                 p=p->next;
			 }     /*p是和多项式中的一项,p后移 */

		 } 
               if (q!=NULL)             /*若B表长,则B剩余项插入A中*/
                pre->next=q;
                free(hb);
				 
}
//输出结果
void output(SZ *h)
{
       SZ *p; int i=0;
      p=h->next;
	/*  if(p->exp==0)
		  printf("%.1f",p->coef); //shuruchangshu.
	 // if(p->coef==1&&p->exp==1)
	//	printf("x");
      if(p->coef==-1&&p->exp==1)
		  printf("-x");
	  if(p->coef==-1&&p->exp!=1)
      printf("%.1fx",p->coef);*/
	 // p=p->next;
     while(p!=NULL)
	 {
		   if(p->coef!=0&&p->exp==0)
		  printf("%.1f",p->coef); //shuruchangshu.
		    if(p->coef==-1&&p->exp==1)
		     printf("-x");
	      if(p->coef==-1&&p->exp!=1&&p->exp!=0)
              printf("-x^%d",p->exp);
	 
	
	 // if(p->coef>0&&p->coef!=1&&p->exp!=1&&p->exp!=0)
      // printf("+%.1fx^%d",p->coef,p->exp);
	  if(i==0)
	  {
		   if(p->coef==1&&p->exp==1)
	    	  printf("x");
		   if(p->coef>0&&p->coef!=1&&p->exp!=1&&p->exp!=0)
			    printf("%.1fx^%d",p->coef,p->exp);
         
		  if(p->coef==1&&p->exp!=1&&p->exp!=0)
			  printf("x^%d",p->exp);
		    if(p->coef>0&&p->coef!=1&&p->exp==1)
            printf("%.1fx",p->coef);
	  }
	  else
	  { 
		 if(p->coef>0&&p->coef!=1&&p->exp!=1&&p->exp!=0)
         printf("+%.1fx^%d",p->coef,p->exp);
		  if(p->coef==1&&p->exp!=1)
	      printf("+x^%d",p->exp);
		   if(p->coef>0&&p->coef!=1&&p->exp==1)
            printf("%.1fx",p->coef);
	  }

      if(p->coef<0&&p->coef!=-1)
	    printf("%.1fx^%d",p->coef,p->exp);
	  
        p=p->next; i++;
	 }
      printf("\n");
}
int main()
{ 
	int m;
	for(;;)
	{
      SZ *ha,*hb;
      ha=creat();
      output(ha);
      hb=creat();
      output(hb);
      paixu(ha,hb);
      printf("输出结果：\n");
	  if (ha->next==NULL)
		 printf("0\n");
	  else
      output(ha);
	  printf("继续输1，停止输入0.");
	  scanf("%d",&m);
	  if(m==0)
		  break;
	}
	  
}
 
