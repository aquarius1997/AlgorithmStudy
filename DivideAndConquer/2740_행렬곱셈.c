//
//  2740_행렬곱셈.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/22.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int A[102][102] = {0, };
int B[102][102] = {0, };
int result[102][102] = {0, };
int N, M, K;

void devideFunc(int row, int col) {
    int i;
    int temp = 0;
    
    for(i=0; i<M; i++) {
        temp += (A[row][i] * B[i][col]);
    }
    
    result[row][col] = temp;
}

int main(void) {
    int i, j;
    
    scanf("%d %d", &N, &M);
    
    for(i=0; i<N; i++) {
        for(j=0; j<M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    
    scanf("%d %d", &M, &K);
    
    for(i=0; i<M; i++) {
        for(j=0; j<K; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    
    for(i=0; i<N; i++) {
        for(j=0; j<K; j++) {
            devideFunc(i, j);
        }
    }
    
    for(i=0; i<N; i++) {
        for(j=0; j<K; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
