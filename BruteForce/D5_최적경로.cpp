//
//  D5_최적경로.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/19.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
using namespace std;

int N;
int houses[11][2] = {0, };  //houses[i][j] : i는 1~N까지의 인덱스를 사용. 집 번호를 나타냄. j가 0이면 행위치, 1이면 열위치
int company[2] = {0, };
int home[2] = {0,};
int minDist;
int visited[11] = {0, };    //방문한집은 1

/// 모든 경우의 수에 대해 집을 방문한다
/// @param cnt 방문한 집의 수
/// @param idx 확인시작할 인덱스 위치
/// @param dist 여태까지 거리
/// @param preHouse 이전에 방문한 집의 번호
void visiting(int cnt, int idx, int dist, int preHouse) {
    int distance = 0;
    int rowDist, colDist;
        
    if(cnt > N) {
        
    } else {
        visited[idx] = 1;
        
        visited[idx] = 0;
    }

    
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
            visiting(1, i, 0, 0);
        }
        
        
        printf("#%d %d", t, minDist);
    }
    
    return 0;
}
