//
//  D5_최적경로.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/19.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
using namespace std;

int N;
int houses[11][2] = {0, };  //houses[i][j] : i는 1~N까지의 인덱스를 사용. 집 번호를 나타냄. j가 0이면 행위치, 1이면 열위치
int company[2] = {0, };
int home[2] = {0,};
int minDist;
int visited[11] = {0, };    //방문한집은 1

void visiting(int preHouse, int idx, int cnt, int dist) {
    int rowDist, colDist;
    int distance;
    
    visited[idx] = 1;
    
    if(preHouse == 0) { //첫번째 집
        rowDist = company[0] - houses[idx][0];
        colDist = company[1] - houses[idx][1];
    } else {
        rowDist = houses[preHouse][0] - houses[idx][0];
        colDist = houses[preHouse][1] - houses[idx][1];
    } 
    if(rowDist < 0) {
        distance = (rowDist * (-1));
    } else {
        distance = rowDist;
    }
    if(colDist < 0) {
        distance += (colDist * (-1));
    } else {
        distance += colDist;
    }
    
    if(cnt >= N) {  //집으로 가고 종료
        rowDist = home[0] - houses[idx][0];
        colDist = home[1] - houses[idx][1];
        if(rowDist < 0) {
            distance += (rowDist * (-1));
        } else {
            distance += rowDist;
        }
        if(colDist < 0) {
            distance += (colDist * (-1));
        } else {
            distance += colDist;
        }
        
        if(distance + dist < minDist) {
            minDist = distance + dist;
        }
    } else {
        for(int i=1; i<=N; i++) {
            if(visited[i] == 0) {
                visiting(idx, i, cnt+1, dist+distance);
            }
        }
    }
    
    visited[idx] = 0;
}

int main(void) {
    int T, t;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d", &N);
        
        scanf("%d %d", &company[0], &company[1]);
        scanf("%d %d", &home[0], &home[1]);
        for(int i=1; i<=N; i++) {
            scanf("%d %d", &houses[i][0], &houses[i][1]);
            
        }
        
        minDist = 987987987;
        
        for(int i=1; i<=N; i++) {
            visiting(0, i, 1, 0);
        }
        
        printf("#%d %d\n", t, minDist);
    }
    
    return 0;
}
