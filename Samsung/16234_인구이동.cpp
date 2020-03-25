//
//  16234_인구이동.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/25.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
using namespace std;

int N, L, R;
int table[52][52] = {0, };
int visited[52][52] = {0, };
int union_cnt = 0;
int union_sum = 0;
queue<int> Queue;

void dfs_simul(int row, int col) {
    int diff;
    
    union_cnt += 1;
    union_sum += table[row][col];
    visited[row][col] = 1;
    Queue.push(row);    Queue.push(col);
    
    if(row-1 >= 0) {
        diff = table[row-1][col] - table[row][col];
        if(diff < 0) { diff *= (-1); }
        if(diff >= L && diff <= R) {
            if(visited[row-1][col] == 0) {
                dfs_simul(row-1, col);
            }
        }
    }
    if(row+1 < N) {
        diff = table[row+1][col] - table[row][col];
        if(diff < 0) { diff *= (-1); }
        if(diff >= L && diff <= R) {
            if(visited[row+1][col] == 0) {
                dfs_simul(row+1, col);
            }
        }
    }
    if(col-1 >= 0) {
        diff = table[row][col-1] - table[row][col];
        if(diff < 0) { diff *= (-1); }
        if(diff >= L && diff <= R) {
            if(visited[row][col-1] == 0) {
                dfs_simul(row, col-1);
            }
        }
    }
    if(col+1 < N) {
        diff = table[row][col+1] - table[row][col];
        if(diff < 0) { diff *= (-1); }
        if(diff >= L && diff <= R) {
            if(visited[row][col+1] == 0) {
                dfs_simul(row, col+1);
            }
        }
    }
}

int main(void) {
    int flag = 0;
    int cnt = 0;
    scanf("%d %d %d", &N, &L, &R);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    while(flag == 0) {
        flag = 1;
        //인구 이동이 한번이라도 발생하면 flag를 0으로 변경한다
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                if(visited[i][j] == 0) {
                    union_cnt = union_sum = 0;
                    dfs_simul(i, j);
                    int newVal = union_sum / union_cnt;
                    if(union_cnt > 1) { //인구이동
                        flag = 0;
                    }
                    while(!Queue.empty()) {
                        int r = Queue.front();  Queue.pop();
                        int c = Queue.front();  Queue.pop();
                        table[r][c] = newVal;
                    }
                }
            }
        }
        //방문여부초기화
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++){
                visited[i][j] = 0;
            }
        }

        if(flag == 0) {
            cnt++;
        }
    }
    
    printf("%d", cnt);
    
    return 0;
}
