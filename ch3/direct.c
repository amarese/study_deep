/*****************************************/
/*              direct.c                 */
/*완전탐색으로 배낭 문제 풀기            */
/*사용 방법                              */
/*\Users\deeplearning\ch3>direct<data.txt*/
/*****************************************/

/*Visual Studio와의 호환성 확보 */
#define _CRT_SECURE_NO_WARNINGS

/*헤더 파일 포함*/
#include <stdio.h>
#include <stdlib.h>

/*   기호 상수 정의                 */
#define MAXVALUE 100 /*무게와 가치의 최댓값*/
#define N 30 /*짐 개수*/
#define WEIGHTLIMIT (N*MAXVALUE/10) 
			/*무게 제한*/
#define SEED 32768 /*난수 시드*/

/*   함수 프로토타입 선언      */
void initparcel(int parcel [N][2]);/*짐 초기화*/
void prints(int solution);/*정답 후보 출력*/
int solve(int parcel [N][2]) ;/*탐색*/
int pow2n(int n);/*2의 멱승*/
int calcval(int parcel[N][2],int i);/*평갓값 계산*/

/****************/
/*  main() 함수 */
/****************/
int main()
{
 int parcel[N][2] ;/*짐*/
 int solution=0xfff ;/*정답*/

 /*짐 초기화*/
 initparcel(parcel) ;
 /*탐색*/
 solution=solve(parcel) ;
 /*정답 출력*/
 prints(solution) ;
 return 0 ;
}

/****************************/
/*       solve() 함수       */
/*       탐색               */
/****************************/
int solve(int parcel [N][2])
{
 int i ;/*반복 제어*/
 int limit ;/*탐색 상한*/
 int maxvalue=0 ;/*평갓값의 최댓값*/
 int value ;/*평값값*/
 int solution ;/*정답 후보*/

 /*탐색 범위 설정*/
 limit=pow2n(N) ;
 /*정답 탐색*/
 for(i=0;i<limit;++i){
  /*평갓값 계산*/
  value=calcval(parcel,i) ;
  /*최댓값 갱신*/
  if(value>maxvalue){
   maxvalue=value ;
   solution=i ;
   printf("*** maxvalue %d\n",maxvalue) ;
  }
 }
 return solution ;
}

/****************************/
/*       calcval() 함수     */
/*       평갓값의 계산      */
/****************************/
int calcval(int parcel[N][2],int i)
{
 int pos ;/*유전자 위치 지정*/
 int value=0 ;/*평갓값*/
 int weight=0 ;/*중량*/

 /*각 유전자 위치를 조사하여 중량과 평갓값을 계산*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*((i>>pos)&0x1) ;
  value+=parcel[pos][1]*((i>>pos)&0x1) ;
 }
 /*죽은 유전자 처리*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
}

/****************************/
/*       pow2n() 함수       */
/*       2의 멱승           */
/****************************/
int pow2n(int n)
{
 int pow=1 ;
 for(;n>0;--n)
  pow*=2 ;
 return pow ;
}

/****************************/
/*     prints() 함수        */
/*     정답 후보 출력       */
/****************************/
void prints(int solution)
{
 int i ;
 for(i=0;i<N;++i)
  printf("%1d ",(solution>>i)&0x1) ;
 printf("\n") ;
}

/****************************/
/*     initparcel() 함수    */
/*     짐 초기화            */
/****************************/
void initparcel(int parcel [N][2])
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])!=EOF)){
  ++i ;
 }
}
