//
//  인구이동BFS.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/26.
//  Copyright © 2020 송혜경. All rights reserved.
//
#include <cstdio>
#include <queue>
using namespace std;

int N, L, R;
int table[52][52] = {0, };
int visited[52][52] = {0, }; //방문 : 1
int flag = 0;   //한번이라도 연합이 이뤄지면 1로 변경

void population_migration(int row, int col) {
    queue<int> Queue;
    queue<int> tempQueue;   // 나중에 새로이 위치를 저장할 때 사용
    int unionCnt = 0;   int unionSum = 0;
    int r, c;
    int diff;
    
    //큐에 첫번째 위치 삽입
    Queue.push(row);    Queue.push(col);
    visited[row][col] = 1;
    //인접 정점 확인
    while(!Queue.empty()) {
        r = Queue.front();
        Queue.pop();
        c = Queue.front();
        Queue.pop();
        tempQueue.push(r);  tempQueue.push(c);
        
        unionCnt += 1;
        unionSum += table[r][c];
        //상하좌우
        if(r-1 >= 0) {  //배열 범위 확인
            if(visited[r-1][c] == 0) {  //방문 여부 확인
                diff = table[r][c] - table[r-1][c];
                if(diff < 0) { diff *= (-1); }
                if(diff >= L && diff <= R) {
                    Queue.push(r-1);
                    Queue.push(c);
                    visited[r-1][c] = 1;
                }
            }
        }
        if(r+1 < N) {
            if(visited[r+1][c] == 0) {
                diff = table[r][c] - table[r+1][c];
                if(diff < 0) { diff *= (-1); }
                if(diff >= L && diff <= R) {
                    Queue.push(r+1);
                    Queue.push(c);
                    visited[r+1][c] = 1;
                }
            }
        }
        if(c-1 >= 0) {
            if(visited[r][c-1] == 0) {
                diff = table[r][c] - table[r][c-1];
                if(diff < 0) { diff *= (-1); }
                if(diff >= L && diff <= R) {
                    Queue.push(r);
                    Queue.push(c-1);
                    visited[r][c-1] = 1;
                }
            }
        }
        if(c+1 < N) {
            if(visited[r][c+1] == 0) {
                diff = table[r][c] - table[r][c+1];
                if(diff < 0 ) { diff *= (-1); }
                if(diff >= L && diff <= R) {
                    Queue.push(r);
                    Queue.push(c+1);
                    visited[r][c+1] = 1;
                }
            }
        }
    }
    
    int newNum = unionSum / unionCnt;
    if(unionCnt > 1) {  //연합 생성된거 있으면
        flag = 1;
    }
    while(!tempQueue.empty()) {
        r = tempQueue.front();
        tempQueue.pop();
        c = tempQueue.front();
        tempQueue.pop();
        
        table[r][c] = newNum;
    }
}


int main(void) {
    int roundCnt = 0;
    int i, j;
    
    scanf("%d %d %d", &N, &L, &R);
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    while(1) {
        flag = 0;
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(visited[i][j] == 0) {
                    population_migration(i, j);
                }
            }
        }
        if(flag == 0) { //연합 이룬거 없으면
            break;
        }
        //방문여부 초기화
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                visited[i][j] = 0;
            }
        }
        roundCnt++;
    }

    printf("%d", roundCnt);
    
    return 0;
}
