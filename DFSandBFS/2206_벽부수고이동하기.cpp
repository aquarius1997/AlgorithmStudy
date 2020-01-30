//
//  2206_벽부수고이동하기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/30.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
#define INF 987987987

using namespace std;

int N, M;
int T1[1002][1002] = {0, };
int T2[1002][1002] = {0, };


/// 시작점으로부터 각 지점까지의  최단 거리를 알아낸다
/// @param row 시작 정점의 행
/// @param col 시작 정점의 열
void bfs_f(int row, int col) {
    queue<int> Queue;
    int r, c, d;
    
    Queue.push(row);
    Queue.push(col);
    
    if(row == 1 && col == 1) {  //시작정점으로부터 최단거리 구하기
        while(!Queue.empty()) {
            r = Queue.front();  Queue.pop();
            c = Queue.front();  Queue.pop();
            d = T1[r][c] + 1;
            
            if(r-1 > 0 && (T1[r-1][c] == 0 || T1[r-1][c] > d)) {
                Queue.push(r-1);    Queue.push(c);
                T1[r-1][c] = d;
            }
            if(r+1 <= N && (T1[r+1][c] == 0 || T1[r+1][c] > d)) {
                Queue.push(r+1);    Queue.push(c);
                T1[r+1][c] = d;
            }
            if(c-1 > 0 && (T1[r][c-1] == 0 || T1[r][c-1] > d)) {
                Queue.push(r);  Queue.push(c-1);
                T1[r][c-1] = d;
            }
            if(c+1 <= M && (T1[r][c+1] == 0 || T1[r][c+1] > d)) {
                Queue.push(r);   Queue.push(c+1);
                T1[r][c+1] = d;
            }
        }
    } else {    //도착정점으로부터 최단거리 구하기
        while(!Queue.empty()) {
            r = Queue.front();  Queue.pop();
            c = Queue.front();  Queue.pop();
            d = T2[r][c] + 1;
            
            if(r-1 > 0 && (T2[r-1][c] == 0 || T2[r-1][c] > d)) {
                Queue.push(r-1);    Queue.push(c);
                T2[r-1][c] = d;
            }
            if(r+1 <= N && (T2[r+1][c] == 0 || T2[r+1][c] > d)) {
                Queue.push(r+1);    Queue.push(c);
                T2[r+1][c] = d;
            }
            if(c-1 > 0 && (T2[r][c-1] == 0 || T2[r][c-1] > d)) {
                Queue.push(r);  Queue.push(c-1);
                T2[r][c-1] = d;
            }
            if(c+1 <= M && (T2[r][c+1] == 0 || T2[r][c+1] > d)) {
                Queue.push(r);   Queue.push(c+1);
                T2[r][c+1] = d;
            }
        }
    }

}


int main(void) {
    char str[1002];
    int minDist = INF;
    int d1;
    int i, j;
    
    scanf("%d %d", &N, &M);
    
    for(i=1; i<=N; i++) {
        scanf("%s", str);
        for(j=1; j<=M; j++) {
            if(str[j-1] - '0' == 0) {
                T1[i][j] = T2[i][j] = 0;
            } else {
                T1[i][j] = T2[i][j] = -1;
            }

        }
    }
    
    //시작과 마지막 정점을 1로 저장해놓는다. -> 마지막 정답에서 -2 필수!!
    T1[1][1] = T2[N][M] = 1;

    //시작정점과 도착정점에서 각 노드로 이동할 수 있는 최소 거리를 구한다
    bfs_f(1, 1);
    bfs_f(N, M);

    
    if(T1[N][M] != 0) { //벽을 부시지 않고 도착정점까지 가는 경우 거리를 알아낸다
        minDist = T1[N][M];
    }
    
    //벽을 부실 때 최단거리를 업데이트 할 수 있는지 알아낸다
    for(i=1; i<=N; i++) {
        for(j=1; j<=M; j++) {
            if(T1[i][j] == -1) {
                //T1의 북쪽 + T2시계방향
                if(i-1 > 0 && T1[i-1][j] > 0) {   //벽 위가 T1이 이동했던 곳이면
                    d1 = T1[i-1][j] + 1;
                    
                    if(j+1 <= M && T2[i][j+1] > 0) {
                        if(minDist > d1 + T2[i][j+1]) {
                            minDist = d1 + T2[i][j+1];
                        }
                    }
                    if(i+1 <= N && T2[i+1][j] > 0) {
                        if(minDist > d1 + T2[i+1][j]) {
                            minDist = d1 + T2[i+1][j];
                        }
                    }
                    if(j-1 > 0 && T2[i][j-1] > 0) {
                        if(minDist > d1 + T2[i][j-1]) {
                            minDist = d1 + T2[i][j-1];
                        }
                    }
                }   //end 벽 위가 T1이 이동했던 곳이면
                if(i+1 <= N && T1[i+1][j] > 0) {  //벽 아래가
                    d1 = T1[i+1][j] + 1;
                    
                    if(j-1 > 0 && T2[i][j-1] > 0) {
                        if(minDist > d1 + T2[i][j-1]) {
                            minDist = d1 + T2[i][j-1];
                        }
                    }
                    if(i-1 > 0 && T2[i-1][j] > 0) {
                        if(minDist > d1 + T2[i-1][j]) {
                            minDist = d1 + T2[i-1][j];
                        }
                    }
                    if(j+1 <= M && T2[i][j+1] > 0) {
                        if(minDist > d1 + T2[i][j+1]) {
                            minDist = d1 + T2[i][j+1];
                        }
                    }
                } //end 벽 아래가
                if(j-1 > 0 && T1[i][j-1] > 0) {   //벽 왼쪽
                    d1 = T1[i][j-1] + 1;
                    
                    if(i-1 > 0 && T2[i-1][j] > 0) {
                        if(minDist > d1 + T2[i-1][j]) {
                            minDist = d1 + T2[i-1][j];
                        }
                    }
                    if(j+1 <= M && T2[i][j+1] > 0) {
                        if(minDist > d1 + T2[i][j+1]) {
                            minDist = d1 + T2[i][j+1];
                        }
                    }
                    if(i+1 <= N && T2[i+1][j] > 0) {
                        if(minDist > d1 + T2[i+1][j]) {
                            minDist = d1 + T2[i+1][j];
                        }
                    }
                }   //end 벽 왼쪽이
                if(j+1 <= M && T1[i][j+1] > 0) {  //벽 오른쪽
                    d1 = T1[i][j+1] + 1;
                    
                    if(i+1 <= N && T2[i+1][j] > 0) {
                        if(minDist > d1 + T2[i+1][j]) {
                            minDist = d1 + T2[i+1][j];
                        }
                    }
                    if(j-1 > 0 && T2[i][j-1] > 0) {
                        if(minDist > d1 + T2[i][j-1]) {
                            minDist = d1 + T2[i][j-1];
                        }
                    }
                    if(i-1 > 0 && T2[i-1][j] > 0) {
                        if(minDist > d1 + T2[i-1][j]) {
                            minDist = d1 + T2[i-1][j];
                        }
                    }
                }   //end 벽오른쪽
            }   //end if(T1[i][j] == -1) {
        }
    }
    
    if(minDist == INF) {    //도착 못할 경우
        printf("-1");
    } else {
        printf("%d", minDist);
    }
    return 0;
}


