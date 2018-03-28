/*****************************************************/
/*                  kpga.c����                       */
/* GA�� �̿��� �賶 ���� �ذ� ���α׷�               */
/* GA�� �̿��Ͽ� �賶 ������ ���� ���� �ش��� Ž��   */
/* ��� ���                                         */
/*\Users\deeplearning\ch3>kpga < data.txt            */
/*****************************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*��ȣ ��� ����*/
#define MAXVALUE 100 /* ���Կ� ��ġ�� �ִ�*/
#define N 30 /*���ΰ���*/
#define WEIGHTLIMIT (N*MAXVALUE/4) /*���� ����*/
#define POOLSIZE 30 /*Ǯ ũ��*/
#define LASTG 50    /*�� ����*/
#define MRATE 0.01  /*���������� Ȯ��*/
#define SEED 32767    /*���� �õ�*/
#define YES 1   /*yes�� �ش��ϴ� ����*/
#define NO 0    /*no�� �ش��ϴ� ����/

/*�Լ� ������Ÿ�� ����*/
void initparcel();/*�� �ʱ�ȭ*/
int evalfit(int gene[]) ; /*������ ���*/
void mating(int pool[POOLSIZE][N]
            ,int ngpool[POOLSIZE*2][N]) ; /*����*/
void mutation(int ngpool[POOLSIZE*2][N]) ; /*��������*/
void printp(int pool[POOLSIZE][N]) ; /*��� ���*/
void initpool(int pool[POOLSIZE][N]) ; /*�ʱ� ���� ����*/
int rndn() ; /*n�̸��� ���� ����  */
int notval(int v) ;/*������ ����*/
int selectp(int roulette[POOLSIZE],int totalfitness) ;
                    /*�θ� ����*/
void crossing(int m[],int p[],int c1[],int c2[]) ;
                /* Ư�� ����ü 2���� ���� */
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) ;/*���� ���� ����*/

/*���� ����(�� ������)*/
 int parcel[N][2] ;/*��*/

/*******************/
/*   main() �Լ�   */
/*******************/
int main(int argc,char *argv[])
{
 int pool[POOLSIZE][N] ; /*����ü Ǯ*/
 int ngpool[POOLSIZE*2][N] ; /*���� ���� ����ü Ǯ*/
 int generation;/* ���� ���� �� */
 
 /*���� �ʱ�ȭ*/
 srand(SEED) ;

 /*�� �ʱ�ȭ*/
 initparcel() ;
 
 /*�ʱ� ���� ����*/
 initpool(pool) ;
 
 /*�� ������� �ݺ�*/
 for(generation=0;generation<LASTG;++generation){
  printf("%d����\n",generation) ;
  mating(pool,ngpool) ;/*����*/
  mutation(ngpool) ;/*��������*/
  selectng(ngpool,pool) ;/*���� ���� ����*/
  printp(pool) ;/*��� ���*/
 }

 return 0 ;
}

/****************************/
/*      initparcel() �Լ�   */
/*       �� �ʱ�ȭ          */
/****************************/
void initparcel()
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])
                 !=EOF)){
  ++i ;
 }
}

/************************/
/*   selectng() �Լ�    */
/*   ���� ���� ����     */
/************************/
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) 
{
 int i,j,c ;/* �ݺ� ���� ���� */
 int totalfitness=0 ;/*������ �հ�*/
 int roulette[POOLSIZE*2] ;/*������ ����*/
 int ball ;/* ��(���� ��ġ�� ��ġ)*/
 int acc=0 ;/*������ ��� ��*/
 
 /*������ �ݺ�*/
 for(i=0;i<POOLSIZE;++i){
  /* �귿 �ۼ� */
  totalfitness=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   roulette[c]=evalfit(ngpool[c]) ;
   /* ������ �հ� ���*/
   totalfitness+=roulette[c] ;
  }
  /*����ü �ϳ��� ����*/
  ball=rndn(totalfitness) ;
  acc=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   acc+=roulette[c] ;/*������ ���ϱ�*/
   if(acc>ball) break ;/*�ش��ϴ� ������*/
  }

  /*����ü ����*/
  for(j=0;j<N;++j){
   pool[i][j]=ngpool[c][j] ;
  }
 }
}

/************************/
/*   selectp() �Լ�     */
/*   �θ� ����          */
/************************/
int selectp(int roulette[POOLSIZE],int totalfitness)
{
 int i ;/* �ݺ� ���� ���� */
 int ball ;/* ��(���� ��ġ�� ��ġ)*/
 int acc=0 ;/*������ ��� ��*/

 ball=rndn(totalfitness) ;
 for(i=0;i<POOLSIZE;++i){
  acc+=roulette[i] ;/*������ ���ϱ�*/
  if(acc>ball) break ;/*�ش��ϴ� ������*/
 }
 return i ;
}

/************************/
/*   mating() �Լ�      */
/*        ����          */
/************************/
void mating(int pool[POOLSIZE][N]
           ,int ngpool[POOLSIZE*2][N])
{
 int i ;/* �ݺ� ���� ���� */
 int totalfitness=0 ;/*������ �հ�*/
 int roulette[POOLSIZE] ;/*������ ����*/
 int mama,papa ;/*�θ� ������ ��ȣ*/

 /* �귿 �ۼ�*/
 for(i=0;i<POOLSIZE;++i){
  roulette[i]=evalfit(pool[i]) ;
  /* ������ �հ���*/
  totalfitness+=roulette[i] ;
 }

 /*���ð� ������ �ݺ�*/
 for(i=0;i<POOLSIZE;++i){
  do{/*�θ� ����*/
   mama=selectp(roulette,totalfitness) ;
   papa=selectp(roulette,totalfitness) ;
  }while(mama==papa) ;/*���ܪ����*/

  /*Ư�� ������ 2���� ����*/
  crossing(pool[mama],pool[papa]
            ,ngpool[i*2],ngpool[i*2+1])  ;  
 }
}

/**************************/
/*  crossing() �Լ�       */
/* Ư�� ����ü 2���� ���� */
/**************************/
void crossing(int m[],int p[],int c1[],int c2[])
{
 int j ;/* �ݺ� ���� ���� */
 int cp ;/*�����ϴ� ��*/

 /*������ ����*/
 cp =rndn(N) ;

 /*�պκ� ����*/
 for(j=0;j<cp;++j){
  c1[j]=m[j] ;
  c2[j]=p[j] ;
 }
 /*�޺κ� ����*/
 for(;j<N;++j){
  c2[j]=m[j] ;
  c1[j]=p[j] ;
 }
}

/************************/
/*   evalfit() �Լ�     */
/*   ������ ���        */
/************************/
int evalfit(int g[])
{
 int pos ;/*������ ��ġ ����*/
 int value=0 ;/*�򰫰�*/
 int weight=0 ;/*�߷�*/

 /*�� ������ ��ġ�� �����Ͽ� �߷��� �򰫰��� ���*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*g[pos] ;
  value+=parcel[pos][1]*g[pos] ;
 }
 /*���� ������ ó��*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
}

/***********************/
/*   printp() �Լ�     */
/*   ��� ���         */
/***********************/
void printp(int pool[POOLSIZE][N])
{
 int i,j ;/* �ݺ� ���� ���� */
 int fitness ;/* ������ */
 double totalfitness=0 ;/* ������ �հ� */
 int elite,bestfit=0 ;/*����Ʈ ������ ó���� ����*/

 for(i=0;i<POOLSIZE;++i){
  for(j=0;j<N;++j)
   printf("%1d",pool[i][j]) ;
  fitness=evalfit(pool[i]) ;
  printf("\t%d\n",fitness) ;
  if(fitness>bestfit){/*����Ʈ ����*/
   bestfit=fitness ;
   elite=i ;
  }
  totalfitness+=fitness ;
 }
 /*����Ʈ ������ ������ ���*/
 printf("%d\t%d \t",elite,bestfit) ;
 /*��� ������ ���*/
 printf("%lf\n",totalfitness/POOLSIZE) ;
}

/***********************/
/*   initpool() �Լ�   */
/*   �ʱ� ���� ����    */
/***********************/
void initpool(int pool[POOLSIZE][N])
{
 int i,j ;/* �ݺ� ���� ���� */

 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<N;++j)
   pool[i][j]=rndn(2) ;
}

/************************/
/*   rndn() �Լ�        */
/*   n �̸��� ���� ���� */
/************************/
int rndn(int l)
{
 int rndno ;/*������ ����*/

 while((rndno=((double)rand()/RAND_MAX)*l)==l) ;

 return rndno;
}

/***********************/
/*   mutation() �Լ�    */
/*   ��������          */
/***********************/
void mutation(int ngpool[POOLSIZE*2][N])
{
 int i,j ;/* �ݺ� ���� ���� */

 for(i=0;i<POOLSIZE*2;++i)
  for(j=0;j<N;++j)
   if((double)rndn(100)/100.0<=MRATE)
    /*���� ��������*/
    ngpool[i][j]=notval(ngpool[i][j]) ;
}

/************************/
/*   notval() �Լ�      */
/*   ������ ����        */
/************************/
int notval(int v)
{
 if(v==YES) return NO ;
 else return YES ;
}