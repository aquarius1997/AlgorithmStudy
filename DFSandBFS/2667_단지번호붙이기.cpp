//
//  2667_단지번호붙이기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/09.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int houses[1000] = {0, };    //각 단지에 속하는 집의 개수를 저장할 배열
int housesIdx = 0;
int visited[26][26] = {0, };    //BFS 방문 노드인지 확인 (1 : 방문함)

/// 단지내 집의 수를 카운팅한다
/// @param N 지도크기
/// @param row BFS탐색을 시작할 노드의 행정보
/// @param col BFS탐색을 시작할 노드의 열정보
void bfs_f(int T[26][26], int N, int row, int col) {
    queue<int> Queue;
    int houseCnt = 0;   //단지의 집 개수
    int r, c;
    
    //큐에 인자로 주어진 행, 열 정보를 삽입
    Queue.push(row);    Queue.push(col);
    visited[row][col] = 1;
    
    //큐가 빌때까지 반복
    while(!Queue.empty()) {
        r = Queue.front();  Queue.pop();
        c = Queue.front();  Queue.pop();
        houseCnt++;
        
        //상하좌우확인
        if(r-1 >= 0) {
            if(T[r-1][c] == 1 && visited[r-1][c] == 0) {
                Queue.push(r-1);    Queue.push(c);
                visited[r-1][c] = 1;
            }
        }
        if(r+1 < N) {
            if(T[r+1][c] == 1 && visited[r+1][c] == 0) {
                Queue.push(r+1);    Queue.push(c);
                visited[r+1][c] = 1;
            }
        }
        if(c-1 >= 0) {
            if(T[r][c-1] == 1 && visited[r][c-1] == 0) {
                Queue.push(r);  Queue.push(c-1);
                visited[r][c-1] = 1;
            }
        }
        if(c+1 < N) {
            if(T[r][c+1] == 1 && visited[r][c+1] == 0) {
                Queue.push(r);  Queue.push(c+1);
                visited[r][c+1] = 1;
            }
        }
    }   //end while
    
    //단지 내 집의 개수를 저장하고 종료
    houses[housesIdx] = houseCnt;
    housesIdx++;
    
}


int main(void) {
    int T[26][26] = {0,};   char str[27];
    int N;
    int callCnt = 0;    //단지의 개수
    int i, j;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%s", str);
        for(j=0; j<N; j++) {
            T[i][j] = str[j] - '0';
        }
    }
    
    //BFS방문 호출
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(T[i][j] == 1 && visited[i][j] == 0) {
                bfs_f(T, N, i, j);
                callCnt++;
            }
        }
    }
    
    //단지내 집의 수를 오름차순 정렬
    sort(houses, houses+housesIdx);
    
    printf("%d\n", callCnt);
    for(i=0; i<housesIdx; i++) {
        printf("%d\n", houses[i]);
    }
    
    return 0;
}

