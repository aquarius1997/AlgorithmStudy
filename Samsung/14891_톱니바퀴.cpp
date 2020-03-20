//
//  14891_톱니바퀴.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/19.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <cstdio>
using namespace std;

int cogwheel[5][10] = {0, };    //cogwheel[1][1] : 1번째 톱니바퀴의 12시 방향 상태 ( 1: S, 0 : N)

/// 톱니바퀴를 회전시킨다
/// @param cogwheelNum 회전시킬 톱니바퀴 번호
/// @param dir 회전시킬 방향
void rotating(int cogwheelNum, int dir) {
    //시계방향 회전
    if(dir == 1) {
        for(int i=8; i>=1; i--) {
            cogwheel[cogwheelNum][i+1] = cogwheel[cogwheelNum][i];
        }
        cogwheel[cogwheelNum][1] = cogwheel[cogwheelNum][9];
    }
    //반시계 방향 회전
    else {
        for(int i=1; i<=8; i++) {
            cogwheel[cogwheelNum][i-1] = cogwheel[cogwheelNum][i];
        }
        cogwheel[cogwheelNum][8] = cogwheel[cogwheelNum][0];
    }
}


/// 입력받은 톱니바퀴를 회전시키며 다른 톱니바퀴들도 회전하는지 확인한다
/// @param cogwheelNum 회전시킬 바퀴 번호
/// @param dir 회전시킬 방향
void simul(int cogwheelNum, int dir) {
    int direction[5] = {0, };   //0 : 회전안함, 1: 시계, -1 : 반시계
    
    direction[cogwheelNum] = dir;
    //기준 톱니바퀴의 오른쪽 톱니바퀴들 확인
    for(int i=cogwheelNum+1; i<=4; i++) {
        if(cogwheel[i-1][3] != cogwheel[i][7]) {    //i번째 톱니바퀴의 왼쪽과 i-1번째 톱니바퀴의 오른쪽이 다른극
            direction[i] = direction[i-1] * (-1);   //반대 방향으로 회전
        } else {    //중요
            break;
        }
    }
    //기준 톱니바퀴의 왼쪽 톱니바퀴들 확인
    for(int i=cogwheelNum-1; i>=1; i--) {
        if(cogwheel[i][3] != cogwheel[i+1][7]) {    //다른극이면
            direction[i] = direction[i+1] * (-1);
        } else {
            break;
        }
    }
    
    //톱니바퀴 회전하는 것들이 있으면 회전시킨다
    for(int i=1; i<=4; i++) {
        if(direction[i] != 0) {
            rotating(i, direction[i]);
        }
    }
}


int main(void) {
    char str[11];
    int cogwheelNum, dir;
    int cnt = 0;
    int K;
    
    for(int i=1; i<=4; i++) {
        scanf("%s", str);
        for(int j=0; j<8; j++) {
            cogwheel[i][j+1] = (str[j] - '0');
        }
    }

    scanf("%d", &K);

    for(int i=1; i<=K; i++) {   //입력대로 회전시킨다
        scanf("%d %d", &cogwheelNum, &dir);
        simul(cogwheelNum, dir);
    }
    
    int x = 1;
    for(int i=1; i<=4; i++) {
        if(cogwheel[i][1] == 1) {
            cnt += x;
        }
        x *= 2;
    }
    
    printf("%d", cnt);
    
    return 0;
}
