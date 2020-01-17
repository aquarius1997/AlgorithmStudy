//  17144미세먼지안녕.cpp
//  삼성기출문제
//
//  Created by 송혜경 on 21/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <stdio.h>

int A[55][55] = {0, };
int R, C, T;
int R1, R2; //공기청정기 위치

//미세먼지 확장+공기청정기 가동 함수
void round_f(void) {
    int i, j;
    int spread, a, count;
    int temp[55][55] = {0, };
    
    //미세먼지 확장
    for(i=1; i<=R; i++) {
        for(j=1; j<=C; j++) {
            
            //먼지 발견
            if(A[i][j] != 0 || A[i][j] != -1) {
                count = 0;  //확산 방향 개수를 세기 위한 초기화
                spread = A[i][j] / 5;   //확산시킬 양
                
                if(i-1 >= 1 && A[i-1][j] != -1) {
                    count++;    temp[i-1][j] += spread;
                }
                if(i+1 <= R && A[i+1][j] != -1) {
                    count++;    temp[i+1][j] += spread;
                }
                if(j-1 >= 1 && A[i][j-1] != -1) {
                    count++;    temp[i][j-1] += spread;
                }
                if(j+1 <= C && A[i][j+1] != -1) {
                    count++;    temp[i][j+1] += spread;
                }
                
                a = A[i][j] - (spread * count);
                
                temp[i][j] += a;
            }   //end 먼지발견 if
            
        }   //end inner loop
    }   //end outer loop, end 미세먼지 확장
    
    //위쪽 공기청정기 가동
    for(i = R1-2; i >= 1; i--) {
        temp[i+1][1] = temp[i][1];
    }
    for(j = 2; j <= C; j++) {
        temp[1][j-1] = temp[1][j];
    }
    for(i = 2; i <= R1; i++) {
        temp[i-1][C] = temp[i][C];
    }
    for(j = C-1; j >= 2; j--) {
        temp[R1][j+1] = temp[R1][j];
    }
    temp[R1][2] = 0;
    
    //아래쪽 공기청정기 가동
    for(i = R2+2; i <= R; i++) {
        temp[i-1][1] = temp[i][1];
    }
    for(j = 2; j <= C; j++) {
        temp[R][j-1] = temp[R][j];
    }
    for(i = R-1; i >= R2; i--) {
        temp[i+1][C] = temp[i][C];
    }
    for(j = C-1; j >= 2; j--) {
        temp[R2][j+1] = temp[R2][j];
    }
    temp[R2][2] = 0;
    
    
    //temp -> A
    for(i = 1; i <= R; i++)
        for(j = 1; j <= C; j++)
            A[i][j] = temp[i][j];
    
}


int main(void) {
    int i, j, t;
    int minus_count = 0;
    int result = 0;
    
    scanf("%d %d %d", &R, &C, &T);
    
    for(i = 1; i <= R; i++) {
        for(j = 1; j <= C; j++) {
            scanf("%d", &A[i][j]);
            //공기 청정기의 위치를 저장
            if(A[i][j] == -1 && minus_count == 0){
                R1 = i; R2 = i+1; minus_count++;
            }
        }
    }
    
    for(t = 0; t < T; t++) {
        round_f();
    }
    
    for(i = 1; i <= R; i++) {
        for(j = 1; j <= C; j++){
            if(A[i][j] != -1)
                result += A[i][j];
        }
    }
    
    printf("%d", result);
    return 0;
}
