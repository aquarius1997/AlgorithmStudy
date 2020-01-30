//
//  1780_종이의개수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <stdio.h>
#define MAXN 2500

int T[MAXN][MAXN] = {0, };
int zeroCnt = 0;    int minusCnt = 0;   int plusCnt = 0;

/// [r1,c1] ~ [r2, c2] 범위의 종이가 모두 같은 숫자인지 검증하여 아닐경우 분할정복한다
/// @param r1 시작 행
/// @param r2 마지막 행
/// @param c1 시작 열
/// @param c2 마지막 열
void numOfPaper(int r1, int r2, int c1, int c2) {
    int num;
    int div;
    int flag = 0;
    int i, j;
    
    num = T[r1][c1];
    
    for(i=r1; i<=r2; i++) {
        for(j=c1; j<=c2; j++) {
            if(T[i][j] != num) {    //다 같은 숫자로 채워져 있지 않을 경우
                flag = 1;   break;
            }
        }
        if(flag == 1) {
            break;
        }   //end for(j)
    }   //end for(i)
    
    if(flag == 1) { //분할정복
        div = (r2 - r1 + 1) / 3;
        numOfPaper(r1, r1+div-1, c1, c1+div-1);
        numOfPaper(r1, r1+div-1, c1+div, c1+(2*div)-1);
        numOfPaper(r1, r1+div-1, c1+2*div, c1+(3*div)-1);
        numOfPaper(r1+div, r1+(2*div)-1, c1, c1+div-1);
        numOfPaper(r1+div, r1+(2*div)-1, c1+div, c1+(2*div)-1);
        numOfPaper(r1+div, r1+(2*div)-1, c1+2*div, c1+(3*div)-1);
        numOfPaper(r1+2*div, r1+(3*div)-1, c1, c1+div-1);
        numOfPaper(r1+2*div, r1+(3*div)-1, c1+div, c1+(2*div)-1);
        numOfPaper(r1+2*div, r1+(3*div)-1, c1+2*div, c1+(3*div)-1);
    } else {    //같은 숫자
        if(num == 1) {
            plusCnt++;
        } else if(num == 0) {
            zeroCnt++;
        } else {
            minusCnt++;
        }
    }
}



int main(void) {
    int N;
    int i, j;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    
    numOfPaper(0, N-1, 0, N-1);
    
    printf("%d\n%d\n%d", minusCnt, zeroCnt, plusCnt);
    
    return 0;
}
