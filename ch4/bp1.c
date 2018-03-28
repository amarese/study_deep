/*********************************************************/
/*                      bp1.c                            */
/* �������۰��̼��� �̿��� �Ű�� �н�                   */
/* ��� ���                                             */
/*  \Users\deeplearning\ch4>bp1 < data.txt > result.txt  */
/* ������ ���̳� �н������ �Ǵ� ���� ��� ���� ���     */
/*********************************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*��ȣ ��� ����*/
#define INPUTNO 3  /*�Է��� �� ����*/ 
#define HIDDENNO 3  /*�߰��� �� ����*/ 
#define ALPHA  10  /*�н� ���*/ 
#define SEED 65535    /*���� �õ�*/ 
#define MAXINPUTNO 100    /*�н� �������� �ִ� ����*/ 
#define BIGNUM 100    /*������ �ʱ갪*/ 
#define LIMIT 0.001    /*������ �ʱ갪*/ 

/*�Լ� ������Ÿ�� ����*/
double f(double u) ; /*��ȯ �Լ�(�ñ׸��̵� �Լ�)*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
								/*�߰��� ����ġ���ʱ�ȭ*/
void initwo(double wo[HIDDENNO+1]) ;/*����� ����ġ�� �ʱ�ȭ*/
double drnd(void) ;/* ���� ����     */
void print(double wh[HIDDENNO][INPUTNO+1]
	,double wo[HIDDENNO+1]) ; /*��� ���*/
double forward(double wh[HIDDENNO][INPUTNO+1]
	,double wo[HIDDENNO+1],double hi[]
	,double e[INPUTNO+1]) ; /*������ ���*/
void olearn(double wo[HIDDENNO+1],double hi[]
	,double e[INPUTNO+1],double o) ; /*����� ����ġ�� ����*/
int getdata(double e[][INPUTNO+1]) ; /*�н� ������ �о���̱�*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
	,double wo[HIDDENNO+1],double hi[]
	,double e[INPUTNO+1],double o) ; /*�߰��� ����ġ�� ����*/

/*******************/ 
/*    main() �Լ�  */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*�߰��� ����ġ*/
 double wo[HIDDENNO+1] ;/*����� ����ġ*/
 double e[MAXINPUTNO][INPUTNO+1] ;/*�н� ������ ��Ʈ*/
 double hi[HIDDENNO+1] ;/*�߰��� ���*/
 double o ;/*���*/
 double err=BIGNUM ;/*���� ��*/
 int i,j ;/*�ݺ� ����*/
 int n_of_e ;/*�н� ������ ����*/
 int count=0 ;/*�ݺ� Ƚ�� ī����*/

 /*���� �ʱ�ȭ*/
 srand(SEED) ;

 /*����ġ �ʱ�ȭ*/
 initwh(wh) ;/*�߰��� ����ġ�� �ʱ�ȭ*/
 initwo(wo) ;/*����� ����ġ�� �ʱ�ȭ*/
 print(wh,wo) ; /*��� ���*/

 /*�н� ������ �о���̱�*/
 n_of_e=getdata(e) ;
 printf("�н� ������ ����:%d\n",n_of_e) ;

 /*�н�*/
 while(err>LIMIT){
  err=0.0 ;
  for(j=0;j<n_of_e;++j){
   /*������ ���*/
   o=forward(wh,wo,hi,e[j]) ;
   /*����� ����ġ�� ����*/
   olearn(wo,hi,e[j],o) ;
   /*�߰��� ����ġ�� ����*/
   hlearn(wh,wo,hi,e[j],o) ;
   /*���� ���*/
   err+=(o-e[j][INPUTNO])*(o-e[j][INPUTNO]) ;
  }
  ++count ;
  /*���� ���*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*�н� ����*/

 /*���� ���� ���*/
 print(wh,wo) ; 

 /*�н� �����Ϳ� ���� ���*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**************************/
/*  hlearn() �Լ�         */
/*  �߰��� ����ġ�� �н�  */
/**************************/
void hlearn(double wh[HIDDENNO][INPUTNO+1],
	double wo[HIDDENNO+1],
	double hi[],double e[INPUTNO+1],double o)
{
 int i,j ;/*�ݺ� ����*/
 double dj ;/*�߰��� ����ġ ��꿡 �̿�*/

 for(j=0;j<HIDDENNO;++j){/*�߰��� �� �� j�� �������*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*i��° ����ġ ó��*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*��ġ �н�*/
 }
}

/*************************/
/*  getdata() �Լ�       */
/* �н� ������ �о���̱�*/
/*************************/
int getdata(double e[][INPUTNO+1])
{
 int n_of_e=0 ;/*������ ��Ʈ ����*/
 int j=0 ;/*�ݺ� �����*/

 /*������ �Է�*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>INPUTNO){/*���� �ε�����*/
   j=0 ;
   ++n_of_e ;
  }
 }
 return n_of_e ;
}

/*************************/
/* olearn() �Լ�         */
/* ������� ����ġ �н�  */
/*************************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i ;/*�ݺ� ����*/
 double d ;/*����ġ ��꿡 �̿�*/

 d=(e[INPUTNO]-o)*o*(1-o) ;/*���� ���*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*����ġ �н�*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*��ġ �н�*/
} 

/**********************/
/*  forward() �Լ�    */
/*  ������ ���       */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1],
	double wo[HIDDENNO+1],double hi[],
	double e[INPUTNO+1])
{
 int i,j ;/*�ݺ� ����*/
 double u ;/*����ġ�� ������ �� ���*/
 double o ;/*��� ���*/

 /*hi ���*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*����ġ�� ������ �� ���ϱ�*/
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

/**********************/
/*   print() �Լ�     */
/*   ��� ���        */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*�ݺ� ����*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/************************/
/*    initwh() �Լ�     */
/*�߰��� ����ġ�� �ʱ�ȭ*/
/************************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;/*�ݺ� ����*/

 /*������ �̿��� ����ġ ����*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/************************/
/*    initwo() �Լ�     */
/*����� ����ġ�� �ʱ�ȭ*/
/************************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*�ݺ� ����*/

 /*������ �̿��� ����ġ ����*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd() �Լ�     */
/* ���� ����       */
/*******************/
double drnd(void)
{
 double rndno ;/*������ ����*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*-1���� 1 ������ ���� ����*/
 return rndno; 
}

/*******************/
/* f() �Լ�        */
/* ��ȯ �Լ�       */
/*(�ñ׸��̵� �Լ�)*/
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}