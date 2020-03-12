//
//  14502_연구소.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/12.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
using namespace std;

int table[10][10];
int tempTable[10][10];
int N, M;
int maxNum = 0;
queue<int> Queue;   //바이러스의 위치 정보를 저장한다
int visited[10][10] = {0, };

void virus(void) {
    int row, col;
    
    while(!Queue.empty()) {
        row = Queue.front();    Queue.pop();
        col = Queue.front();    Queue.pop();
        tempTable[row][col] = 2;
        
        //상하좌우 전파 가능한지 확인해서 가능하면 푸시
        if(row-1 >= 0) {
            if(visited[row-1][col] == 0 && tempTable[row-1][col] == 0) {
                Queue.push(row-1);  Queue.push(col);
                visited[row-1][col] = 1;
            }
        }
        if(row+1 < N) {
            if(visited[row+1][col] == 0 && tempTable[row+1][col] == 0) {
                Queue.push(row+1);  Queue.push(col);
                visited[row+1][col] = 1;
            }
        }
        if(col-1 >= 0) {
            if(visited[row][col-1] == 0 && tempTable[row][col-1] == 0) {
                Queue.push(row);    Queue.push(col-1);
                visited[row][col-1] = 1;
            }
        }
        if(col+1 < M) {
            if(visited[row][col+1] == 0 && tempTable[row][col+1] == 0) {
                Queue.push(row);    Queue.push(col+1);
                visited[row][col+1] = 1;
            }
        }
        //End 상하좌우 전파 가능한지 확인해서 가능하면 푸시
    }
    
}

/// 빈칸에 벽을 세개 세우고 안전 영역의 최대 개수를 업데이트한다
/// @param row 벽을 세울 위치의 행
/// @param col 벽을 세울 위치의 열
/// @param cnt 현재까지 세운 벽의 수
void simul_dfs(int row, int col, int cnt) {
    int safeCnt = 0;
    table[row][col] = 1;
    
    if(cnt >= 3) {
        //바이러스 전파시키는 BFS호출
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(table[i][j] == 2) {
                    Queue.push(i);  Queue.push(j);
                    visited[i][j] = 1;  //방문처리
                }
                tempTable[i][j] = table[i][j];  //tempTable가지고 바이러스 전파시킬거임
            }
        }
        virus();
        
        //빈칸수 세서 최대 안전구역 업데이트 가능한지 확인
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(tempTable[i][j] == 0) {
                    safeCnt++;
                }
                visited[i][j] = tempTable[i][j] = 0;  //동시에 초기화
            }
        }
        if(safeCnt > maxNum) {
            maxNum = safeCnt;
        }
    } else {
        for(int j=col+1; j<M; j++) {
            if(table[row][j] == 0) {
                simul_dfs(row, j, cnt+1);
            }
        }
        for(int i=row+1; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(table[i][j] == 0) {
                    simul_dfs(i, j, cnt+1);
                }
            }
        }
    }
    //세웠던 벽 없애주기
    table[row][col] = 0;
}

int main(void) {
    scanf("%d %d", &N, &M);
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    //빈칸이 있으면 해당 칸을 시작으로 벽을 세개 세우는 함수를 호출한다
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(table[i][j] == 0) {
                simul_dfs(i, j, 1);
            }
        }
    }
    
    printf("%d", maxNum);
    
    return 0;
}
