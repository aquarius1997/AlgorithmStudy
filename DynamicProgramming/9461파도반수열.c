//
//  9461파도반수열.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/07.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <stdio.h>

int main(void) {
    long P[102];
    int N, T;
    int i, t;
    
    scanf("%d", &T);
    
    //base-case
    P[1] = P[2] = P[3] = 1;
    P[4] = P[5] = 2;
    
    //파도반 수열은 바로 직전 삼각형과 5번째 전의 삼각형을 이어붙인 길이를 가짐
    for(i=6; i<=100; i++) {
        P[i] = P[i-1] + P[i-5];
    }
    
    for(t=0; t<T; t++) {
        scanf("%d", &N);
        printf("%ld\n", P[N]);
    }

    return 0;
}
