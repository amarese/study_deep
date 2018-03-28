/*********************************************************/
/*                   nn.c                                */
/* �ܼ��� ������ �Ű�� ���                             */
/* �� ��� ���� ���(�н� ����)                          */
/* ��� ���                                             */
/*  \Users\deeplearning\ch4>nn < data.txt                */
/*********************************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*��ȣ ��� ����*/
#define INPUTNO 2  /*�Է����� �� ����*/ 
#define HIDDENNO 2  /*�߰����� �� ����*/ 
#define MAXINPUTNO 100    /*������ �ִ� ����*/ 

/*�Լ� ������Ÿ�� ����*/
double f(double u) ; /*��ȯ �Լ�*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*�߰����� ����ġ �ʱ�ȭ*/
void initwo(double wo[HIDDENNO+1]) ;/*������� ����ġ �ʱ�ȭ*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO]) ; /*������ ���*/
int getdata(double e[][INPUTNO]) ;/*������ �о���̱�*/ 

/*******************/ 
/*    main() �Լ�  */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*�߰����� ����ġ*/
 double wo[HIDDENNO+1] ;/*������� ����ġ*/
 double e[MAXINPUTNO][INPUTNO] ;/*������ ��Ʈ*/
 double hi[HIDDENNO+1] ;/*�߰��� ���*/
 double o ;/*���*/
 int i,j ;/*�ݺ� ����*/
 int n_of_e ;/*������ ����*/
 
 /*����ġ �ʱ�ȭ*/
 initwh(wh) ;
 initwo(wo) ;

 /*�Է� ������ �о���̱�*/
 n_of_e=getdata(e) ;
 printf("������ ����:%d\n",n_of_e) ;
 
 /*��� ��ü*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/************************/
/*  getdata() �Լ�      */
/*�н� ������ �о���̱�*/
/************************/
int getdata(double e[][INPUTNO])
{
 int n_of_e=0 ;/*������ ��Ʈ ����*/
 int j=0 ;/*�ݺ� �����*/

 /*������ �Է�*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO){/*���� ������*/
   j=0 ;
   ++n_of_e ;
  }
 }
 return n_of_e ;
}

/**********************/
/*  forward() �Լ�    */
/*  ������ ���       */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1],
	double wo[HIDDENNO+1],double hi[],
	double e[INPUTNO])
{
 int i,j ;/*�ݺ� ����*/
 double u ;/*����ġ�� ������ ���� ����*/
 double o ;/*��� ���*/

 /*hi ���*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*����ġ�� ������ ���� ����*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*��ġ ó��*/
  hi[i]=f(u) ;
 }
 /*��� o ���*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*��ġ ó��*/
 
 return f(o) ;
} 

//***********************/
/*    initwh() �Լ�     */
/*�߰����� ����ġ �ʱ�ȭ*/
/************************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 
 /*������ ����μ� �ο�*/
 wh[0][0]=-2 ;
 wh[0][1]=3 ;
 wh[0][2]=-1 ;
 wh[1][0]=-2 ;
 wh[1][1]=1 ;
 wh[1][2]=0.5 ;
} 

/************************/
/*    initwo() �Լ�     */
/*������� ����ġ �ʱ�ȭ*/
/************************/
void initwo(double wo[HIDDENNO+1])
{
 /*������ ����μ� �ο�*/
 wo[0]=-60 ;
 wo[1]=94 ;
 wo[2]=-1 ;
} 

/*******************/
/* f() �Լ�         */
/* ��ȯ �Լ�        */
/*******************/
double f(double u)
{
 /*��� �Լ� ���*/
 if(u>=0) return 1.0 ;
 else return 0.0 ;
 
 /*�ñ׸��̵� �Լ� ���*/
// return 1.0/(1.0+exp(-u)) ;
}