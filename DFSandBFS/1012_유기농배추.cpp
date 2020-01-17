//
//  1012_유기농배추.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/09.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int ground[52][52] = {0, }; //배추가 심어져 있는 곳은 1
int visited[52][52] = {0, };    //방문한 노드는 1
int N, M;

/// 배추가 심어져있는 인접 구역을 dfs탐색한다
/// @param row 탐색을 시작할 노드의 행정보
/// @param col 탐색을 시작할 노드의 열정보
void dfs_f(int row, int col) {
    
    //입력으로 들어온 노드에 대해 방문 처리한다
    visited[row][col] = 1;
    
    //상하좌우에 대해 인접 노드는 탐색
    if(row-1 >= 0) {
        if(ground[row-1][col] == 1 && visited[row-1][col] == 0) {
            dfs_f(row-1, col);
        }
    }
    if(row+1 < M) {
        if(ground[row+1][col] == 1 && visited[row+1][col] == 0) {
            dfs_f(row+1, col);
        }
    }
    if(col-1 >= 0) {
        if(ground[row][col-1] == 1 && visited[row][col-1] == 0) {
            dfs_f(row, col-1);
        }
    }
    if(col+1 < N) {
        if(ground[row][col+1] == 1 && visited[row][col+1] == 0) {
            dfs_f(row, col+1);
        }
    }
}

int main(void) {
    int t, T;
    int K, X, Y;
    int callCnt = 0;    //그래프들의 개수를 카운트한다
    int i, j;
    
    scanf("%d", &T);
    
    for(t=0; t<T; t++) {
        scanf("%d %d %d", &M, &N, &K);
        
        for(i=0; i<K; i++){ //심어져있는 위치를 입력받음
            scanf("%d %d", &X, &Y);
            ground[X][Y] = 1;   //심어져있는 곳은 1로 저장
        }
        
        //모든 그래프들에 대하여 dfs방문
        for(i=0; i<M; i++) {
            for(j=0; j<N; j++) {
                if(ground[i][j] == 1 && visited[i][j] == 0) {
                    dfs_f(i, j);
                    callCnt++;
                }
            }
        }
        
        printf("%d\n", callCnt);
        
        //초기화
        callCnt = 0;
        for(i=0; i<M; i++) {
            for(j=0; j<N; j++) {
                ground[i][j] = visited[i][j] = 0;
            }
        }
    }
    
    return 0;
}
