/*****************************************/
/*              direct.c                 */
/*����Ž������ �賶 ���� Ǯ��            */
/*��� ���                              */
/*\Users\deeplearning\ch3>direct<data.txt*/
/*****************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/*��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>

/*   ��ȣ ��� ����                 */
#define MAXVALUE 100 /*���Կ� ��ġ�� �ִ�*/
#define N 30 /*�� ����*/
#define WEIGHTLIMIT (N*MAXVALUE/10) 
			/*���� ����*/
#define SEED 32768 /*���� �õ�*/

/*   �Լ� ������Ÿ�� ����      */
void initparcel(int parcel [N][2]);/*�� �ʱ�ȭ*/
void prints(int solution);/*���� �ĺ� ���*/
int solve(int parcel [N][2]) ;/*Ž��*/
int pow2n(int n);/*2�� ���*/
int calcval(int parcel[N][2],int i);/*�򰫰� ���*/

/****************/
/*  main() �Լ� */
/****************/
int main()
{
 int parcel[N][2] ;/*��*/
 int solution=0xfff ;/*����*/

 /*�� �ʱ�ȭ*/
 initparcel(parcel) ;
 /*Ž��*/
 solution=solve(parcel) ;
 /*���� ���*/
 prints(solution) ;
 return 0 ;
}

/****************************/
/*       solve() �Լ�       */
/*       Ž��               */
/****************************/
int solve(int parcel [N][2])
{
 int i ;/*�ݺ� ����*/
 int limit ;/*Ž�� ����*/
 int maxvalue=0 ;/*�򰫰��� �ִ�*/
 int value ;/*�򰪰�*/
 int solution ;/*���� �ĺ�*/

 /*Ž�� ���� ����*/
 limit=pow2n(N) ;
 /*���� Ž��*/
 for(i=0;i<limit;++i){
  /*�򰫰� ���*/
  value=calcval(parcel,i) ;
  /*�ִ� ����*/
  if(value>maxvalue){
   maxvalue=value ;
   solution=i ;
   printf("*** maxvalue %d\n",maxvalue) ;
  }
 }
 return solution ;
}

/****************************/
/*       calcval() �Լ�     */
/*       �򰫰��� ���      */
/****************************/
int calcval(int parcel[N][2],int i)
{
 int pos ;/*������ ��ġ ����*/
 int value=0 ;/*�򰫰�*/
 int weight=0 ;/*�߷�*/

 /*�� ������ ��ġ�� �����Ͽ� �߷��� �򰫰��� ���*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*((i>>pos)&0x1) ;
  value+=parcel[pos][1]*((i>>pos)&0x1) ;
 }
 /*���� ������ ó��*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
}

/****************************/
/*       pow2n() �Լ�       */
/*       2�� ���           */
/****************************/
int pow2n(int n)
{
 int pow=1 ;
 for(;n>0;--n)
  pow*=2 ;
 return pow ;
}

/****************************/
/*     prints() �Լ�        */
/*     ���� �ĺ� ���       */
/****************************/
void prints(int solution)
{
 int i ;
 for(i=0;i<N;++i)
  printf("%1d ",(solution>>i)&0x1) ;
 printf("\n") ;
}

/****************************/
/*     initparcel() �Լ�    */
/*     �� �ʱ�ȭ            */
/****************************/
void initparcel(int parcel [N][2])
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])!=EOF)){
  ++i ;
 }
}
