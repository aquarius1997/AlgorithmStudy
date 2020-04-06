//
//  17822_원판돌리기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/06.
//  Copyright © 2020 송혜경. All rights reserved.
//  난이도 자체는 안높은데 예외처리 너무 대충해서 3번이나 틀리고 오래 잡아먹음 **** 2h

#include <cstdio>
#include <queue>
using namespace std;

int g_layer[52][53] = {0, };  //layer[i][j] : i번째 판의 j번째 숫자
int g_remove_layer[52][53]= {0, };  //지울 숫자들의 위치를 1로 저장
int g_N = 0;    //원판 수
int g_M = 0;    //숫자 수

/// 특정 판을 회전시킨다
/// @param layerNum 회전시킬 판의 번호
/// @param direc 회전시킬 방향
/// @param rotateCnt 회전시킬 칸의 수
void rotate_layer(int layerNum, int direc, int rotateCnt) {
    int temp[53] = {0, };   //회전시킨 정보
    int i;
    
    if(direc == 0) {    //시계방향
        for(i=1; i<=g_M; i++) {
            if(i+rotateCnt > g_M) {
                temp[i+rotateCnt-g_M] = g_layer[layerNum][i];
            } else {
                temp[i+rotateCnt] = g_layer[layerNum][i];
            }
        }
        for(i=1; i<=g_M; i++) {
            g_layer[layerNum][i] = temp[i];
        }
    } else {    //반시계방향
        for(i=1; i<=g_M; i++) {
            if(i-rotateCnt <= 0) {
                temp[(i-rotateCnt+g_M)] = g_layer[layerNum][i];
            } else {
                temp[i-rotateCnt] = g_layer[layerNum][i];
            }
        }
        for(i=1; i<=g_M; i++) {
            g_layer[layerNum][i] = temp[i];
        }
    }
    //end 회전
}

/// 원판을 회전시키고 인접한 수를 지운다
/// @param layerNum 입력으로 받은 xi
/// @param direc 회전 방향 (0 : 시계, 1: 반시계)
/// @param rotateCnt 회전시킬 칸의 수
void simul(int layerNum, int direc, int rotateCnt) {
    double ave = 0.0;    //남은 숫자의 평균
    int sum = 0;    //원판의 숫자들의 총 합
    int cnt = 0;    //원판 숫자들의 개수
    int removeCnt = 0;  //지운 숫자 개수
    int i, j;
    
    //회전시킬 판을 알아내서 회전시킨다
    for(i=1; i<=g_N; i++) {
        if(i % layerNum == 0) {
            rotate_layer(i, direc, rotateCnt);
        }
    }
    
    //인접한 수끼리 비교하며 지울것들을 알아낸다
    for(i=1; i<=g_N; i++) {
        for(j=1; j<=g_M; j++) {
            if(g_layer[i][j] != -1) {   //지워진 숫자가 아니면
                //남은 숫자의 개수 카운팅 + 숫자 누적
                cnt++;
                sum += g_layer[i][j];
                
                //하나의 판 이내의 인접한 숫자 비교
                if(j == g_M) {
                    if(g_layer[i][j] == g_layer[i][1]) {
                        g_remove_layer[i][j] = g_remove_layer[i][1] = 1;
                        removeCnt++;
                    }
                    if(g_layer[i][j-1] == g_layer[i][j]) {
                        g_remove_layer[i][j] = g_remove_layer[i][j-1] = 1;
                        removeCnt++;
                    }
                } else if(j == 1) {
                    if(g_layer[i][j] == g_layer[i][g_M]) {
                        g_remove_layer[i][j] = g_remove_layer[i][g_M] = 1;
                        removeCnt++;
                    }
                    if(g_layer[i][j] == g_layer[i][j+1]) {
                        g_remove_layer[i][j] = g_remove_layer[i][j+1] = 1;
                        removeCnt++;
                    }
                } else {
                    if(g_layer[i][j] == g_layer[i][j+1]) {
                        g_remove_layer[i][j] = g_remove_layer[i][j+1] = 1;
                        removeCnt++;
                    }
                    if(g_layer[i][j] == g_layer[i][j-1]) {
                        g_remove_layer[i][j] = g_remove_layer[i][j-1] = 1;
                        removeCnt++;
                    }
                }
                
                //다음 판과 인접한 숫자 비교
                if(i < g_N) {
                    if(g_layer[i][j] == g_layer[i+1][j]) {
                        g_remove_layer[i][j] = g_remove_layer[i+1][j] = 1;
                        removeCnt++;
                    }
                }
            }
        }
    }
    
    //지운 정보를 업데이트
    if(removeCnt > 0) {
        for(i=1; i<=g_N; i++) {
            for(j=1; j<=g_M; j++) {
                if(g_remove_layer[i][j] == 1) { //지울 숫자
                    g_layer[i][j] = -1; //지우기
                    g_remove_layer[i][j] = 0;   //초기화
                }
            }
        }
    } else if(cnt > 0){    //지울 숫자가 없을경우
        //평균구하기
        ave = (double)sum / (double)cnt;
        for(i=1; i<=g_N; i++) {
            for(j=1; j<=g_M; j++) {
                if(g_layer[i][j] != -1) {   //지워진 숫자가 아닌것에 대해
                    if(g_layer[i][j] > ave) {   //평균보다 크면 -1
                        g_layer[i][j] -= 1;
                    } else if(g_layer[i][j] < ave){    //작으면 +1
                        g_layer[i][j] += 1;
                    }
                }
            }
        }
    }
    
}

int main(void) {
    int sum = 0;
    int T, x, d, k;
    int i, j;
    
    scanf("%d %d %d", &g_N, &g_M, &T);
    //원판 정보 입력받기
    for(i=1; i<=g_N; i++) {
        for(j=1; j<=g_M; j++) {
            scanf("%d", &g_layer[i][j]);
        }
    }
    //T개만큼 회전
    for(i=1; i<=T; i++) {
        scanf("%d %d %d", &x, &d, &k);
        simul(x, d, k);
    }
    
//    //원판에 적힌 숫자들의 총 합 구하기
//    for(i=1; i<=g_N; i++) {
//        for(j=1; j<=g_M; j++) {
//            if(g_layer[i][j] != -1) {
//                sum += g_layer[i][j];
//            }
//        }
//    }
    
    //정답 출력
    printf("%d", sum);
    
    return 0;
}
