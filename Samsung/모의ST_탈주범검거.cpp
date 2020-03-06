//
//  모의ST_탈주범검거.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/02.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <cstdio>
#include <queue>
using namespace std;

int visited[51][51] = {0, };    //갔던 위치면 1
int table[51][51] = {0, };
queue<int> Queue;   //BFS사용
int cnt = 0;    //도둑이 있을 수 있는 위치의 갯수
int L;  //경과시간
int N, M;   //테이블 세로, 가로 크기

/// 입력으로 받은 위치로부터 다음 진행 가능한 방향을 알아내 이동시킨다
/// @param row time-1 시간에 도둑이 있는 행위치
/// @param col time-1 시간에 도둑이 있는 열 위치
/// @param time 이동한 위치에 있을 시간
void bfs_visit(int row, int col, int time) {
    int tun_type;   //time-1시간에 도둑이있던 터널의 유형
    
    tun_type = table[row][col];
    
    if(tun_type == 1) { //상하좌우로 이동
        if(row - 1 >= 0) {  //테이블 크기 안벗어나고
            if(table[row-1][col] == 1 || table[row-1][col] == 2 || table[row-1][col] == 5 || table[row-1][col] == 6) {    //연결되어있는 터널이면
                if(visited[row-1][col] == 0) { //방문하지 않은 터널이 있으면
                    cnt++;
                    Queue.push(row-1);  Queue.push(col);    Queue.push(time);
                    visited[row-1][col] = 1;
                }
            }
        }
        if(row + 1 < N) {   //하
            if(table[row+1][col] == 1 || table[row+1][col] == 2 || table[row+1][col] == 4 || table[row+1][col] == 7) {
                if(visited[row+1][col] == 0) {
                    cnt++;
                    Queue.push(row+1);  Queue.push(col);    Queue.push(time);
                    visited[row+1][col] = 1;
                }
            }
        }
        if(col - 1 >= 0) {  //좌
            if(table[row][col-1] == 1 || table[row][col-1] == 3 || table[row][col-1] ==4 || table[row][col-1] == 5) {
                if(visited[row][col-1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col-1);  Queue.push(time);
                    visited[row][col-1] = 1;
                }
            }
        }
        if(col + 1 < M) {   //우
            if(table[row][col+1] == 1 || table[row][col+1] == 3 || table[row][col+1] == 6 || table[row][col+1] == 7) {
                if(visited[row][col+1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col+1);  Queue.push(time);
                    visited[row][col+1] = 1;
                }
            }
        }
    } else if(tun_type == 2) {  //상하
        if(row - 1 >= 0) {  //테이블 크기 안벗어나고
            if(table[row-1][col] == 1 || table[row-1][col] == 2 || table[row-1][col] == 5 || table[row-1][col] == 6) {    //연결되어있는 터널이면
                if(visited[row-1][col] == 0) { //방문하지 않은 터널이 있으면
                    cnt++;
                    Queue.push(row-1);  Queue.push(col);    Queue.push(time);
                    visited[row-1][col] = 1;
                }
            }
        }
        if(row + 1 < N) {   //하
            if(table[row+1][col] == 1 || table[row+1][col] == 2 || table[row+1][col] == 4 || table[row+1][col] == 7) {
                if(visited[row+1][col] == 0) {
                    cnt++;
                    Queue.push(row+1);  Queue.push(col);    Queue.push(time);
                    visited[row+1][col] = 1;
                }
            }
        }
    } else if(tun_type == 3) {  //좌우
        if(col - 1 >= 0) {  //좌
            if(table[row][col-1] == 1 || table[row][col-1] == 3 || table[row][col-1] ==4 || table[row][col-1] == 5) {
                if(visited[row][col-1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col-1);  Queue.push(time);
                    visited[row][col-1] = 1;
                }
            }
        }
        if(col + 1 < M) {   //우
            if(table[row][col+1] == 1 || table[row][col+1] == 3 || table[row][col+1] == 6 || table[row][col+1] == 7) {
                if(visited[row][col+1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col+1);  Queue.push(time);
                    visited[row][col+1] = 1;
                }
            }
        }
    } else if(tun_type == 4) {  //상, 우
        if(row - 1 >= 0) {  //테이블 크기 안벗어나고
            if(table[row-1][col] == 1 || table[row-1][col] == 2 || table[row-1][col] == 5 || table[row-1][col] == 6) {    //연결되어있는 터널이면
                if(visited[row-1][col] == 0) { //방문하지 않은 터널이 있으면
                    cnt++;
                    Queue.push(row-1);  Queue.push(col);    Queue.push(time);
                    visited[row-1][col] = 1;
                }
            }
        }
        if(col + 1 < M) {   //우
            if(table[row][col+1] == 1 || table[row][col+1] == 3 || table[row][col+1] == 6 || table[row][col+1] == 7) {
                if(visited[row][col+1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col+1);  Queue.push(time);
                    visited[row][col+1] = 1;
                }
            }
        }
    } else if(tun_type == 5) {  //하, 우
        if(row + 1 < N) {   //하
            if(table[row+1][col] == 1 || table[row+1][col] == 2 || table[row+1][col] == 4 || table[row+1][col] == 7) {
                if(visited[row+1][col] == 0) {
                    cnt++;
                    Queue.push(row+1);  Queue.push(col);    Queue.push(time);
                    visited[row+1][col] = 1;
                }
            }
        }
        if(col + 1 < M) {   //우
            if(table[row][col+1] == 1 || table[row][col+1] == 3 || table[row][col+1] == 6 || table[row][col+1] == 7) {
                if(visited[row][col+1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col+1);  Queue.push(time);
                    visited[row][col+1] = 1;
                }
            }
        }
    } else if(tun_type == 6) {  //하, 좌
        if(row + 1 < N) {   //하
            if(table[row+1][col] == 1 || table[row+1][col] == 2 || table[row+1][col] == 4 || table[row+1][col] == 7) {
                if(visited[row+1][col] == 0) {
                    cnt++;
                    Queue.push(row+1);  Queue.push(col);    Queue.push(time);
                    visited[row+1][col] = 1;
                }
            }
        }
        if(col - 1 >= 0) {  //좌
            if(table[row][col-1] == 1 || table[row][col-1] == 3 || table[row][col-1] ==4 || table[row][col-1] == 5) {
                if(visited[row][col-1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col-1);  Queue.push(time);
                    visited[row][col-1] = 1;
                }
            }
        }
    } else if(tun_type == 7) {  //상, 좌
        if(row - 1 >= 0) {  //테이블 크기 안벗어나고
            if(table[row-1][col] == 1 || table[row-1][col] == 2 || table[row-1][col] == 5 || table[row-1][col] == 6) {    //연결되어있는 터널이면
                if(visited[row-1][col] == 0) { //방문하지 않은 터널이 있으면
                    cnt++;
                    Queue.push(row-1);  Queue.push(col);    Queue.push(time);
                    visited[row-1][col] = 1;
                }
            }
        }
        if(col - 1 >= 0) {  //좌
            if(table[row][col-1] == 1 || table[row][col-1] == 3 || table[row][col-1] ==4 || table[row][col-1] == 5) {
                if(visited[row][col-1] == 0) {
                    cnt++;
                    Queue.push(row);    Queue.push(col-1);  Queue.push(time);
                    visited[row][col-1] = 1;
                }
            }
        }
    } else {}
    
}

/// 맨홀 위치를 입력으로 받아서 경과시간동안 어디로 이동할 수 있는지 알아낸다
/// @param R 맨홀 행위치
/// @param C 맨홀 열위치
void bfs_function(int R, int C) {
    int row, col, time;
    
    Queue.push(R);
    Queue.push(C);
    Queue.push(1);  //처음에 시간 1
    visited[R][C] = 1;
    cnt++;
    
    while(!Queue.empty()) {
        row = Queue.front();    Queue.pop();
        col = Queue.front();    Queue.pop();
        time = Queue.front();   Queue.pop();
        time += 1;  //1시간 지난 후
        
        if(time > L) {  //경과시간보다 더 지난경우는 체크안함
            break;
        }
    
        bfs_visit(row, col, time);
    }
    
}

int main(void) {
    int T, t, R, C;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
        
        for(i=0; i<N; i++) {
            for(j=0; j<M; j++) {
                scanf("%d", &table[i][j]);
            }
        }
        
        //함수호출
        bfs_function(R, C);
        
        //정답
        printf("#%d %d\n", t, cnt);
        
        //초기화
        cnt = 0;
        while(!Queue.empty()) {
            Queue.pop();
        }
        for(i=0; i<51; i++) {
            for(j=0; j<51; j++) {
                visited[i][j] = 0;
            }
        }
    }
    
    return 0;
}
