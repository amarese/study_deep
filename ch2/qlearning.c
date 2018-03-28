/********************************************/
/*         qlearning.c                      */
/*   ��ȭ�н�(Q �н�) ���� ���α׷�         */
/*   �̷� Ž���� �н��մϴ�.                */
/*   ��� ���                              */
/*    C:\Users\deeplearning\ch2>qlearning   */
/********************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>

/* ��ȣ ����� ����             */
#define GENMAX  1000	/*�н� �ݺ� Ƚ��*/
#define NODENO  15		/*�� ���� ��� */
#define ALPHA 0.1		/*�н� ���*/
#define GAMMA 0.9		/* ������*/
#define EPSILON 0.3		/*�ൿ ������ �������� ���� */
#define SEED 32767		/*���� �õ�*/

/* �Լ� ���α׷� ����  */
int rand100() ;		/*0��100�� ��ȯ�ϴ� ���� �Լ�*/
int rand01() ;		/*0 �Ǵ� 1�� ��ȯ�ϴ� ���� �Լ�*/
double rand1() ;	/*0��1 ������ �Ǽ��� ��ȯ�ϴ� ���� �Լ�*/
void printqvalue(int qvalue[NODENO]);	/*Q �� ���*/
int selecta(int s,int qvalue[NODENO]);	/*�ൿ ����*/
int updateq(int s,int qvalue[NODENO]);	/*Q �� ����*/

/*****************/
/*  main() �Լ�  */
/*****************/
int main()
{
 int i;
 int s;/*����*/
 int t;/*�ð�*/
 int qvalue[NODENO];/*Q ��*/

 srand(SEED);/*���� �ʱ�ȭ*/

 /*�� �� �ʱ�ȭ*/
 for(i=0;i<NODENO;++i)
  qvalue[i]=rand100() ;
 printqvalue(qvalue) ;

 /*���� �н�*/
 for(i=0;i<GENMAX;++i){
  s=0;/*�ൿ �ʱ� ����*/
  for(t=0;t<3;++t){/*���� �Ʒ��ܱ��� �ݺ�*/
   /*�ൿ ����*/
   s=selecta(s,qvalue) ;
   
   /*Q �� ����*/
   qvalue[s]=updateq(s,qvalue) ;
  }
  /*Q �� ���*/
  printqvalue(qvalue) ;
 }
 return 0;
}

/****************************/
/*       updateq() �Լ�     */
/*       Q �� ����          */
/****************************/
int updateq(int s,int qvalue[NODENO])
{
 int qv ;/*���ŵǴ� Q ��*/
 int qmax ;/*�� ���� �ִ�*/
 
 /*���� �Ʒ����� ��*/
 if(s>6){
  if(s==14)/*���� �ο�*/
   qv=qvalue[s]+ALPHA*(1000-qvalue[s]) ;
  /*������ �ִ� ��� ����   */
  /*�ٸ� ��带 �߰��� ���� */
  /*���� 2���� �ּ��� ����  */
//  else if(s==11)/*���� �ο�*/
//   qv=qvalue[s]+ALPHA*(500-qvalue[s]) ;
  else/*���� ����*/
   qv=qvalue[s] ;
 }
 /*���� �Ʒ��� �̿�*/
 else{
  if((qvalue[2*s+1])>(qvalue[2*s+2])) 
   qmax=qvalue[2*s+1];
  else qmax=qvalue[2*s+2];
  qv=qvalue[s]+ALPHA*(GAMMA*qmax-qvalue[s]) ;
 }

 return qv ;
}

/****************************/
/*        selecta() �Լ�    */
/*        �ൿ ����         */
/****************************/
int selecta(int olds,int qvalue[NODENO])
{
 int s ;
 
 /*��-greedy ���� �̿��� �ൿ ����*/
 if(rand1()<EPSILON){
  /*�������� �ൿ*/
  if(rand01()==0) s=2*olds+1 ;
  else s=2*olds+2 ;
 }
 else{
  /*�� �� �ִ��� ����*/
  if((qvalue[2*olds+1])>(qvalue[2*olds+2])) 
   s=2*olds+1;
  else s=2*olds+2;
 }

 return s ;
}

/****************************/
/*    printqvalue()�Լ�     */
/*    Q �� ���             */
/****************************/
void printqvalue(int qvalue[NODENO])
{
 int i ;
 
 for (i=1;i<NODENO;++i)
  printf("%d\t",qvalue[i]);

 printf("\n");
}

/***********************************/
/*     rand1() �Լ�                */
/*0��1 ������ �Ǽ� ��ȯ ���� �Լ�  */
/***********************************/
double rand1()
{
 /*���� ���*/ 
 return (double)rand()/RAND_MAX ;
}

/***********************************/
/*     rand01() �Լ�               */
/*   0 �Ǵ� 1�� ��ȯ�ϴ� ���� �Լ� */
/***********************************/
int rand01()
{
 int rnd ;
 
 /*���� �ִ��� ����*/
 while((rnd=rand())==RAND_MAX) ;
 /*���� ���*/ 
 return (int)((double)rnd/RAND_MAX*2) ;
}

/**********************************/
/*     rand100() �Լ�             */
/*   0��100�� ��ȯ�ϴ� ���� �Լ�  */
/**********************************/
int rand100()
{
 int rnd ;
 
 /*���� �ִ� ����*/
 while((rnd=rand())==RAND_MAX) ;
 /*���� ���*/ 
 return (int)((double)rnd/RAND_MAX*101) ;
}