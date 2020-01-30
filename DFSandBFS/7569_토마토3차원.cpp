//
//  7569_토마토3차원.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/30.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
#include <queue>

using namespace std;

int tomato[102][102][102] = {0, };
int totalCnt = 0;   //입력으로 받은 토마토의 총 개수
int N, M, H;
queue<int> Queue;

/// 더 많은 토마토를 익힌다.
void bfsF(void) {
    int m, n, h, d;
        
    while(!Queue.empty()) { //익어있는 토마토의 위치정보를 알아내서 상하좌우위아래 익힌다
        h = Queue.front();  Queue.pop();
        n = Queue.front();  Queue.pop();
        m = Queue.front();  Queue.pop();
        d = tomato[h][n][m] + 1;
        
        //인접한 익지 않은 토마토는 익히고, tempQeueu에 정보를 삽입한다
        if(tomato[h][n-1][m] == 0 && n-1 >= 1) {
            tomato[h][n-1][m] = d;
            Queue.push(h);  Queue.push(n-1);    Queue.push(m);
        }
        if(tomato[h][n+1][m] == 0 && n+1 <= N) {
            tomato[h][n+1][m] = d;
            Queue.push(h);  Queue.push(n+1);    Queue.push(m);
        }
        if(tomato[h][n][m-1] == 0 && m-1 >= 1) {
            tomato[h][n][m-1] = d;
            Queue.push(h);  Queue.push(n);  Queue.push(m-1);
        }
        if(tomato[h][n][m+1] == 0 && m+1 <= M) {
            tomato[h][n][m+1] = d;
            Queue.push(h);  Queue.push(n);  Queue.push(m+1);
        }
        if(tomato[h-1][n][m] == 0 && h-1 >= 1) {
            tomato[h-1][n][m] = d;
            Queue.push(h-1);    Queue.push(n);  Queue.push(m);
        }
        if(tomato[h+1][n][m] == 0 && h+1 <= H) {
            tomato[h+1][n][m] = d;
            Queue.push(h+1);    Queue.push(n);  Queue.push(m);
        }
    }   //end for(//익어있는 토마토의 위치정보를 알아내서 상하좌우위아래 익힌다)
    
}

int main(void) {
    int mday = 0;
    int result = 0;
    int i, j, k;
    
    
    scanf("%d %d %d", &M, &N, &H);
    
    for(i=1; i<=H; i++) {
        for(j=1; j<=N; j++) {
            for(k=1; k<=M; k++) {
                scanf("%d", &tomato[i][j][k]);
                
                if(tomato[i][j][k] == 1) {  //익은 토마토면 큐에 삽입
                    Queue.push(i);  Queue.push(j);  Queue.push(k);
                }
                
            }
        }
    }
        
    bfsF();
    
    for(i=1; i<=H; i++) {
        for(j=1; j<=N; j++) {
            for(k=1; k<=M; k++) {
                if(tomato[i][j][k] == 0){//안 익은 토마토가 있으면
                    result = -1;
                } else if(tomato[i][j][k] > mday) {
                    mday = tomato[i][j][k];
                }
            }
        }
    }
    
    if(result != -1) {
        result = mday-1;
    }
    
    printf("%d", result);
    
    return 0;
}
