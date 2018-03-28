/****************************************/
/*                aco.c                 */
/*  ���̹��� ����ȭ��(aco) ���α׷�     */
/*   aco�� �̿��Ͽ� �������� �н�       */
/*  ��� ���                           */
/*\Users\deeplearning\ch3>aco           */
/****************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/*��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>

/*   ��ȣ ��� ����                 */
#define NOA 10 /*������ ��ü ��*/
#define ILIMIT 50 /*�ݺ� Ƚ��*/
#define Q 3 /*��θ� ���� ����*/
#define RHO 0.8 /*���� ���*/
#define STEP 10 /*�� ���� �ܰ� ��*/
#define EPSILON 0.15 /*�ൿ ������ ���������� ����*/
#define SEED 32768 /*���� �õ�*/

/*   �Լ� ������Ÿ�� ����      */
void printp(double pheromone[2][STEP]) ;/*ǥ��*/
void printmstep(int mstep[NOA][STEP]) ;
                             /*������ �ൿ ǥ��*/
void walk(int cost[2][STEP]
          ,double pheromone[2][STEP]
          ,int mstep[NOA][STEP] ) ;/*���̸� �Ȱ� ��*/
void update(int cost[2][STEP]
         ,double pheromone[2][STEP]
        ,int mstep[NOA][STEP] ) ;/*��θ� ����*/
double rand1() ;/*0��1������ �Ǽ��� ��ȯ�ϴ� ���� �Լ�*/
int rand01() ;/*0 �Ǵ� 1�� ��ȯ�ϴ� ���� �Լ�*/

/**********************/
/*     main() �Լ�    */
/**********************/
int main()
{
 int cost[2][STEP]={/*�� �ܰ��� ���(�Ÿ�)*/
	 {1,1,1,1,1,1,1,1,1,1},
	 {5,5,5,5,5,5,5,5,5,5}};
 double pheromone[2][STEP]={0} ;/*�� �ܰ��� ��θ� ��*/
 int mstep[NOA][STEP] ;/*���̰� ���� ����*/
 int i;/*�ݺ� Ƚ�� ����*/
 
 /*���� �ʱ�ȭ*/
 srand(SEED) ;

 /*����ȭ*/
 for(i=0;i<ILIMIT;++i){
  /*��θ� ���� ���*/
  printf("%d:\n",i) ;
  printp(pheromone) ;
  /*���̸� �Ȱ� ��*/
  walk(cost,pheromone,mstep) ;
  /*��θ� ����*/
  update(cost,pheromone,mstep) ;
 }
 
 return 0 ;
}

/**************************/
/*    update() �Լ�        */
/*    ��θ� ����    */
/**************************/
void update(int cost[2][STEP]
        ,double pheromone[2][STEP]
        ,int mstep[NOA][STEP] )
{
 int m ;/*������ ��ü ��ȣ*/
 int lm ;/*���̰� ���� �Ÿ�*/
 int i,j ;
 double sum_lm=0 ;/*���̰� ���� �հ� �Ÿ�*/
 
 /*��θ� ����*/
 for(i=0;i<2;++i)
  for(j=0;j<STEP;++j)
   pheromone[i][j]*=RHO ;

 /*���̿� ���� ��ĥ*/
 for(m=0;m<NOA;++m){
  /*��ü m�� �̵� �Ÿ� lm�� ���*/
  lm=0 ;
  for(i=0;i<STEP;++i)
   lm+=cost[mstep[m][i]][i] ;

  /*��θ� ��ĥ*/
  for(i=0;i<STEP;++i)
   pheromone[mstep[m][i]][i]+=Q*(1.0/lm) ;
  sum_lm+=lm ;
 }
 /*���̰� ���� ��� �Ÿ��� ���*/
 printf("%lf\n",sum_lm/NOA) ;
}

/**************************/
/*    walk() �Լ�         */
/*    ���̸� �Ȱ� ��      */
/**************************/
void walk(int cost[2][STEP]
,double pheromone[2][STEP],int mstep[NOA][STEP])
{
 int m ;/*������ ��ü ��ȣ*/
 int s ;/*������ ���� �ܰ� ��ġ*/

 for(m=0;m<NOA;++m){
  for(s=0;s<STEP;++s){
   /*��-greedy���� �̿��� �ൿ ����*/
   if((rand1()<EPSILON)
    ||(abs(pheromone[0][s]-pheromone[1][s])<1e-9))
   {/*������ �ൿ*/
    mstep[m][s]=rand01() ;
   }
   else{/*��θ� �󵵿� ���� ����*/
    if(pheromone[0][s]>pheromone[1][s]) 
      mstep[m][s]=0 ;
    else
      mstep[m][s]=1 ;
   }
 }
 }
 /*������ �ൿ ���*/
 printmstep(mstep) ;
}

/**************************/
/*  printmstep() �Լ�      */
/*   ������ �ൿ ǥ��       */
/**************************/
void printmstep(int mstep[NOA][STEP])
{
 int i,j ;

 printf("*mstep\n") ;
 for(i=0;i<NOA;++i){
  for(j=0;j<STEP;++j)
   printf("%d ",mstep[i][j]) ;
  printf("\n") ;
 }
}

/**************************/
/*    printp() �Լ�       */
/*   ��θ� ǥ��          */
/**************************/
void printp(double pheromone[2][STEP]) 
{
 int i,j ;

 for(i=0;i<2;++i){
  for(j=0;j<STEP;++j)
   printf("%4.2lf ",pheromone[i][j]) ;
  printf("\n") ;
 }
}

/****************************************/
/*    rand1() �Լ�                      */
/*0��1������ �Ǽ��� ��ȯ�ϴ� ���� �Լ�  */
/****************************************/
double rand1()
{
 /*������ ���*/
 return (double)rand()/RAND_MAX ;
}

/*************************************/
/*     rand01() �Լ�                 */
/*��   0 �Ǵ� 1�� ��ȯ�ϴ� ���� �Լ� */
/*************************************/
int rand01()
{
 int rnd ;
 
 /*������ �ִ� ����*/
 while((rnd=rand())==RAND_MAX) ;
 /*������ ���*/ 
 return (int)((double)rnd/RAND_MAX*2) ;
}