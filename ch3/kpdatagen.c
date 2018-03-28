/********************************************/
/*              kpdatagen.c                 */
/* �賶 ���� ������ ������                  */
/* ���� �߷��� ��ġ�� ������ ����           */
/* ��� ���                                */
/*\Users\deeplearning\ch3>kpdatagen>data.txt*/
/********************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/*��� ���� ����*/
#include <stdio.h>
#include <stdlib.h>

/*   ��ȣ ��� ����                 */
#define MAXVALUE 100 /*���Կ� ��ġ�� �ִ�*/
#define N 30 /*�� ����*/
#define SEED 32768 /*���� �õ�*/

/*   �Լ� ������Ÿ�� ����      */
int randdata() ; /*MAXVALUE ������ ������ ��ȯ�ϴ� ���� �Լ�*/

/****************/
/*  main() �Լ� */
/****************/
int main()
{
 int i ;

 srand(SEED) ;
 for(i=0;i<N;++i)
  printf("%ld %ld\n",randdata(),randdata()) ;
 return 0 ;
}

/*********************************************/
/*     randdata() �Լ�                       */
/*MAXVALUE ������ ������ ��ȯ�ϴ� ���� �Լ�  */
/*********************************************/
int randdata()
{
 int rnd ;
 
 /*������ �ִ� ����*/
 while((rnd=rand())==RAND_MAX) ;
 /*������ ���*/ 
 return (int)((double)rnd/RAND_MAX*MAXVALUE+1) ;
}
