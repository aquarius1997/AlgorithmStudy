//
//  모의ST_미생물격리.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/27.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <vector>
using namespace std;

typedef struct GroupType {
    int row;
    int col;
    int tempSum;    //누적 저장
    int number; //미생물수  -> 죽으면 0으로 저장
    int dir;    //1:상, 2:하, 3:좌 4:우
}GroupType;

GroupType g_group[1002];    //미생물 군집
int g_cell[102][102] = {0,};    //살아있는 미생물의 번호 저장
int g_N = 0;    //셀의개수
int g_K = 0;    //초기 미생물 군집 개수

void simul(int M) {
    int timeCnt = 0;
    int row, col;
    int preGroupNum = 0;
    int i;
    
    
    //주어진 시간만큼 미생물들을 움직인다
    while(timeCnt < M) {
        
        //1. 미생물들을 이동시킨다
        for(i=1; i<=g_K; i++) {
            //살아있는 군집만
            if(g_group[i].number != 0) {
                g_cell[g_group[i].row][g_group[i].col] = 0;
                if(g_group[i].dir == 1) { g_group[i].row -= 1; }
                else if(g_group[i].dir == 2) { g_group[i].row += 1; }
                else if(g_group[i].dir == 3) { g_group[i].col -= 1; }
                else { g_group[i].col += 1;}
            }
            //end 살아있는 군집만
        }
        //end 1
        //2. 이동 이후 정보들을 바탕으로 cellTable 위치 정보를 업데이트하고 군집 정보를 업데이트 처리한다
        for(i=1; i<=g_K; i++) {
            if(g_group[i].number != 0) {
                row = g_group[i].row;
                col = g_group[i].col;
                //가장자리로 위치하면 반으로 줄이고 죽었는지 확인해서 처리
                if(row == 0 || row == g_N-1 || col == 0 || col == g_N-1) {
                    g_group[i].number = g_group[i].number / 2;
                    g_group[i].tempSum = g_group[i].number;
                    //방향전환
                    if(g_group[i].dir == 1) { g_group[i].dir = 2;}
                    else if(g_group[i].dir == 2) { g_group[i].dir = 1;}
                    else if(g_group[i].dir == 3) { g_group[i].dir = 4;}
                    else { g_group[i].dir = 3; }
                    if(g_group[i].number != 0) {    //살아있으면 테이블에 정보 저장
                        g_cell[row][col] = i;
                    }
                } else {    //가장자리로 위치하지 않은경우
                    if(g_cell[row][col] == 0) { //아직 겹치는 군집 없으면
                        g_cell[row][col] = i;
                        g_group[i].tempSum = g_group[i].number; //자기 자신의 미생물 수로 누적 초기화
                    } else { // 겹치는 군집이 생기면
                        preGroupNum = g_cell[row][col];
                        if(g_group[preGroupNum].number > g_group[i].number) {   //원래 있던 군집이 나보다 더 크면
                            g_group[preGroupNum].tempSum += g_group[i].number;  //누적시키고
                            g_group[i].number = 0;  //현재 군집 죽은거 처리
                        } else {    //원래 있던 군집보다 내가 더 크면
                            g_cell[row][col] = i;   //내 군집 번호로 테이블 저장
                            g_group[i].tempSum = g_group[preGroupNum].tempSum + g_group[i].number; //이전 군집의 누적을 내 누적에 저장
                            g_group[preGroupNum].number = g_group[preGroupNum].tempSum = 0; //이전 군집 죽은거 처리
                        }
                    }// end 겹치는 군집이 생기면
                }
            }//end if(g_group[i].number != 0)
        }
        //end 2
        
        //3. 살아있는 군집들에 대해 누적을 number로 업데이트
        for(i=1; i<=g_K; i++) {
            if(g_group[i].number > 0) {
                g_group[i].number = g_group[i].tempSum;
                g_group[i].tempSum = 0;
            }
        }
        //end 3
        
        timeCnt++;
    }
    //end while
    
}


int main(void) {
    int t, T, M;
    int sum = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d %d", &g_N, &M, &g_K);
        //미생물 군집의 정보 입력받기
        for(i=1; i<=g_K; i++) {
            scanf("%d %d %d %d", &g_group[i].row, &g_group[i].col, &g_group[i].number, &g_group[i].dir);
            g_cell[g_group[i].row][g_group[i].col] = i;
            g_group[i].tempSum = 0;
        }
        
        //시뮬레이션 돌리기
        simul(M);
        
        //정답 출력
        for(i=1; i<=g_K; i++) {
            if(g_group[i].number > 0) {
                sum += g_group[i].number;
            }
        }
        printf("#%d %d\n", t, sum);
        
        //초기화
        sum = 0;
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                g_cell[i][j] = 0;
            }
        }
    }
    
    return 0;
}

