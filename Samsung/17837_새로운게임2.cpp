//
//  17837_새로운게임2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/05.
//  Copyright © 2020 송혜경. All rights reserved.
//  1h 31min    *****

#include <cstdio>
using namespace std;

typedef struct Horse {
    int row;
    int col;
    int dir;
}Horse;

int g_color[14][14] = {0, };    //색 저장
int g_table[14][14][22] = {0, };    //체스판에 올려진 말들의 정보 저장
int g_idx[14][14] = {0, }; //체스판에 올려진 말들의 개수를 저장
Horse g_horses[12] = {0, };   //말
int g_N = 0;
int g_K = 0;
int g_result = -1;   //정답 저장

/// 말을 하얀 칸으로 이동시킨다
/// @param horseNum 움직이려는 말의 번호
void move_to_white(int horseNum) {
    int row, col, dir;
    int num = 0;
    int i, j;
    
    row = g_horses[horseNum].row;
    col = g_horses[horseNum].col;
    dir = g_horses[horseNum].dir;
    
    //이동하려는 방향 알아내기
    if(dir == 1) {  //오른쪽 이동
        //이동하려는 말 위에 있는 모든 말들을 같이 이동시킨다
        for(i=0; i<g_idx[row][col]; i++) {
            if(g_table[row][col][i] == horseNum) {
                for(j=i; j<g_idx[row][col]; j++) {  //현재 말과 위의 모든 말을 같이 이동
                    num = g_table[row][col][j];
                    g_table[row][col+1][(g_idx[row][col+1])] = num;
                    g_horses[num].col = col+1;    //말 정보 모두 업데이트
                    g_idx[row][col+1] += 1;
                }
                //원래 자리의 개수 업데이트
                g_idx[row][col] = i;
                break;
            }
        }

    } else if(dir == 2) {   //왼쪽이동
        for(i=0; i<g_idx[row][col]; i++) {
            if(g_table[row][col][i] == horseNum) {  //이동시킬 말 번호부터
                for(j=i; j<g_idx[row][col]; j++) {  //위의 말까지 같이 이동
                    num = g_table[row][col][j];
                    g_table[row][col-1][(g_idx[row][col-1])] = num;
                    g_horses[num].col = col-1;    //말 정보 모두 업데이트
                    g_idx[row][col-1] += 1;
                }
                //원래 자리 개수 업데이트
                g_idx[row][col] = i;
            }
        }
    } else if(dir == 3) { //위로이동
        for(i=0; i<g_idx[row][col]; i++) {
            if(g_table[row][col][i] == horseNum) {  //이동시킬 말 번호부터
                for(j=i; j<g_idx[row][col]; j++) {  //위의 말까지 같이 이동
                    num = g_table[row][col][j];
                    g_table[row-1][col][(g_idx[row-1][col])] = num;
                    g_horses[num].row = row-1;    //말 정보 모두 업데이트
                    g_idx[row-1][col] += 1;
                }
                //원래 자리 개수 업데이트
                g_idx[row][col] = i;
            }
        }
    } else { //아래로이동
        for(i=0; i<g_idx[row][col]; i++) {
            if(g_table[row][col][i] == horseNum) {  //이동시킬 말 번호부터
                for(j=i; j<g_idx[row][col]; j++) {  //위의 말까지 같이 이동
                    num = g_table[row][col][j];
                    g_table[row+1][col][(g_idx[row+1][col])] = num;
                    g_horses[num].row = row+1; //말 정보 업데이트
                    g_idx[row+1][col] += 1;
                }
                //원래 자리 개수 업데이트
                g_idx[row][col] = i;
            }
        }
    }
}

/// 말을 빨간 칸으로 이동시킨다
/// @param horseNum 움직이려는 말의 번호
void move_to_red(int horseNum) {
    int row, col, dir;
    int num;
    int i;
    
    row = g_horses[horseNum].row;
    col = g_horses[horseNum].col;
    dir = g_horses[horseNum].dir;
    
    if(dir == 1) {  //오른쪽이동
        for(i=g_idx[row][col]-1; i>=0; i--) { //맨 위의 말부터 원래 이동시킬 말까지 이동
            num = g_table[row][col][i];
            if(num == horseNum) {  //원래 이동시킬 말까지만
                g_table[row][col+1][(g_idx[row][col+1])] = num;
                g_idx[row][col+1] += 1;
                g_idx[row][col] = i;    //원래 자리 개수 변경
                //말 정보 업데이트
                g_horses[num].col = col+1;
                break;
            } else {
                g_table[row][col+1][(g_idx[row][col+1])] = num;
                g_idx[row][col+1] += 1;
                //말 정보 업데이트
                g_horses[num].col = col+1;
            }
        }
    } else if(dir == 2) { //왼쪽이동
        for(i=g_idx[row][col]-1; i>=0; i--) { //맨 위의 말부터 원래 이동시킬 말까지 이동
            num = g_table[row][col][i];
            if(num == horseNum) {  //원래 이동시킬 말까지만
                g_table[row][col-1][(g_idx[row][col-1])] = num;
                g_idx[row][col-1] += 1;
                g_idx[row][col] = i;    //원래 자리 개수 변경
                //말 정보 업데이트
                g_horses[num].col = col-1;
                break;
            } else {
                g_table[row][col-1][(g_idx[row][col-1])] = num;
                g_idx[row][col-1] += 1;
                //말 정보 업데이트
                g_horses[num].col = col-1;
            }
        }
    } else if(dir == 3) { //위로이동
        for(i=g_idx[row][col]-1; i>=0; i--) { //맨 위의 말부터 원래 이동시킬 말까지 이동
            num = g_table[row][col][i];
            if(num == horseNum) {  //원래 이동시킬 말까지만
                g_table[row-1][col][(g_idx[row-1][col])] = num;
                g_idx[row-1][col] += 1;
                g_idx[row][col] = i;    //원래 자리 개수 변경
                //말 정보 업데이트
                g_horses[num].row = row-1;
                break;
            } else {
                g_table[row-1][col][(g_idx[row-1][col])] = num;
                g_idx[row-1][col] += 1;
                //말 정보 업데이트
                g_horses[num].row = row-1;
            }
        }

    } else { //아래로 이동
        for(i=g_idx[row][col]-1; i>=0; i--) { //맨 위의 말부터 원래 이동시킬 말까지 이동
            num = g_table[row][col][i];
            if(num == horseNum) {  //원래 이동시킬 말까지만
                g_table[row+1][col][(g_idx[row+1][col])] = num;
                g_idx[row+1][col] += 1;
                g_idx[row][col] = i;    //원래 자리 개수 변경
                //말 정보 업데이트
                g_horses[num].row = row+1;
                break;
            } else {
                g_table[row+1][col][(g_idx[row+1][col])] = num;
                g_idx[row+1][col] += 1;
                //말 정보 업데이트
                g_horses[num].row = row+1;
            }
        }
    }
}

/// 체스판들의 말을 이동시킨다
/// @param roundCnt 현재까지의 라운드 수
void simul(int roundCnt) {
    int row, col, dir;
    int i;
    
    if(roundCnt > 1000) { return; }
    
    //1번말부터 K번말에 대해 수행
    for(i=1; i<=g_K; i++) {
        //원래 위치와 방향을 알아낸다
        row = g_horses[i].row;
        col = g_horses[i].col;
        dir = g_horses[i].dir;
        
        //이동할 위치에 따라
        if(dir == 1) {  //오른쪽이동
            if(col+1 > g_N || g_color[row][col+1] == 2) { //이동할 위치가 범위를 벗어나거나 파란색이면
                //이동방향 반대로하고
                g_horses[i].dir = 2;
                if(!(col-1 < 1 || g_color[row][col-1] == 2)) { //이동할 위치가 범위를 벗어나거나 파란색이 아니면
                    //이동할 위치의 색에 따라 이동시킨다
                    if(g_color[row][col-1] == 0) {
                        move_to_white(i);
                    } else {
                        move_to_red(i);
                    }
                    if(g_idx[row][col-1] >= 4) {    //이동한 위치가 4개 이상되면 종료
                        g_result = roundCnt;    return;
                    }
                }
            } else {    //이동할 위치가 빨간색이나 흰색이면
                //이동시키고
                if(g_color[row][col+1] == 0) {
                    move_to_white(i);
                } else {
                    move_to_red(i);
                }
                //개수확인
                if(g_idx[row][col+1] >= 4) {
                    g_result = roundCnt; return;
                }
            }
        } else if(dir == 2) {   //왼쪽이동
            if(col-1 < 1 || g_color[row][col-1] == 2) { //이동할 위치가 범위를 벗어나거나 파란색이면
                //이동 방향 변경
                g_horses[i].dir = 1;
                if(!(col+1 > g_N || g_color[row][col+1] == 2)) { //이동할 위치가 범위를 벗어나거나 파란색이 아니면
                    //이동할 위치의 색에 따라 이동시킨다
                    if(g_color[row][col+1] == 0) {
                        move_to_white(i);
                    } else {
                        move_to_red(i);
                    }
                    if(g_idx[row][col+1] >= 4) {    //이동한 위치가 4개 이상되면 종료
                        g_result = roundCnt;    return;
                    }
                }
            } else {    //이동할 위치가 빨간색이나 흰색이면
                //이동시키고
                if(g_color[row][col-1] == 0) {
                    move_to_white(i);
                } else {
                    move_to_red(i);
                }
                //개수확인
                if(g_idx[row][col-1] >= 4) {
                    g_result = roundCnt; return;
                }
            }
        } else if(dir == 3) {   //위로이동
            if(row-1 < 1 || g_color[row-1][col] == 2) { //이동할 위치가 범위를 벗어나거나 파란색이면
                //이동 방향 변경
                g_horses[i].dir = 4;
                if(!(row+1 > g_N || g_color[row+1][col] == 2)) { //이동할 위치가 범위를 벗어나거나 파란색이 아니면
                    //이동할 위치의 색에 따라 이동시킨다
                    if(g_color[row+1][col] == 0) {
                        move_to_white(i);
                    } else {
                        move_to_red(i);
                    }
                    if(g_idx[row+1][col] >= 4) {    //이동한 위치가 4개 이상되면 종료
                        g_result = roundCnt;    return;
                    }
                }
            } else {    //이동할 위치가 빨간색이나 흰색이면
                //이동시키고
                if(g_color[row-1][col] == 0) {
                    move_to_white(i);
                } else {
                    move_to_red(i);
                }
                //개수확인
                if(g_idx[row-1][col] >= 4) {
                    g_result = roundCnt; return;
                }
            }
        } else {    //아래로이동
            if(row+1 > g_N || g_color[row+1][col] == 2) { //이동할 위치가 범위를 벗어나거나 파란색이면
                //이동 방향 변경
                g_horses[i].dir = 3;
                if(!(row-1 < 1 || g_color[row-1][col] == 2)) { //이동할 위치가 범위를 벗어나거나 파란색이 아니면
                    //이동할 위치의 색에 따라 이동시킨다
                    if(g_color[row-1][col] == 0) {
                        move_to_white(i);
                    } else {
                        move_to_red(i);
                    }
                    if(g_idx[row-1][col] >= 4) {    //이동한 위치가 4개 이상되면 종료
                        g_result = roundCnt;    return;
                    }
                }
            } else {    //이동할 위치가 빨간색이나 흰색이면
                //이동시키고
                if(g_color[row+1][col] == 0) {
                    move_to_white(i);
                } else {
                    move_to_red(i);
                }
                //개수확인
                if(g_idx[row+1][col] >= 4) {
                    g_result = roundCnt; return;
                }
            }
        }
        //end 이동할 위치에 따라 분기
    }
    //end 1번말부터 K번말에 대해 수행
    
    //재귀호출
    simul(roundCnt+1);
}

int main(void) {
    int r, c, d;
    int idx = 0;
    int i, j;
    
    scanf("%d %d", &g_N, &g_K);
    for(i=1; i<=g_N; i++) {
        for(j=1; j<=g_N; j++) {
            scanf("%d", &g_color[i][j]);
        }
    }
    //말 정보 입력
    for(i=1; i<=g_K; i++) {
        scanf("%d %d %d", &r, &c, &d);
        g_horses[i].row = r;
        g_horses[i].col = c;
        g_horses[i].dir = d;
        idx = g_idx[r][c];
        g_table[r][c][idx] = i;  //말 번호 저장
        g_idx[r][c] += 1;
    }
    
    //시뮬레이션 호출
    simul(1);
    
    //정답출력
    printf("%d", g_result);
    
    return 0;
}
