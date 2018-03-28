/********************************************/
/*              kpdatagen.c                 */
/* 배낭 문제 데이터 생성기                  */
/* 짐의 중량과 가치를 난수로 생성           */
/* 사용 방법                                */
/*\Users\deeplearning\ch3>kpdatagen>data.txt*/
/********************************************/

/*Visual Studio와의 호환성 확보 */
#define _CRT_SECURE_NO_WARNINGS

/*헤더 파일 포함*/
#include <stdio.h>
#include <stdlib.h>

/*   기호 상수 정의                 */
#define MAXVALUE 100 /*무게와 가치의 최댓값*/
#define N 30 /*짐 개수*/
#define SEED 32768 /*난수 시드*/

/*   함수 프로토타입 선언      */
int randdata() ; /*MAXVALUE 이하의 정수를 반환하는 난수 함수*/

/****************/
/*  main() 함수 */
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
/*     randdata() 함수                       */
/*MAXVALUE 이하의 정수를 반환하는 난수 함수  */
/*********************************************/
int randdata()
{
 int rnd ;
 
 /*난수의 최댓값 제외*/
 while((rnd=rand())==RAND_MAX) ;
 /*난수의 계산*/ 
 return (int)((double)rnd/RAND_MAX*MAXVALUE+1) ;
}
