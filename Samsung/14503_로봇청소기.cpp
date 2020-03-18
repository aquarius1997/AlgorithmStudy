//
//  14503_로봇청소기.cpp
//  temppp
//
//  Created by 송혜경 on 2020/03/18.
//  Copyright © 2020 송혜경. All rights reserved.
//  35min   **

#include <cstdio>
using namespace std;

typedef struct RobotNode{
    int dir;
}RobotNode;

int N, M;
RobotNode robot;
int cleaned[52][52] = {0, };    //청소한 구역은 1로 변경
int table[52][52] = {0, };
int cnt = 0;

/// 현재 위치에 대해서 청소하고 탐색 진행
/// @param row 현재 위치 행
/// @param col 현재 위치 열
void simul(int row, int col) {
    int temp_dir = robot.dir;   //로봇의 처음 방향
    int next_dir = robot.dir;   //왼쪽으로 회전했을때의 방향
    if(cleaned[row][col] == 0) {    //청소 안한 구역
        cleaned[row][col] = 1;  //청소표시
        cnt++;
    }
    for(int i=0; i<4; i++) {
        next_dir = (next_dir + 3) % 4;  //왼쪽으로 회전했을 경우 방향
        if(next_dir == 0) { //북을 바라보게되면
            if(table[row-1][col] == 0 && cleaned[row-1][col] == 0) {    //벽이 아니고 청소 안돼있으면
                robot.dir = next_dir;   //방향전환
                simul(row-1, col);
                return;
            }
        } else if(next_dir == 1) {  //동쪽 바라보게 되면
            if(table[row][col+1] == 0 && cleaned[row][col+1] == 0) {
                robot.dir = next_dir;
                simul(row, col+1);
                return;
            }
        } else if(next_dir == 2) {  //남쪽 바라보게 되면
            if(table[row+1][col] == 0 && cleaned[row+1][col] == 0) {
                robot.dir = next_dir;
                simul(row+1, col);
                return;
            }
        } else {    //서쪽 바라보게 되면
            if(table[row][col-1] == 0 && cleaned[row][col-1] == 0) {
                robot.dir = next_dir;
                simul(row, col-1);
                return;
            }
        }
        //여기오면 왼쪽방향이 벽이거나 청소가 되어있음을 의미
        robot.dir = next_dir;   //왼쪽 방향을 바라보도록 회전시킨다
    }
    //여기까지 오면 상하좌우를 이미 청소했거나 벽임을 의미
    robot.dir = temp_dir;   //로봇을 원래 방향을 바라보도록 조정한다
    if(robot.dir == 0) {    //북쪽 바라보고 있을 때
        if(table[row+1][col] == 1) {    //후진불가능
            return;
        } else {    //후진 가능
            simul(row+1, col);
        }
    } else if(robot.dir == 1) { //동쪽 바라보고 있을 때
        if(table[row][col-1] == 1) {
            return;
        } else {
            simul(row, col-1);
        }
    } else if(robot.dir == 2) { //남족 바라보고 있을 때
        if(table[row-1][col] == 1) {
            return;
        } else {
            simul(row-1, col);
        }
    } else {    //서쪽 바라볼때
        if(table[row][col+1] == 1) {
            return;
        } else {
            simul(row, col+1);
        }
    }
}

int main(void) {
    int r, c, d;
    
    scanf("%d %d", &N, &M);
    scanf("%d %d %d", &r, &c, &d);
    robot.dir = d;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    simul(r, c);
    
    printf("%d", cnt);
    
    return 0;
}
