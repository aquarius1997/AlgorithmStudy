//
//  모의ST_홈방범서비스.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/28.
//  Copyright © 2020 송혜경. All rights reserved.
//  28min. Fail : 0 **

#include <cstdio>
using namespace std;

typedef struct HouseType {
    int row;
    int col;
}HouseType;

HouseType g_houses[410];
int g_houseNum = 0;   //집들의 수
int g_M = 0;

int simul(int N) {
    int maxCnt = 0;
    int houseCnt = 0;
    int K;
    int rDist, cDist, dist;
    int r, c, i;
    int provideValue = 0;
    int profit = 0;
    
    //홈 방범 서비스의 면적을 증가시키며 확인
    for(K=1; K<=N+2; K++) {
        //운영비용
        provideValue = (K*K) + ((K-1) * (K-1));
        //방범 서비스의 중심을 이동시키며 확인
        for(r=0; r<N; r++) {
            for(c=0; c<N; c++) {
                houseCnt = 0;
                //모든 집들에 대해 구역 안에 있는지 확인
                for(i=0; i<g_houseNum; i++) {
                    //거리 차이 구하고
                    rDist = r - g_houses[i].row;
                    cDist = c - g_houses[i].col;
                    if(rDist < 0) { rDist *= -1;}
                    if(cDist < 0) { cDist *= -1;}
                    dist = rDist + cDist;
                    
                    if(dist < K) {  //구역 안에 있으면 카운팅
                        houseCnt++;
                    }
                } //모든 집들에 대해 구역 안에 있는지 확인
                //손해를 안보면 최대 제공 집들 수로 업데이트
                profit = (g_M * houseCnt) - provideValue;
                if(profit >= 0) {
                    if(maxCnt < houseCnt) { maxCnt = houseCnt; }
                }
            }
        }//방범 서비스의 중심을 이동시키며 확인
    }//홈 방범 서비스의 면적을 증가시키며 확인
    
    return maxCnt;
}


int main(void) {
    int t, T, num, N;
    int answer = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d", &N, &g_M);
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &num);
                //집 -> 정보 저장
                if(num == 1) {
                    g_houses[g_houseNum].row = i;
                    g_houses[g_houseNum].col = j;
                    g_houseNum++;
                }
            }
        }
        
        //함수 호출
        answer = simul(N);
        
        // 정답 출력
        printf("#%d %d\n", t, answer);
        
        //초기화
        g_houseNum = 0;
    }
    
    return 0;
}
