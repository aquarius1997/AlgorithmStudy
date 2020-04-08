//
//  모의ST_벽돌깨기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/08.
//  Copyright © 2020 송혜경. All rights reserved.
//  **, 45min, F:0

#include <cstdio>
using namespace std;

int bricks[20][20] = {0, };
int g_N = 0;
int g_W = 0;
int g_H = 0;
int g_min = 0;  //남은 벽돌의 최소 개수

/// 벽돌 사이의 빈 공간을 없앤다
void arrange_bricks(void) {
    int zeroCnt = 0;
    int idx = 0;
    int i, j;
    
    for(j=0; j<g_W; j++) {  //각 열에 대해
        zeroCnt = 0;
        for(idx = g_H-1; idx>=0; ) {
            if(bricks[idx][j] == 0) {   //연속되는 빈칸의 수 카운팅
                zeroCnt++;
                idx--;
            } else {
                if(zeroCnt > 0) {
                    for(i=idx; i>=0; i--) { //빈칸 없애주기(아래로 내리기)
                        bricks[i+zeroCnt][j] = bricks[i][j];
                    }
                    for(i=0; i<zeroCnt; i++) {  //위에 빈칸으로
                        bricks[i][j] = 0;
                    }
                    idx = idx + zeroCnt - 1;
                } else {
                    idx--;
                }
                zeroCnt = 0;
            }
        }
    }   //end for(j)
}

/// 벽돌을 연쇄적으로 깬다
/// @param row 깰 벽돌의 행
/// @param col 깰 벽돌의 열
void breaking(int row, int col) {
    int brickNum = bricks[row][col];
    int i;
    
    //1. 기준 벽돌 0으로 만든다
    bricks[row][col] = 0;
    //2. 벽돌 수의 -1만큼 상하좌우 벽돌이 잇을 경우 연쇄적으로 부신다
    for(i=1; i<=brickNum-1; i++) {
        if(row-i >= 0) {    //상
            if(bricks[row-i][col] != 0) {
                breaking(row-i, col);
            }
        }
        if(row+i < g_H) {   //하
            if(bricks[row+i][col] != 0) {
                breaking(row+i, col);
            }
        }
        if(col-i >= 0) {    //좌
            if(bricks[row][col-i] != 0) {
                breaking(row, col-i);
            }
        }
        if(col+i < g_W) {   //우
            if(bricks[row][col+i] != 0) {
                breaking(row, col+i);
            }
        }
    }
    //end 2
}

/// g_N개의 벽돌을 떨어트리고 남은 벽돌의 최소 개수를 구한다
/// @param brickCnt 현재까지 떨어트린 벽돌의 수
void simul(int brickCnt) {
    int tempBricks[20][20] = {0, }; //재귀호출 이전의 벽돌 정보를 저장
    int cnt = 0;
    int i, j;
    int l, m;
    
    if(brickCnt == g_N) { //종료조건
        //남은 벽돌의 수를 세서 최소 업데이트한다
        for(i=0; i<g_H; i++) {
            for(j=0; j<g_W; j++) {
                if(bricks[i][j] != 0) {
                    cnt++;
                }
            }
        }
        if(cnt < g_min) {
            g_min = cnt;
        }
        return;
    } else {    //재귀호출
        //1. 재귀호출 이전에 벽돌 정보를 저장한다
        for(i=0; i<g_H; i++) {
            for(j=0; j<g_W; j++) {
                tempBricks[i][j] = bricks[i][j];
            }
        }
        //end 1
        
        //2. 각 열에 대해 첫번째 벽돌을 찾는다
        for(j=0; j<g_W; j++) {
            for(i=0; i<g_H; i++) {
                if(bricks[i][j] != 0) { //첫번째 벽돌
                    //벽돌을 연쇄적으로 깨고
                    breaking(i, j);
                    //빈공간은 없앤다
                    arrange_bricks();
                    //재귀호출한다
                    simul(brickCnt+1);
                    //깨기 이전의 벽돌 모양으로 만든다
                    for(l=0; l<g_H; l++) {
                        for(m=0; m<g_W; m++) {
                            bricks[l][m] = tempBricks[l][m];
                        }
                    }
                    break;
                }
            }   //end for(i)
            //해당 열에 벽돌이 하나도 없을 경우
            if(i == g_H) {
                simul(brickCnt+1);
            }
        }   //end for(j)
        // end 2
        
        
    }   //end 재귀호출
}

int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //입력받기
        scanf("%d %d %d", &g_N, &g_W, &g_H);
        for(i=0; i<g_H; i++) {
            for(j=0; j<g_W; j++) {
                scanf("%d", &bricks[i][j]);
                if(bricks[i][j] != 0) { //처음 벽돌의 수로 남은 벽돌의 최소 개수를 저장
                    g_min++;
                }
            }
        }
        
        //시뮬레이션
        simul(0);
        
        //정답 출력
        printf("#%d %d\n", t, g_min);
    }
    
    return 0;
}
