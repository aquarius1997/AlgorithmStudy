//
//  10830_행렬제곱.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/26.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** 문제는 빨리풀었으나 조건찾기 개힘들었음

/*
 2 1
 1000 1000
 1000 1000
 
 을 고려못해 마지막에 계속 오류뜸

 고치기전 출력
 1000 1000
 1000 1000
 고친이후
 0 0
 0 0
 */

#include <stdio.h>

int N;
int A[6][6] ={0,};
int result[6][6] = {0,};
int temp[6][6] = {0, };


void multi(int row, int col) {
    int num = 0;
    int i;
    
    for(i=0; i<N; i++) {
        num += (result[row][i] * A[i][col]);
        num = num % 1000;
    }
    
    temp[row][col] = num;
}

void resultsMulti(int row, int col) {
    int num = 0;
    int i;
    
    for(i=0; i<N; i++) {
        num += (result[row][i] * result[i][col]);
        num = num % 1000;
    }
    
    temp[row][col] = num;
}

void divideAndConquer(long long b) {
    int i, j;
    
    if(b == 1) {
        for(i=0; i<N; i++) {    //정답 result행렬에 저장
            for(j=0; j<N; j++) {
                result[i][j] = A[i][j] % 1000;
                /* 위 코드
                 result[i][j] = A[i][j];
                 로 햇더니
                 2 1
                 1000 1000
                 1000 1000
                 
                 결과가
                 1000 1000
                 1000 1000
                 이되어 마지막에 계속 오류뜸
                 */
            }
        }
    } else if(b == 2) {
        for(i=0; i<N; i++) {    //result행렬 * A행렬
            for(j=0; j<N; j++) {
                multi(i, j);
            }
        }
        for(i=0; i<N; i++) {    //정답 result행렬에 저장
            for(j=0; j<N; j++) {
                result[i][j] = temp[i][j];
            }
        }
    } else {
        divideAndConquer(b/2);

        if(b % 2 == 0) {    //b가 짝수면 A^(b/2) * A^(b/2)
            for(i=0; i<N; i++) {    //result * result
                for(j=0; j<N; j++) {
                    resultsMulti(i, j);
                }
            }
            for(i=0; i<N; i++) {    //정답 result행렬에 저장
                for(j=0; j<N; j++) {
                    result[i][j] = temp[i][j];
                }
            }
        } else { //홀수면 A^(b/2) * A^(b/2) * A
            for(i=0; i<N; i++) {
                for(j=0; j<N; j++) {
                    resultsMulti(i, j);
                }
            }
            for(i=0; i<N; i++) {    //정답 result행렬에 저장
                for(j=0; j<N; j++) {
                    result[i][j] = temp[i][j];
                }
            }
            for(i=0; i<N; i++) {    //result행렬 * A행렬
                for(j=0; j<N; j++) {
                    multi(i, j);
                }
            }
            for(i=0; i<N; i++) {    //정답 result행렬에 저장
                for(j=0; j<N; j++) {
                    result[i][j] = temp[i][j];
                }
            }
        }
    }

}

int main(void) {
    long long B;
    int i, j;
    
    scanf("%d %lld", &N, &B);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &A[i][j]);
            result[i][j] = A[i][j];
        }
    }
    
    divideAndConquer(B);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
