//
//  11047_동전0.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/16.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int main(void) {
    int coins[1000002] = {0, };
    int maxIdx = 0;
    int N, K;
    int cnt=0;
    int i;
    
    scanf("%d %d", &N, &K);
    
    for(i=0; i<N; i++) {
        scanf("%d", &coins[i]);
        if(coins[i] <= K) { //K보다 같거나 작은 동전들 중에서 최대값을 가지는 동전을 알아낸다
            maxIdx = i;
        }
    }
    
    for(i=maxIdx; i>=0; i--) {
        if(coins[i] <= K) {
            cnt += (K / coins[i]);
            K = K % coins[i];
        }
        if(K == 0) {
            break;
        }
    }
    
    printf("%d", cnt);
    
    return 0;
}
