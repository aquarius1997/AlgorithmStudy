//
//  14501_퇴사.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/08.
//  Copyright © 2020 송혜경. All rights reserved.
//  *** 15min 0fail

#include <cstdio>
using namespace std;

int g_N = 0;
int g_table[17][2] = {0,};
int g_max = 0;

void dfs_simul(int pSum, int dayIdx) {
    if(pSum > g_max) { g_max = pSum; }
    
    for(int i=dayIdx; i<=g_N; i++) {
        if(g_table[i][0] + i - 1 <= g_N) {
            dfs_simul(pSum + g_table[i][1], g_table[i][0]+i);
        
        }
    }
}


int main(void) {
    int i;
    
    scanf("%d", &g_N);
    for(i=1; i<=g_N; i++) {
        scanf("%d %d", &g_table[i][0], &g_table[i][1]);
    }
    
    dfs_simul(0, 1);
    
    printf("%d", g_max);
    
    return 0;
}
