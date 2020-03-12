//
//  14501_퇴사.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/12.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int T[20] = {0, };
int P[20] = {0, };
int maxNum = 0;
int N;

void bf(int idx, int sum) {
    if(sum > maxNum) {
        maxNum = sum;
    }
    for(int i=idx+1; i<idx+T[idx] && i<=N; i++) {   //현재 인덱스 포함 안할때
        bf(i, sum);
    }
    //현재 인덱스 포함할 때
    if(idx + T[idx] - 1 <= N) { //퇴사전까지 일 할 수 있으면
        if(sum + P[idx] > maxNum) {
            maxNum = sum + P[idx];
        }
        for(int i=idx+T[idx]; i<=N; i++) {
            bf(i, sum+P[idx]);
        }
    }
}

int main(void) {
    
    scanf("%d", &N);
    
    for(int i=1; i<=N; i++) {
        scanf("%d %d", &T[i], &P[i]);
    }
    
    bf(1, 0);
    
    printf("%d", maxNum);
    
    return 0;
}
