//
//  모의ST_핀볼게임.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/14.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****** 처음에 재귀로 풀었다가 스택 메모리 초과로 runtimeError뜸.
// 만일 RuntimeError가 뜨고 아무리 살펴봐도 배열 메모리 범위 초과가 없다 싶으면 재귀로 풀 필요가 없음을 살펴보자.

#include <cstdio>
using namespace std;

struct Pinball {
    int row;    //처음 위치
    int col;    //처음 위치
    int dir;    //현재 방향(상:1, 하:-1, 좌:2, 우:-2);
};

int g_table[102][102] = {0,};   //판의 정보 저장
int g_wh[11][2][2] = {0,};
int g_N = 0;
int g_maxCnt = 0;   //최대로 얻을 수 있는 점수 저장
Pinball pinball;

/// 블록 따라 핀볼의 방향을 변환한다
/// @param blockNum 핀볼이 부딪힌 블록의 종류
void changeDir(int blockNum) {
    if(blockNum == 1) {
        if(pinball.dir == 1 || pinball.dir == -2) { //위로 움직이거나 오른쪽으로 움직이던 핀볼은 반대 방향으로 전환
            pinball.dir *= -1;
        } else if(pinball.dir == -1) {  //아래로 움직이던 핀볼은 오른쪽으로 전환
            pinball.dir = -2;
        } else {    //왼쪽으로 움직이던 핀볼은 위로 전환
            pinball.dir = 1;
        }
    } else if(blockNum == 2) {
        if(pinball.dir == -1 || pinball.dir == -2) {    //아래로 움직이거나 오른쪽으로 움직이던 핀볼은 반대 방향으로 전환
            pinball.dir *= -1;
        } else if(pinball.dir == 2) {   //왼쪽으로 움직이던 핀볼은 아래로 전환
            pinball.dir = -1;
        } else {    //위로 움직이던 핀볼은 오른쪽으로 전환
            pinball.dir = -2;
        }
    } else if(blockNum == 3) {
        if(pinball.dir == -1 || pinball.dir == 2) { //아래로 움직이거나 왼쪽으로 움직이던 핀볼은 반대 방향으로 전환
            pinball.dir *= -1;
        } else if(pinball.dir == -2) {  //오른쪽으로 움직이던 핀볼을 아래로 전환
            pinball.dir = -1;
        } else {    //위로 움직이던 핀볼을 왼쪽으로 전환
            pinball.dir = 2;
        }
    } else if(blockNum == 4) {
        if(pinball.dir == 2 || pinball.dir == 1) { //왼쪽으로 움직이거나 위로 움직이던 핀볼은 반대 방향으로 전환
            pinball.dir *= -1;
        } else if(pinball.dir == -1) { //아래로 움직이던 핀볼은 왼쪽으로 전환
            pinball.dir = 2;
        } else { //오른쪽으로 움직이던 핀볼은 위로 전환
            pinball.dir = 1;
        }
    } else {
        //반대 방향으로 전환
        pinball.dir *= -1;
    }
}

/// 핀볼의 방향정보를 바탕으로 핀볼을 움직인다
/// @param row 움직이기 시작할 행의 위치
/// @param col 움직이기 시작할 열의 위치
/// @param score 현재까지의 점수
void movePin(int row, int col, int score) {
    int blockNum = 0;
    int whNum = 0;
    int flag = 0;
    int i, j;
    
    while(1) {
        flag = 0;
        //1. 현재 위치로부터 핀볼 방향으로 움직인다
        if(pinball.dir == 1) {  //위로 움직이는 핀볼
            //1)방향이동
            for(i=row-1; i>=0; i--) {
                if(g_table[i][col] == -1) { //블랙홀
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(i == pinball.row && col == pinball.col) {   //원래 위치
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(g_table[i][col] >=1 && g_table[i][col] <= 5) {    //블록
                    //방향전환
                    blockNum = g_table[i][col];
                    changeDir(blockNum);
                    row = i;
                    score += 1;
                    flag = 1;   break;
                } else if(g_table[i][col] >= 6){    //웜홀
                    //다른 웜홀로 이동
                    whNum = g_table[i][col];
                    //반대편 웜홀 위치 구하기
                    if(g_wh[whNum][0][0] == i && g_wh[whNum][0][1] == col) {
                        row = g_wh[whNum][1][0];
                        col = g_wh[whNum][1][1];
                    } else {
                        row = g_wh[whNum][0][0];
                        col = g_wh[whNum][0][1];
                    }
                    flag = 1;   break;
                }
            }
            //end 1)
            //2) 여기까지 온거면 벽에 부딪히는 거임
            if(flag == 0) {
                pinball.dir *= -1;
                row = -1;
                score += 1;
            }
        } else if(pinball.dir == -1) {  //아래로 움직이는 핀볼
            //1)방향이동
            for(i=row+1; i<g_N; i++) {
                if(g_table[i][col] == -1) { //블랙홀
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(i == pinball.row && col == pinball.col) {   //원래 위치
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(g_table[i][col] >=1 && g_table[i][col] <= 5) {    //블록
                    //방향전환
                    blockNum = g_table[i][col];
                    changeDir(blockNum);
                    row = i;
                    score += 1;
                    flag = 1;   break;
                } else if(g_table[i][col] >= 6){    //웜홀
                    //다른 웜홀로 이동
                    whNum = g_table[i][col];
                    //반대편 웜홀 위치 구하기
                    if(g_wh[whNum][0][0] == i && g_wh[whNum][0][1] == col) {
                        row = g_wh[whNum][1][0];
                        col = g_wh[whNum][1][1];
                    } else {
                        row = g_wh[whNum][0][0];
                        col = g_wh[whNum][0][1];
                    }
                    flag = 1;   break;
                }
            }
            //end 1)
            //2) 여기까지 온거면 벽에 부딪히는 거임
            if(flag == 0) {
                pinball.dir *= -1;
                row = g_N;
                score += 1;
            }
        } else if(pinball.dir == 2) {   //왼쪽으로 움직이는 핀볼
            //1)방향이동
            for(j=col-1; j>=0; j--) {
                if(g_table[row][j] == -1) { //블랙홀
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(row == pinball.row && j == pinball.col) {   //원래 위치
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(g_table[row][j] >=1 && g_table[row][j] <= 5) {    //블록
                    //방향전환
                    blockNum = g_table[row][j];
                    changeDir(blockNum);
                    col = j;
                    score += 1;
                    flag = 1;   break;
                } else if(g_table[row][j] >= 6){    //웜홀
                    //다른 웜홀로 이동
                    whNum = g_table[row][j];
                    //반대편 웜홀 위치 구하기
                    if(g_wh[whNum][0][0] == row && g_wh[whNum][0][1] == j) {
                        row = g_wh[whNum][1][0];
                        col = g_wh[whNum][1][1];
                    } else {
                        row = g_wh[whNum][0][0];
                        col = g_wh[whNum][0][1];
                    }
                    flag = 1;   break;
                }
            }
            //end 1)
            //2) 여기까지 온거면 벽에 부딪히는 거임
            if(flag == 0 ){
                pinball.dir *= -1;
                col = -1;
                score += 1;
            }
            //end 2)
        } else {    //오른쪽으로 움직이는 핀볼
            //1)방향이동
            for(j=col+1; j<g_N; j++) {
                if(g_table[row][j] == -1) { //블랙홀
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(row == pinball.row && j == pinball.col) {   //원래 위치
                    if(score > g_maxCnt) {
                        g_maxCnt = score;
                    }
                    return;
                } else if(g_table[row][j] >=1 && g_table[row][j] <= 5) {    //블록
                    //방향전환
                    blockNum = g_table[row][j];
                    changeDir(blockNum);
                    col = j;
                    score += 1;
                    flag = 1;   break;
                } else if(g_table[row][j] >= 6){    //웜홀
                    //다른 웜홀로 이동
                    whNum = g_table[row][j];
                    //반대편 웜홀 위치 구하기
                    if(g_wh[whNum][0][0] == row && g_wh[whNum][0][1] == j) {
                        row = g_wh[whNum][1][0];
                        col = g_wh[whNum][1][1];
                    } else {
                        row = g_wh[whNum][0][0];
                        col = g_wh[whNum][0][1];
                    }
                    flag = 1;   break;
                }
            }
            //end 1)
            //2) 여기까지 온거면 벽에 부딪히는 거임
            if(flag == 0) {
                pinball.dir *= -1;
                col = g_N;
                score += 1;
            }
        }
        //end 1
    }
}

int main(void) {
    int T, t;
    int whNum;
    int i, j, k;

        
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //initialize
        for(i=0; i<102; i++) {
            for(j=0; j<102; j++) {
                g_table[i][j] = 0;
            }
        }
        for(i=0; i<11; i++) {
            for(j=0; j<2; j++) {
                for(k=0; k<2; k++) {
                    g_wh[i][j][k] = -1; //정보 저장 안되어있으면 -1
                }
            }
        }
        g_maxCnt = 0;
        //end initialize
        
        //입력
        scanf("%d", &g_N);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                scanf("%d", &g_table[i][j]);
                //웜홀이면 웜홀 정보 저장
                if(g_table[i][j] >= 6) {
                    whNum = g_table[i][j];  //웜홀 번호
                    if(g_wh[whNum][0][0] == -1) {   //쌍의 첫번째
                        g_wh[whNum][0][0] = i;
                        g_wh[whNum][0][1] = j;
                    } else {    //쌍의 두번째
                        g_wh[whNum][1][0] = i;
                        g_wh[whNum][1][1] = j;
                    }
                }
            }
        }
        //end 입력
        
        //1.모든 자리에 대해 핀볼게임을 수행해서 최대 점수를 알아낸다
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                if(g_table[i][j] == 0) {    //빈칸
                    //핀볼 위치 정보 초기화
                    pinball.row = i;
                    pinball.col = j;
                    //상하좌우 정보 초기화하고 움직인다
                    pinball.dir = 1;
                    movePin(i, j, 0);
                    pinball.dir = -1;
                    movePin(i, j, 0);
                    pinball.dir = 2;
                    movePin(i, j, 0);
                    pinball.dir = -2;
                    movePin(i, j, 0);
                }
            }
        }
        //end 1
        
        //2. 정답출력
        printf("#%d %d\n", t, g_maxCnt);
    }
    
    return 0;
}
