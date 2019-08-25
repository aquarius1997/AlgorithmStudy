//
//  2798블랙잭.c
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <stdio.h>

int N, M;
int card[102] = {0, };
int max = 0;

//count : 현재 sum에 포함된 카드의 수 ( main에서 1로 넘겨준다)
void dfs_f(int idx, int count, int sum) {
    int i;
    
    if( count >= 3 ) {
        sum += card[idx];
        
        if( sum <= M && sum > max ) {
            max = sum;
        }
    }else {
        sum += card[idx];
        
        for( i=idx+1; i<N; i++ ){
            dfs_f(i, count+1, sum);
        }
    }
    
}


int main(void) {
    int i;
    
    scanf("%d %d", &N, &M);
    
    for( i=0; i<N; i++ ) {
        scanf("%d", &card[i]);
    }
    
    for( i=0; i<=N-3; i++ ) {
        dfs_f(i, 1, 0);
    }
    
    printf("%d", max);
    
    return 0;
}
