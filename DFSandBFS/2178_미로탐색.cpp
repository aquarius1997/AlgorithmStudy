//
//  2178_미로탐색.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/30.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int T[102][102] = {0, };
int visited[102][102] = {0, };

void find_min_dist(void) {
    queue<int> Queue;
    int r, c, d;
    
    //시작점은 고정
    Queue.push(1);  Queue.push(1);
    
    while(!Queue.empty()) { //큐가 빌 때까지 반복
        r = Queue.front();  Queue.pop();
        c = Queue.front();  Queue.pop();
        d = T[r][c] + 1;
        visited[r][c] = 1;
        
        //상하좌우 더 빠르게 이동 할 수 있는지 확인한다
        if(r-1 > 0 && (T[r-1][c] == 1 || T[r-1][c] > d) && visited[r-1][c] == 0) {
            T[r-1][c] = d;
            Queue.push(r-1);    Queue.push(c);
        }
        if(r+1 <= N && (T[r+1][c] == 1 || T[r+1][c] > d) && visited[r+1][c] == 0) {
            T[r+1][c] = d;
            Queue.push(r+1);    Queue.push(c);
        }
        if(c-1 > 0 && (T[r][c-1] == 1 || T[r][c-1] > d) && visited[r][c-1] == 0) {
            T[r][c-1] = d;
            Queue.push(r);  Queue.push(c-1);
        }
        if(c+1 <= M && (T[r][c+1] == 1 || T[r][c+1] > d) && visited[r][c+1] == 0) {
            T[r][c+1] = d;
            Queue.push(r);  Queue.push(c+1);
        }
        
        if(r == 1 && c == 1) {
            T[r][c] = 1;
        }
    }
    
}

int main(void) {
    char str[103];
    int i, j;
    
    scanf("%d %d", &N, &M);
    
    for(i=1; i<=N; i++) {
        scanf("%s", str);
        for(j=1; j<=M; j++) {
            if(str[j-1] - '0' == 0) {
                T[i][j] = 0;
            } else {
                T[i][j] = 1;
            }
        }
    }
    

    find_min_dist();


    printf("%d", T[N][M]);
    
    return 0;
    
}
