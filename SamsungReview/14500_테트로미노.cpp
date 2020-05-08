//
//  14500_테트로미노.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/08.
//  Copyright © 2020 송혜경. All rights reserved.
// 40min * 0Fail

#include <cstdio>
using namespace std;

int g_max = 0;
int g_N = 0;
int g_M = 0;
int g_table[502][502] ={0,};

void tetro(int r, int c) {
    int temp = 0;   int flag = 0;
    int i, j;
    //1번테트로미노
    for(j=c; j<=c+3; j++) {
        if(j >= g_M) { flag = 1; break; }
        temp += g_table[r][j];
    }
    if(flag == 0) {
        if(g_max < temp) { g_max = temp;}
    }
    flag = temp = 0;
    for(i=r; i<=r+3; i++) {
        if(i >= g_N) { flag = 1; break; }
        temp += g_table[i][c];
    }
    if(flag == 0) {
        if(g_max < temp) { g_max = temp;}
    }
    flag = temp = 0;
    //2번테트로미노
    for(i=r; i<=r+1; i++) {
        for(j=c; j<=c+1; j++) {
            if(i >= g_N || j >= g_M) { flag = 1; break;}
            temp += g_table[i][j];
        }
    }
    if(flag == 0) {
        if(g_max < temp) { g_max = temp;}
    }
    flag = temp = 0;
    //3번테트로미노
    for(i=r; i<=r+2; i++) {
        if(i >= g_N) { flag = 1; break;}
        temp += g_table[i][c];
    }
    if(flag == 0) {
        if(c+1 < g_M) {
            if(temp+g_table[r+2][c+1] > g_max) { g_max = temp+g_table[r+2][c+1];}
            if(temp+g_table[r][c+1] > g_max) { g_max = temp+g_table[r][c+1];}
            //5번
            if(temp+g_table[r+1][c+1] > g_max) { g_max = temp+g_table[r+1][c+1];}
        }
        if(c-1 >= 0) {
            if(temp+g_table[r][c-1] > g_max) { g_max = temp+g_table[r][c-1];}
            if(temp+g_table[r+2][c-1] > g_max) { g_max = temp+g_table[r+2][c-1];}
            //5번
            if(temp+g_table[r+1][c-1] > g_max) { g_max = temp+g_table[r+1][c-1];}
        }
    }
    flag = temp = 0;
    for(j=c; j<=c+2; j++) {
        if(j >= g_M) { flag = 1; break;}
        temp += g_table[r][j];
    }
    if(flag == 0) {
        if(r+1 < g_N) {
            if(temp+g_table[r+1][c] > g_max) { g_max = temp+g_table[r+1][c];}
            if(temp+g_table[r+1][c+2] > g_max) { g_max = temp+g_table[r+1][c+2];}
            //5번
            if(temp+g_table[r+1][c+1] > g_max) { g_max = temp+g_table[r+1][c+1];}
        }
        if(r-1 >= 0) {
            if(temp+g_table[r-1][c] > g_max) { g_max = temp+g_table[r-1][c];}
            if(temp+g_table[r-1][c+2] > g_max) { g_max = temp+g_table[r-1][c+2];}
            //5번
            if(temp+g_table[r-1][c+1] > g_max) { g_max = temp+g_table[r-1][c+1];}
        }
    }
    flag = temp = 0;
    //4번테트로미노
    for(i=r; i<=r+1; i++) {
        if(i >= g_N) { flag = 1; break;}
        temp += g_table[i][c];
    }
    if(flag == 0) {
        if(r+2 < g_N && c+1 < g_M) {
            if(temp + g_table[r+1][c+1] + g_table[r+2][c+1] > g_max) { g_max = temp + g_table[r+1][c+1] + g_table[r+2][c+1];}
        }
        if(r-1 >= 0 && c+1 < g_M) {
            if(temp + g_table[r-1][c+1] + g_table[r][c+1] > g_max) { g_max
                = temp + g_table[r-1][c+1] + g_table[r][c+1];
            }
        }
        if(c+1 < g_M && c-1 >= 0) {
            if(temp + g_table[r][c+1] + g_table[r+1][c-1] > g_max) { g_max = temp + g_table[r][c+1] + g_table[r+1][c-1];}
            if(temp + g_table[r][c-1] + g_table[r+1][c+1] > g_max ) { g_max
                = temp + g_table[r][c-1] + g_table[r+1][c+1];
            }
        }
    }
    flag = temp = 0;
}

int main(void) {
    int i, j;
    
    scanf("%d %d", &g_N, &g_M);
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_M; j++) {
            scanf("%d", &g_table[i][j]);
        }
    }
    
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_M; j++) {
            tetro(i, j);
        }
    }
    
    printf("%d", g_max);
    
    return 0;
}
