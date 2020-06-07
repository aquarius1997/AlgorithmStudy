//
//  모의ST_연구소.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/12.
//  Copyright © 2020 송혜경. All rights reserved.
//  22min.

#include <cstdio>
#include <queue>
using namespace std;

int g_table[10][10] = {0,};
int g_N = 0;
int g_M = 0;
int g_maxCnt = 0;
queue<int> g_Q;

void bfs_spreading(void) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int r, c;
    
    while(!g_Q.empty()) {
        r = g_Q.front();    g_Q.pop();
        c = g_Q.front();    g_Q.pop();
        
        for(int d=0; d<4; d++) {
            if(r+dx[d] >= 0 && r+dx[d] < g_N) {
                if(c+dy[d] >= 0 && c+dy[d] < g_M) {   //테이블 범위에 속하고
                    if(g_table[r+dx[d]][c+dy[d]] == 0) {    //빈칸이면
                        g_Q.push(r+dx[d]);  g_Q.push(c+dy[d]);  //큐에 삽입
                        g_table[r+dx[d]][c+dy[d]] = 2;  //세균으로 저장
                    }
                }
            }
        }   //end for(d)
        
    }
}


/// 3개의 벽을 세운다
/// @param row 벽을 세울 위치
/// @param col 벽을 세울 위치
/// @param cnt 함수 실행시 세우는 걸 포함해, 여태까지 세운 벽의 수
void constructing(int row, int col, int cnt) {
    int r, c;
    int tempT[10][10] = {0,};
    int safeCnt = 0;
    
    //벽을 세운다
    g_table[row][col] = 1;
    
    if(cnt == 3) {
        //현재 테이블 정보를 임시 저장
        for(r=0; r<g_N; r++) {
            for(c=0; c<g_M; c++) {
                tempT[r][c] = g_table[r][c];
                if(g_table[r][c] == 2) { g_Q.push(r);   g_Q.push(c);}   //동시에 세균 위치 큐에 삽입
            }
        }
        
        //세균 확산 함수 호출
        bfs_spreading();
        
        //안전영역 최대 크기 구해서 업데이트
        for(r=0; r<g_N; r++) {
            for(c=0; c<g_M; c++) {
                if(g_table[r][c] == 0) { safeCnt++; }
            }
        }
        if(safeCnt > g_maxCnt) { g_maxCnt = safeCnt;}

        
        //원래 테이블 정보로 원상 복구
        for(r=0; r<g_N; r++) {
            for(c=0; c<g_M; c++) {
                g_table[r][c] = tempT[r][c];
            }
        }
    } else {
        for(c=col+1; c<g_M; c++) {
            if(g_table[row][c] == 0) { constructing(row, c, cnt+1);}
        }
        for(r=row+1; r<g_N; r++) {
            for(c=0; c<g_M; c++) {
                if(g_table[r][c] == 0) { constructing(r, c, cnt+1);}
            }
        }
    }
    
    //벽 세운걸 없앤다
    g_table[row][col] = 0;
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
            if(g_table[i][j] == 0) {
                constructing(i, j, 1);
            }
        }
    }
    
    printf("%d", g_maxCnt);
    
    return 0;
}
