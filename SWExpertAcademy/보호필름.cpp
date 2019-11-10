//
//  FINDBEAD.cpp
//  AJ
//
//  Created by 송혜경 on 17/10/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//  지겨워 죽겠네

#include <stdio.h>

using namespace std;

const int MAXN = 101;

int Up[MAXN][MAXN] = {0, };   //Up[i][j] = 1 : 구슬 j는 구슬 i보다 무거움
int Down[MAXN][MAXN] = {0, };   //Down[i][j] = 1 : 구슬 j는 구슬 i보다 가벼움

int N;


void dfsUp(int node, int next) {
    int i;
    
    for(i=1; i<=N; i++) {
        //next구슬 보다 i구슬이 더 무거우면
        if(Up[next][i] == 1) {
            Up[node][i] = 1;
            dfsUp(node, i);
        }
    }
    
}


void dfsDown(int node, int next) {
    int i;
    
    for(i=1; i<=N; i++) {
        //next구슬보다 i구슬이 더 가벼우면
        if(Down[next][i] == 1) {
            Down[node][i] = 1;
            dfsDown(node, i);
        }
    }
}

int main(void) {
    int M, a, b;
    int mid;
    int counting1, counting2;
    int result = 0;
    int i, j;
    
    scanf("%d %d", &N, &M);
    
    mid = (N+1) / 2;
    
    for(i=0; i<M; i++) {
        scanf("%d %d", &a, &b);
        Up[b][a] = 1;
        Down[a][b] = 1;
    }
    
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            if(Up[i][j] == 1) {
                dfsUp(i, j);
            }
            if(Down[i][j] == 1) {
                dfsDown(i, j);
            }
        }
    }
    
    for(i=1; i<=N; i++) {
        counting1 = counting2 = 0;
        
        for(j=1; j<=N; j++) {
            
            if(Up[i][j] == 1) {
                counting1++;
            }
            if(Down[i][j] == 1) {
                counting2++;
            }
        }
        
        if(counting1 >= mid || counting2 >= mid) {
            result++;
        }
    }
    
    printf("%d", result);
    
    return 0;
    
}
