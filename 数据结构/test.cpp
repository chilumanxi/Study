#include<iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

typedef struct list
{    
   int row;
   int colum;
   int value; 
   struct list *right;//the next element have the same row
   struct list *down;//the next element have the same colum  
}node,*element;

typedef struct link
{  
   int row_size;
   int colum_size;  
   int non_zero_amount;
   element *rhead;//the base of the row  
   element *chead;//the base of the colum
}crosslist;

//��ʼ������
int init_matrix(crosslist &one)
{  
   one.row_size=0;
   one.colum_size=0;   
   one.non_zero_amount=0;
   one.rhead=NULL;
   one.chead=NULL;
   return 1;   
}

//����һ������
int creat_matrix(crosslist &one)
{     
   int i;
   element news,temp; 
   
   /*input row size ,colum size and non zero amount*/
   printf("��������������������������Ԫ�صĸ���:\n");
   cin>>one.row_size;
   cin>>one.colum_size;
   cin>>one.non_zero_amount;

   /*allocate memory and the first memory not use*/
   one.rhead=(element*)malloc(sizeof(element)*(one.row_size+1));
   assert(one.rhead!=NULL);//assert have space  
   one.chead=(element*)malloc(sizeof(element)*(one.colum_size+1));
   assert(one.chead!=NULL);

   /*set all the pointer to NULL*/
   for(i=1;i<=one.row_size;i++)
   one.rhead[i]=NULL;
   for(i=1;i<=one.colum_size;i++)
   one.chead[i]=NULL;

   printf("/**************************************/\n");  
   printf("��������Ԫ��Ԫ�����ڵ��кţ��кź���ֵ:\n");

   for(i=1;i<=one.non_zero_amount;i++)
   {//insert all non zero elements

       news=(element)malloc(sizeof(node));
       assert(news!=NULL);
       cin>>news->row;
	   cin>>news->colum;
	   cin>>news->value;
	   
       if(!one.rhead[news->row])
	   {//if there's no node in the row
           news->right=NULL;
           one.rhead[news->row]=news;
	   }
       else
      	{
           for(temp=one.rhead[news->row];temp->right!=NULL;temp=temp->right)  NULL;
           news->right=temp->right;
           temp->right=news;
	   }

       if(!one.chead[news->colum])
	   {
           news->down=NULL;
           one.chead[news->colum]=news;
	   }
       else
	   {
           for(temp=one.chead[news->colum];temp->down!=NULL;temp=temp->down) NULL;
           news->down=temp->down;
           temp->down=news;
	   }

   }//for
   printf("/**************************************/\n");
   return 1;

}//creat_matrix



//�������
int print_matrix(crosslist &one)
{
   element temp;
   int count,i;
   for(count=1;count<=one.row_size;count++)
   {
      if(!one.rhead[count])
	  {
		 for(int i=1;i<=one.colum_size;i++) cout<<"0 ";
		 cout<<endl;
         continue;
	  }
      else
	  {
		  temp=one.rhead[count];
          for(i=1;i<=one.colum_size;i++)
		  {  
			  if(temp!=NULL&&i==temp->colum) 
			  {
				  cout<<temp->value<<" ";
				  temp=temp->right;
			  }
			  else cout<<"0 ";
		  }
		  cout<<endl;
	  }//else  
   }//for
   return 1;
}//print_matrix



//ʮ��������ӷ�
int add_matrix(crosslist one,crosslist two,crosslist &three)
{
	assert(one.row_size==two.row_size&&one.colum_size==two.colum_size);//assert the two matrices are valid to add
    int i,j;
    element insert;//nodes to insert
    element pone,ptwo;
    element prow;//the last node of a row  
    element *pcolum;//array that contains the last node of every colum

    three.row_size=one.row_size;
    three.colum_size=one.colum_size;
    three.non_zero_amount=0;

    three.rhead=(element*)malloc(sizeof(element)*(three.row_size+1));
    assert(three.rhead!=NULL);

    three.chead=(element*)malloc(sizeof(element)*(three.colum_size+1));
    assert(three.chead!=NULL);

    pcolum=(element*)malloc(sizeof(element)*(three.colum_size+1));
    assert(pcolum!=NULL);

    for(i=1;i<=three.row_size;i++)
    three.rhead[i]=NULL;
    for(i=1;i<=three.colum_size;i++)
    three.chead[i]=NULL;
    for(i=1;i<=three.colum_size;i++)
    pcolum[i]=NULL;

    /*start addition in row order*/
    for(i=1;i<=one.row_size;i++)
	{
       pone=one.rhead[i];
       ptwo=two.rhead[i];	

       while(pone!=NULL&&ptwo!=NULL)//�зǿ�
	   {
          if(pone->colum<ptwo->colum)//1������кű�2�����С
		  {
             insert=(element)malloc(sizeof(node));
             assert(insert!=NULL);

             insert->row=i;
             insert->colum=pone->colum;
             insert->value=pone->value;
             insert->right=NULL;

             pone=pone->right;

             three.non_zero_amount++;
		  }
          else 
		  {
			  if(pone->colum>ptwo->colum)//1������кű�2����Ĵ�
			  {
				  insert=(element)malloc(sizeof(node));
                  assert(insert!=NULL);

				  insert->row=i;
				  insert->colum=ptwo->colum;
				  insert->value=ptwo->value;
				  insert->right=NULL;

				  ptwo=ptwo->right;

				  three.non_zero_amount++;
			  }
              else
			  {
				  if(pone->value+ptwo->value!=0)//1������кź�2�����һ�����ҺͲ�Ϊ��
				  {
					  insert=(element)malloc(sizeof(node));
				      assert(insert!=NULL);

				      insert->row=i;
				      insert->colum=ptwo->colum;
				      insert->value=pone->value+ptwo->value;
				      insert->right=NULL;

				      pone=pone->right;
				      ptwo=ptwo->right;

				      three.non_zero_amount++;
				  }
                  else//1������кź�2�����һ�����Һ�Ϊ��
				  { 
                      pone=pone->right;
                      ptwo=ptwo->right;
                      continue;
				  }
			  }
		  }
          /*insert into three and link row*/
          if(three.rhead[i]==NULL)
          three.rhead[i]=prow=insert;
          else
		  {
             prow->right=insert;
             prow=insert;
		  }
          /*colum link*/
          if(three.chead[insert->colum]==NULL)
          three.chead[insert->colum]=pcolum[insert->colum]=insert;
          else
		  {
              pcolum[insert->colum]->down=insert;
              pcolum[insert->colum]=insert;
		  }
	   }//while

       /*insert the other nodes in one*/
       while(pone!=NULL)
	   {
          insert=(element)malloc(sizeof(node));
          assert(insert!=NULL);
          insert->row=i;
          insert->colum=pone->colum;
          insert->value=pone->value;
          insert->right=NULL;
          pone=pone->right;	
          three.non_zero_amount++;

          /*row link*/
          if(three.rhead[i]==NULL)
          three.rhead[i]=prow=insert;
          else
		  {
             prow->right=insert;
             prow=insert;
		  }

          /*colum link */
          if(three.chead[insert->colum]==NULL)
          three.chead[insert->colum]=pcolum[insert->colum]=insert;
          else
		  {
            pcolum[insert->colum]->down=insert;
            pcolum[insert->colum]=insert;
		  }
	   }//while

       /*insert the other nodes in two*/
       while(ptwo!=NULL)
	   {
           insert=(element)malloc(sizeof(node));
           assert(insert!=NULL);
           insert->row=i;
           insert->colum=ptwo->colum;
           insert->value=ptwo->value;
           insert->right=NULL;
           ptwo=ptwo->right;	
           three.non_zero_amount++;

           /*row link*/
           if(three.rhead[i]==NULL)
           three.rhead[i]=prow=insert;
           else
           {
               prow->right=insert;
               prow=insert;
		   }

           /*colum link */
           if(three.chead[insert->colum]==NULL)
           three.chead[insert->colum]=pcolum[insert->colum]=insert;
           else
		   {
              pcolum[insert->colum]->down=insert;
              pcolum[insert->colum]=insert;
		   }
	   }//while
	}//for

    three.non_zero_amount=three.non_zero_amount;
    for(j=1;j<=three.colum_size;j++)
	{//set the nonzero pcolum to null
        if(pcolum[j]!=NULL)
        pcolum[j]->down=NULL;
	}

    /*free pcolum's memory*/
    free(pcolum);
    return 1;
}//add_matrix


//�Ѿ����Ԫ��ת��Ϊ���ǵ��෴��
int opposite_matrix(crosslist &one)
{
   element temp;
   int count;
   for(count=1;count<=one.row_size;count++)
   {
      if(!one.rhead[count]) continue;
      else
	  {
		  temp=one.rhead[count];
   
		  while(temp!=NULL) 
		  {
			  temp->value=-temp->value;
		      temp=temp->right;
		  }
	  }//else  
   }//for
   return 1;
}//print_matrix




int multi_matrix(crosslist one,crosslist two,crosslist &three)
{
	assert(one.colum_size==two.row_size);

    int i,j;
    int value;//temp total value
    element insert;//the node to insert into three
    element pone,ptwo;//use in traverse the node in one and two
    element prow,pcolum;//mark the last row and colum node

    three.row_size=one.row_size;
    three.colum_size=two.colum_size;
    three.non_zero_amount=0;	

    three.rhead=(element*)malloc(sizeof(element)*(three.row_size+1));
    assert(three.rhead!=NULL);
    three.chead=(element*)malloc(sizeof(element)*(three.colum_size+1));
    assert(three.chead!=NULL);	

    for(i=1;i<=three.row_size;i++)
    three.rhead[i]=NULL;
    for(i=1;i<=three.colum_size;i++)
    three.chead[i]=NULL;	

    for(i=1;i<=one.row_size;i++)
	{
		for(j=1;j<=two.colum_size;j++)
		{
			pone=one.rhead[i];
            ptwo=two.chead[j];	
            value=0;
            while(pone!=NULL&&ptwo!=NULL)
			{
               if(pone->colum==ptwo->row)
			   {	
                  value+=pone->value*ptwo->value;	
                  pone=pone->right;//to the next node node in same row
                  ptwo=ptwo->down;//point to the next node in same colum
                  while(pone!=NULL&&ptwo!=NULL)
				  {//for the emtire row and colum
                     if(pone->colum==ptwo->row)
					 {
                        value+=pone->value*ptwo->value;
                        pone=pone->right;
                        ptwo=ptwo->down;
					 }
                     else if(pone->colum>ptwo->row)	
					 {
                        ptwo=ptwo->down;
                        continue;
					 }
                     else
					 {
                        pone=pone->right;
                        continue;
					 }	
				  }//while
                  if(value==0) break;	
                  insert=(element)malloc(sizeof(node));
                  assert(insert!=NULL);
                  insert->row=i;
                  insert->colum=j;
                  insert->value=value;
                  insert->right=NULL;
                  insert->down=NULL;
                  three.non_zero_amount++;	
                  /*insert into c and row link*/
                  if(three.rhead[i]==NULL)
                  three.rhead[i]=prow=insert;
                  else
				  {
                     prow->right=insert;
                     prow=insert;
				  }
                  /*colum link*/
                  if(three.chead[j]==NULL)
                  three.chead[j]=pcolum=insert;
                  else
				  {
                     pcolum->down=insert;
                     pcolum=insert;
				  }
			   }//if (colum==row)
               else if(pone->colum>ptwo->row)	
			   {
                  ptwo=ptwo->down;
                  continue;
			   }
               else
			   {
                  pone=pone->right;	
                  continue;
			   }	
			}//while	
		}//inner for
	}//outter for
    return 1;
}//multi_matrix




int main(void)
{
	crosslist one,two,three;
    int choice;//as a mark of selection	
    char flag;//selection mark
    while(1)
	{
		system("cls");
        system("color 81");
        system("mode con cols=80 lines=400");
        system("title #Crosslist To Deal With Sparse Matrix#");
        printf("\t@*************************************************************@\n");
        putchar('\n');	
        printf("\t\t %c----------ϡ�����-Ӧ�ó���ϵͳ----------%c\n",2,2);
        putchar('\n');
        printf("\t@*************************************************************@\n");	
        printf("\t$*************************************************************$\n");
        printf("\t\t %c----------------����ѡ��-----------------%c\n",2,2);
        putchar('\n');	
        printf("\t\t %c-----------------------------------------%c\n",2,2);
        printf("\t\t %c <1> ϡ�����ļӷ����� %c\n",2,2);	
        printf("\t\t %c-----------------------------------------%c\n",2,2);
        printf("\t\t %c <2> ϡ�����ļ������� %c\n",2,2);	
        printf("\t\t %c-----------------------------------------%c\n",2,2);
        printf("\t\t %c <3> ϡ�����ĳ˷����� %c\n",2,2);	
        printf("\t\t %c-----------------------------------------%c\n",2,2);
        printf("\t\t %c <4> �˳�Ӧ�ó��� %c\n",2,2);	
        printf("\t\t %c-----------------------------------------%c\n",2,2);
        putchar('\n');
        printf("\t\t %c-----------����������Ϊ����-----------%c\n",2,2);	
        printf("\t$*************************************************************$\n");
        printf("\t\t!!ע�⣺�������ֹ�����밴 Ctrl +C\n");	
        printf("\t$*************************************************************$\n\n");
        printf("���������ѡ��:(1--4)\n");
        fflush(stdin);//������뻺����
        printf("���ѡ����:");
        scanf("%d",&choice);
	    putchar('\n');
        switch(choice)
        {
		case 1: printf("\t<�ӷ�����>\n");	
			putchar('\n');

			init_matrix(one);//��ʼ������one

			printf("\t<������һ������>\n");
			creat_matrix(one);
			putchar('\n');
			printf("��һ����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(one);
			printf("-------------------------------------------------\n");

			init_matrix(two);//��ʼ������two
			putchar('\n');
			printf("\t<�����ڶ�������>\n");
			creat_matrix(two);
			putchar('\n');
			printf("�ڶ�����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(two);
			printf("-------------------------------------------------\n");
			
			/*add the two matrix*/
	        putchar('\n');
			printf("�����������\n");

			init_matrix(three);//��ʼ������three
			putchar('\n');

			add_matrix(one,two,three);
			printf("�������:\n");
			printf("-------------------------------------------------\n");
			Sleep(1000);
			print_matrix(three);
			printf("-------------------------------------------------\n");
			system("pause");
			break;

		case 2: printf("\t<��������>\n");	
			putchar('\n');

			init_matrix(one);//��ʼ������one

			printf("\t<������һ������>\n");
			creat_matrix(one);
			putchar('\n');
			printf("��һ����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(one);
			printf("-------------------------------------------------\n");

			init_matrix(two);//��ʼ������two
			putchar('\n');
			printf("\t<�����ڶ�������>\n");
			creat_matrix(two);
			putchar('\n');
			printf("�ڶ�����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(two);	
			printf("-------------------------------------------------\n");

			/*add the two matrix*/
         	putchar('\n');
			printf("�����������\n");

			init_matrix(three);//��ʼ������three
			putchar('\n');
            opposite_matrix(two);
			add_matrix(one,two,three);
			printf("�������:\n");
			printf("-------------------------------------------------\n");
			Sleep(1000);
			print_matrix(three);
			printf("-------------------------------------------------\n");
			system("pause");
			break;

		case 3: printf("\t<�˷�����>\n");
            putchar('\n');

			init_matrix(one);//��ʼ������one
			putchar('\n');

			printf("\t<������һ������>\n");
			creat_matrix(one);
			putchar('\n');
			printf("��һ����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(one);
			printf("-------------------------------------------------\n");

			init_matrix(two);//��ʼ������two
			putchar('\n');
			printf("\t<�����ڶ�������>\n");
			creat_matrix(two);
			putchar('\n');
			printf("�ڶ�����������:\n");

			printf("-------------------------------------------------\n");
			print_matrix(two);
			printf("-------------------------------------------------\n");		

            /*multiply the two matrix*/
         	putchar('\n');
            printf("�����������\n");
            init_matrix(three);
            multi_matrix(one,two,three);
            printf("�������:\n");
			printf("-------------------------------------------------\n");
            Sleep(1000);
            print_matrix(three);
			printf("-------------------------------------------------\n");
            system("pause");
            break;

		case 4:	printf("��ȷ���˳�������<Y/N>?\n");
            fflush(stdin);
            scanf("%c",&flag);
            if(flag=='y'||flag=='Y'||flag=='\n')
			{
                printf("\t\t%c-------%c-------%c-------%c-------%c\n",2,2,2,2,2);
                putchar('\n');
                printf("\t\t(^_^)ллʹ��!(^_^)\n");	
                putchar('\n');
                printf("\t\t%c-------%c-------%c-------%c-------%c\n",2,2,2,2,2);
                putchar('\n');
                Sleep(2000);
                exit(1);
			}
            else  
			{
                printf("��������ӭ����ʹ�á�����\n");
                Sleep(2000);
			}
            break;

		default:printf("��������Ч��ѡ�� 1 ~ 4!\n");
            Sleep(2000);
            break;
       }//switch
    }//while	
    return 1;
}

