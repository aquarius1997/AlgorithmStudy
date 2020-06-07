//
//  지폐사용.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/06/05.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int t[1000][2] = {0, };
int N = 0;
int max = 0;

void dfs(int idx, int sum) {
    if(sum > max) { max = sum; }
    for(int i=idx; i<N; i++) {
        if(i+t[i][0] < N) {
            dfs(i+t[i][0], sum+t[i][1]);
        }
    }
}


int main(void) {
    scanf("%d", &N);
    
    for(int i=0; i<N; i++) {
        scanf("%d", &t[i][0]);
        scanf("%d", &t[i][1]);
    }
    
    for(int i=0; i<N; i++) {
        dfs(i, 0);
    }
    
    printf("%d", max);
    
    return 0;
}
