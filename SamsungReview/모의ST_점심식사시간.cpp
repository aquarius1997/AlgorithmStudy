//
//  모의ST_점심식사시간.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/27.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef struct PersonNode {
    int row;
    int col;
    int toStair;   //계단입구까지 걸리는 시간
    int endCnt; //계단을 모두 내려가기까지 남은 시간
} PersonNode;

PersonNode g_persons[11];
int g_personStair[11];  //사람들을 어느 계단으로 이동시킬 지 정보를 저장한다
int g_stairs[2][3] = {0, }; //g_stairs[0][0] : 0번 계단의 행위치
int g_personCnt = 0;  //사람들이 몇 명 있는지 저장
int g_N = 0;    //테이블 크기
int g_visited[11] = {0, };
int g_minTime = 987987987;

void go_down(void) {
    vector<int> stair1V;
    vector<int> stair2V;
    int stair1Cnt, stair2Cnt;
    int timeCnt = 1;
    int endCnt = 0; //내려가기를 완료한 사람들의  수
    int idx = 0;
    int i =0;
    int perNum = 0;
    
    while(1) {
        //모두 내려가지 못했으면
        stair1Cnt = stair2Cnt = 0;  //내려가는 사람들의 수
        endCnt = 0; //모두 내려가기를 완료한 사람들의 수
        
        //내려가는 중인 사람들 3명만 -1
        for(idx=0; idx<stair1V.size(); idx++) {
            if(stair1Cnt >= 3) { break; }
            perNum = stair1V[idx];
            g_persons[perNum].endCnt -= 1;
            if(g_persons[perNum].endCnt >= 0) {
                stair1Cnt++;
            } else {
                endCnt++;
            }
        }
        for(idx=0; idx<stair2V.size(); idx++) {
            if(stair2Cnt >= 3) { break; }
            perNum = stair2V[idx];
            g_persons[perNum].endCnt -= 1;
            if(g_persons[perNum].endCnt >= 0) {
                stair2Cnt++;
            } else {
                endCnt++;
            }
        }
        
        //모든 사람이 내려가기를 완료한 경우 루프 나간다
        if(endCnt == g_personCnt) {
            if(g_minTime > timeCnt) {
                g_minTime = timeCnt;
            }
            break;
        }
        
        //입구에 도착한 사람은 해당 계단 벡터에 넣어준다
        for(i=0; i<g_personCnt; i++) {
            if(g_persons[i].toStair == timeCnt) {
                if(g_personStair[i] == 0) {
                    g_persons[i].endCnt = g_stairs[0][2];
                    stair1V.push_back(i);
                } else {
                    g_persons[i].endCnt = g_stairs[1][2];
                    stair2V.push_back(i);
                }
            }
        }


        //시간 증가
        timeCnt++;
    }
    
}

void move_to_stair(int idx, int cnt) {
    int rDist, cDist, dist;
    
    //계단배치 끝나면
    if(cnt == g_personCnt) {
        go_down();
        return;
    }
    
    g_visited[idx] = 1;
    
    g_personStair[idx] = 0;
    //시간 구하기
    rDist = g_stairs[0][0] - g_persons[idx].row;
    cDist = g_stairs[0][1] - g_persons[idx].col;
    if(rDist < 0) { rDist *= -1; }
    if(cDist < 0) { cDist *= -1; }
    dist = rDist + cDist;
    g_persons[idx].toStair = dist;

    move_to_stair(idx+1, cnt+1);
    
    g_personStair[idx] = 1;
    //시간 구하기
    rDist = g_stairs[1][0] - g_persons[idx].row;
    cDist = g_stairs[1][1] - g_persons[idx].col;
    if(rDist < 0) { rDist *= -1; }
    if(cDist < 0) { cDist *= -1; }
    dist = rDist + cDist;
    g_persons[idx].toStair = dist;
    
    move_to_stair(idx+1, cnt+1);
    
    g_visited[idx] = 0;
}

int main(void) {
    int T, t, num;
    int stairCnt = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //테이블 정보 입력받기
        scanf("%d", &g_N);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                scanf("%d", &num);
                if(num == 1) {  //사람이면
                    g_persons[g_personCnt].row = i;
                    g_persons[g_personCnt].col = j;
                    g_personCnt++;
                } else if(num > 1) {    //계단이면
                    g_stairs[stairCnt][0] = i;
                    g_stairs[stairCnt][1] = j;
                    g_stairs[stairCnt][2] = num;
                    stairCnt++;
                }
            }
        }
        
        //사람들을 어떤 계단으로 이동시킬지 경우의 수를 구하는 함수를 호출한다
        move_to_stair(0, 0);
        
        printf("#%d %d\n", t, g_minTime);
    
        
        //초기화
        g_personCnt = 0;
        stairCnt = 0;
        g_minTime = 987987987;
    }
    
    return 0;
}
