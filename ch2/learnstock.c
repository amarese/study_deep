/********************************************/
/*         learnstock.c                     */
/*  �ܼ��� �ͳ��н� ���� ���α׷�        */
/*            ���� �н���                */
/* 100���� �н� �����͸� �о�鿩            */
/* ������ 10�ڸ��� 2���� ������ ����  */
/* ��� ���                                    */
/*:\Users\deeplearning\ch2>learnstock < ldata.txt */
/********************************************/

/*Visual Studio���� ȣȯ�� Ȯ�� */
#define _CRT_SECURE_NO_WARNINGS

/* ��� ���� ���� */
#include <stdio.h>
#include <stdlib.h>

/* ��ȣ ��� ����             */
#define OK 1 
#define NG 0
#define SETSIZE 100 /* �н� ������ ��Ʈ�� ũ�� */
#define CNO 10 /* �н� �������� �ڸ���(10ȸ�� ��) */
#define GENMAX  10000 /* �ش� �ĺ� ���� Ƚ�� */
#define SEED 32767 /* ���� �õ� */

/* �Լ� ������Ÿ�� ����  */
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE]) ;
           /* �н� ������ ��Ʈ�� �о���� */
int rand012() ;/*0, 1 �Ǵ� 2�� ��ȯ�ϴ� ���� �Լ� */
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO]) ;
           /* �ش� �ĺ� ������ ����(0~SETSIZE��)�� ��� */

/****************/
/*  main() �Լ�  */
/****************/
int main()
{
 int i, j;
 int score = 0;/* ����(0��SETSIZE��)*/
 int answer[CNO];/* �ش� �ĺ� */
 int data[SETSIZE][CNO];/* �н� ������ ��Ʈ */
 int teacher[SETSIZE];/* ���� ������ */
 int bestscore = 0;/* ���� ���� ���� */
 int bestanswer[CNO];/* Ž�� �� ã�� ���� ���� ���� */

 srand(SEED);/* ���� �ʱ�ȭ */

 /*�н� ������ ��Ʈ�� �о���� */
 readdata(data,teacher) ;

 /* �ش� �ĺ� ������ �˻� */
 for (i = 0; i<GENMAX; ++i) {
  /* �ش� �ĺ� ���� */
  for (j = 0; j<CNO; ++j) {
   answer[j] = rand012();
  }

  /* �˻� */
  score=calcscore(data,teacher,answer) ;

  /* ���� ���� ������ ���� */
  if (score>bestscore) {/* ���ݱ��� ���� ���� ������� ���� */
   for (j = 0; j<CNO; ++j)
    bestanswer[j] = answer[j];
   bestscore = score;
   for (j = 0; j<CNO; ++j)
    printf("%1d ", bestanswer[j]);
   printf(":score=%d\n", bestscore);
  }
 }
 /* ���� ���� �ش� ��� */
 printf("\n���� ���� �ش�\n");
 for (j = 0; j<CNO; ++j)
  printf("%1d ", bestanswer[j]);
 printf(":score=%d\n", bestscore);

 return 0;
}

/**********************************************/
/*            calcscore() �Լ�                 */
/* �ش� �ĺ� ������ ����(0��SETSIZE��) ���*/
/**********************************************/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO])
{
 int score = 0;/* ����(0��SETSIZE��)*/
 int point  ;/* ��ġ�� �ڸ���(0��CNO)  */
 int i,j ;
 
for (i = 0; i<SETSIZE; ++i) {
  /* ��ġ�� ��� */
  point = 0;
  for (j = 0; j<CNO; ++j) {
   if (answer[j] == 2) ++point;/* ���ϵ�ī�� */
   else if (answer[j] == data[i][j]) ++point;/* ��ġ */
  }

  if ((point == CNO) && (teacher[i] == 1)) {
   ++score;
  }
  else if ((point != CNO) && (teacher[i] == 0)) {
   ++score;
  }
 }
 return score ;
}

/****************************/
/*     readdata() �Լ�        */
/*�н� ������ ��Ʈ�� �о���� */
/****************************/
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE])
{
 int i,j ;
 
 for (i = 0; i<SETSIZE; ++i) {
  for (j = 0; j<CNO; ++j) {
   scanf("%d", &data[i][j]);
  }
  scanf("%d", &teacher[i]);
 }
}

/****************************/
/*     rand012() �Լ�        */
/*��0, 1 �Ǵ� 2�� ��ȯ�ϴ� ���� �Լ� */
/****************************/
int rand012()
{
 int rnd ;
 
 /* ������ �ִ��� ���� */
 while((rnd=rand())==RAND_MAX) ;
 /* ���� ��� */ 
 return (double)rnd/RAND_MAX*3 ;
}

