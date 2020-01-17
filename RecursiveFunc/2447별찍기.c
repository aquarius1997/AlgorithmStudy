//
//  2447별찍기.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/26.
//  Copyright © 2019 송혜경. All rights reserved.
// ***

#include <stdio.h>
int T[7000][7000];

void makeStar(int row, int col, int N) {
    int sub = N/3;
    int i;
    
    if(N == 3) {
        for(i=0; i<3; i++) {
            T[row][col+i] = 1;  //*
            T[row+2][col+i] = 1;
        }
        T[row+1][col] = 1;
        T[row+1][col+2] = 1;
    } else {
        makeStar(row, col, N/3);
        makeStar(row, col+sub, N/3);
        makeStar(row, col+(2*sub), N/3);
        
        makeStar(row+sub, col, N/3);
        makeStar(row+sub, col+(2*sub), N/3);
        
        makeStar(row+(2*sub), col, N/3);
        makeStar(row+(2*sub), col+sub, N/3);
        makeStar(row+(2*sub), col+(2*sub), N/3);
    }
}

int main(void) {
    int N;
    int i, j;
    
    scanf("%d", &N);

    
    makeStar(0, 0, N);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(T[i][j] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    return 0;
}
