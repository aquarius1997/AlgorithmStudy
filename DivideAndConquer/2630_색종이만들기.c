//
//  2630_색종이만들기.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/07.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <stdio.h>

int T[129][129] = {0, };
int blueCnt = 0;
int whiteCnt = 0;

/*
 구역[행(s1~e1) 열(s2~e2)] 에 대하여 모두 같은 색으로 칠해져 있는지 확인한다.
 같은색이 아닐 경우 분할, 같은색일 경우 카운트
 s1 : 모두 같은 색인지 검사할 행의 시작 인덱스, e1 : 행의 마지막 인덱스
 s2 : .. 열의 시작 인덱스, e2 : 열의 마지막 인덱스
 */
void divide_conquer(int s1, int e1, int s2, int e2) {
    int rowMid, colMid;
    int bOrW = 0;   //모두 파란색으로 칠해져 있을 경우1, 모두 하얀색일 경우0, 섞여 있을 경우 -1
    int color;
    int i, j;

    if(s1 == e1) {  //크기가 하나짜리면 무슨색인지 알아내서 카운팅하고 종료
        color = T[s1][s2];
        if(color == 0) {
            whiteCnt++;
        } else {
            blueCnt++;
        }
    } else {    //크기가 2이상이면
        color = T[s1][s2];  //가장 첫번째 칸의 색을 기준으로 검증
        for(i=s1; i<=e1; i++) {
            for(j=s2; j<=e2; j++) {
                if(T[i][j] != color) {  //모두 같은 색이 아니면
                    bOrW = -1;  break;
                }
            }
            if(bOrW == -1) {
                break;
            }
        }
        
        if(bOrW != -1) {    //모두 같은 색일 경우
            if(color == 0) {    //흰색일 경우
                whiteCnt++;
            } else {
                blueCnt++;
            }
        } else {    //모두 같은 색이아닌경우 분할
            //가운데가 어딘지 알아내고
            rowMid = (s1 + e1) / 2;
            colMid = (s2 + e2) / 2;
            //네개로 분할정복
            divide_conquer(s1, rowMid, s2, colMid);
            divide_conquer(s1, rowMid, colMid+1, e2);
            divide_conquer(rowMid+1, e1, s2, colMid);
            divide_conquer(rowMid+1, e1, colMid+1,e2);
        }
    }
    

}

int main(void) {
    int N;
    int i, j;
    
    scanf("%d", &N);
    
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    
    divide_conquer(1, N, 1, N);
    
    printf("%d\n%d", whiteCnt, blueCnt);
    
    return 0;
}
