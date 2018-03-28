/******************************/
/*          sum2.c            */
/*    합, 제곱 합 구하기      */
/* 표준 입력에서 실수를 읽어 */
/* 합과 제곱 합을 차례대로 출력합니다. */
/* <Ctrl> + <Z>로 종료합니다. */
/* 사용 방법                     */
/* C:\Users\deeplearning\ch1>sum2 */
/******************************/

/* Visual Studio와의 호환성 확보 */
#define _CRT_SECURE_NO_WARNINGS

/* 헤더 파일 포함 */
#include <stdio.h>
#include <stdlib.h>

/* 기호 상수 정의 */
#define BUFSIZE 256  /* 입력 버퍼 크기 */

/****************/
/*  main() 함수  */
/****************/
int main()
{
 char linebuf[BUFSIZE] ;/* 입력 버퍼 */
 double data ;/* 입력 데이터 */
 double sum=0.0 ;/* 합 */
 double sum2=0.0 ;/* 제곱 합*/

 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){
  /* 행을 읽어들일 수 있는 한 계속 반복 */
  if(sscanf(linebuf,"%lf",&data)!=0){/* 변환이 가능하다면 */
    sum+=data ;
    sum2+=data*data ;
    printf("%lf\t%lf\n",sum,sum2) ;
  }
 }

 return 0 ;
}