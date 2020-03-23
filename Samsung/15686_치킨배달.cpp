//
//  15686_치킨배달.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/23.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
using namespace std;

int N, M;
int chicken[14][2] = {0, }; //치킨집들의 위치 정보를 저장
int visited[14] = {0, };    //M개의 치킨집을 고를 때 사용
int house[102][2] = {0, };  //집들의 위치 정보를 저장
int houseCnt, chickenCnt;   //집과 치킨집의 총 개수
int minDist = 987987987;

void city_dist(void) {
    int houseR, houseC, chickenR, chickenC;
    int distance = 0;   //도시 치킨 거리
    for(int i=0; i<houseCnt; i++) { //모든 집들에 대하여
        int minHouseDist = 987987987;
        houseR = house[i][0];   houseC = house[i][1];
        for(int j=0; j<chickenCnt; j++) {   //선택한 M개의 치킨집에대해
            if(visited[j] == 1) {
                chickenR = chicken[j][0];   chickenC = chicken[j][1];
                int rDist = houseR - chickenR;
                int cDist = houseC - chickenC;
                if(rDist < 0) { rDist *= (-1); }
                if(cDist < 0) { cDist *= (-1); }
                if(minHouseDist > (rDist + cDist)) {
                    minHouseDist = rDist + cDist;
                }
            }
        }
        distance += minHouseDist;
    }
    if(minDist > distance) {    //최소 도시 치킨 거리 업데이트
        minDist = distance;
    }
}

/// M개의 치킨집을 고른다
/// @param cnt 여태까지 고른 치킨 집의 개수
/// @param idx 방문할 치킨 집의 인덱스
void select_chicken(int cnt, int idx) {
    visited[idx] = 1;
    if(cnt+1 == M) { //M개 모두 골랐으면
        city_dist();    //도시의 치킨거리를 구해 최소 도시 치킨 거리를 업데이트한다
    } else {
        for(int i=idx; i<chickenCnt; i++) { //DFS로 완탐
            if(visited[i] == 0) {
                select_chicken(cnt+1, i);
            }
        }
    }
    visited[idx] = 0;
}

int main(void) {
    int num;
    
    houseCnt = chickenCnt = 0;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d", &num);
            if(num == 1) {
                house[houseCnt][0] = i; house[houseCnt][1] = j;
                houseCnt++;
            }
            if(num == 2) {
                chicken[chickenCnt][0] = i; chicken[chickenCnt][1] = j;
                chickenCnt++;
            }
        }
    }
    //도시 치킨 거리 구하기
    for(int i=0; i<chickenCnt; i++) {
        select_chicken(0, i);
    }
    //정답출력
    printf("%d", minDist);
    
    return 0;
}
