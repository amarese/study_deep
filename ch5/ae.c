/*********************************************************/
/*                      ae.c                             */
/* �ڵ���ȣȭ��                                          */
/* ��� ���                                             */
/* \Users\deeplearning\ch5>ae < data.txt                 */
/* ������ ���̳� �н� ����� �Ǵ� ���� ��� ���� ���    */
/*********************************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*��ȣ ��� ����*/
#define INPUTNO 9		/*�Է��� �� ����*/ 
#define HIDDENNO 2		/*�߰��� �� ����*/ 
#define OUTPUTNO 9		/*����� �� ����*/
#define ALPHA  10		/*�н� ���*/ 
#define SEED 65535		/*���� �õ�*/ 
#define MAXINPUTNO 100	/*�н� �������� �ִ� ����*/ 
#define BIGNUM 100		/*������ �ʱ갪*/ 
#define LIMIT 0.0001	/*������ ���Ѱ�*/ 

/*�Լ� ������Ÿ�� ����*/
double f(double u) ;	/*��ȯ �Լ�(�ñ׸��̵� �Լ�)*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*�߰��� ����ġ �ʱ�ȭ*/
void initwo(double wo[HIDDENNO+1]) ;	/*����� ����ġ �ʱ�ȭ*/
double drnd(void) ;	/* ������ ����     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ;	/*��� ���*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ;	/*������ ���*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ;	/*����� ����ġ ����*/
int getdata(double e[][INPUTNO+OUTPUTNO]) ;	/*�н� ������ �о���̱�*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ;	/*�߰��� ����ġ ����*/

/*******************/ 
/*    main() �Լ�  */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;	/*�߰��� ����ġ*/
 double wo[OUTPUTNO][HIDDENNO+1] ;	/*����� ����ġ*/
 double e[MAXINPUTNO][INPUTNO+OUTPUTNO] ;	/*�н� ������ ��Ʈ*/
 double hi[HIDDENNO+1] ;	/*�߰��� ���*/
 double o[OUTPUTNO] ;	/*���*/
 double err=BIGNUM ;	/*���� ��*/
 int i,j,k ;	/*�ݺ� ����*/
 int n_of_e ;	/*�н� ������ ����*/
 int count=0 ;	/*�ݺ� Ƚ�� ī����*/

 /*���� �ʱ�ȭ*/
 srand(SEED) ;

 /*����ġ �ʱ�ȭ*/
 initwh(wh) ;	/*�߰��� ����ġ �ʱ�ȭ*/
 for(i=0;i<OUTPUTNO;++i)
  initwo(wo[i]) ;	/*����� ����ġ �ʱ�ȭ*/
 print(wh,wo) ;	/*��� ���*/

 /*�н� ������ �о���̱�*/
 n_of_e=getdata(e) ;
 printf("�н� ������ ����:%d\n",n_of_e) ;

 /*�н�*/
 while(err>LIMIT){
  /*���� ���� ������� ����*/
  for(k=0;k<OUTPUTNO;++k){
   err=0.0 ;
   for(j=0;j<n_of_e;++j){
    /*������ ���*/
    o[k]=forward(wh,wo[k],hi,e[j]) ;
    /*����� ����ġ ����*/
    olearn(wo[k],hi,e[j],o[k],k) ;
    /*�߰��� ����ġ ����*/
    hlearn(wh,wo[k],hi,e[j],o[k],k) ;
    /*���� ���*/
    err+=(o[k]-e[j][INPUTNO+k])*(o[k]-e[j][INPUTNO+k]) ;
   }
   ++count ;
   /*���� ���*/
   fprintf(stderr,"%d\t%lf\n",count,err) ;
   /*���� ���� ����� ���� �κ� ����*/
  }
 }/*�н� ����*/

 /*���� ���� ���*/
 print(wh,wo) ; 

 /*�н� �����Ϳ� ���� ���*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+OUTPUTNO;++j)
   printf("%.3lf ",e[i][j]) ;
  printf("\t") ;
  for(j=0;j<OUTPUTNO;++j)
   printf("%.3lf ",forward(wh,wo[j],hi,e[i])) ;
  printf("\n") ;
 }

 return 0 ;
}

/************************/
/*  hlearn() �Լ�       */
/*  �߰��� ����ġ �н�  */
/************************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[],double o,int k)
{
 int i,j ;	/*�ݺ� ����*/
 double dj ;	/*�߰��� ����ġ ��꿡 �̿�*/

 for(j=0;j<HIDDENNO;++j){/*�߰����� �� �� j�� �������*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO+k]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*i��°�� ����ġ�� ó��*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;	/*��ġ �н�*/
 }
}

/************************/
/*  getdata() �Լ�      */
/*�н� ������ �о���̱�*/
/************************/
int getdata(double e[][INPUTNO+OUTPUTNO])
{
 int n_of_e=0 ;	/*������ ��Ʈ ����*/
 int j=0 ;	/*�ݺ� �����*/

 /*������ �Է�*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO+OUTPUTNO){/*���� ������*/
   j=0 ;
   ++n_of_e ;
  }
 }

 return n_of_e ;
}

/************************/
/*  olearn() �Լ�       */
/*  ����� ����ġ �н�  */
/************************/
void olearn(double wo[HIDDENNO+1]
		,double hi[],double e[INPUTNO+1],double o,int k)
{
 int i ;	/*�ݺ� ����*/
 double d ;	/*����ġ ��꿡 �̿�*/

 d=(e[INPUTNO+k]-o)*o*(1-o) ;	/*���� ���*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;	/*����ġ �н�*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;	/*��ġ �н�*/
} 

/**********************/
/*  forward() �Լ�    */
/*  ������ ���       */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO+1])
{
 int i,j ;	/*�ݺ� ����*/
 double u ;	/*����ġ ���� �� ���*/
 double o ;	/*��� ���*/

 /*hi ���*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;	/*����ġ ���� ���� ����*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;	/*��ġ ó��*/
  hi[i]=f(u) ;
 }
 /*��� o ���*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;	/*��ġ ó��*/
 
 return f(o) ;
} 

/**********************/
/*   print() �Լ�     */
/*   ��� ���        */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;	/*�ݺ� ����*/

 for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1;++j)
   printf("%.3lf ",wh[i][j]) ;
  printf("\n") ;
 } 
 printf("\n") ;
 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   printf("%.3lf ",wo[i][j]) ;
  printf("\n") ;
 }
 printf("\n") ;
} 

/**********************/
/*    initwo() �Լ�   */
/*�߰��� ����ġ �ʱ�ȭ*/
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;	/*�ݺ� ����*/

 /*������ �̿��� ����ġ ����*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo() �Լ�   */
/*����� ����ġ �ʱ�ȭ*/
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;	/*�ݺ� ����*/

 /*������ �̿��� ����ġ ����*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd() �Լ�     */
/* ������ ����     */
/*******************/
double drnd(void)
{
 double rndno ;	/*������ ����*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;	/*-1���� 1 ������ ���� ����*/
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
