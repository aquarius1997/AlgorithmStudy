//
//  모의ST_미생물격리.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/27.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
#include <vector>
using namespace std;

typedef struct Group {
    int row;    //행정보
    int col;    //열정보
    int num;    //미생물수
    int dir;    //방향
    int flag;   //죽은 군집은 1
} Group;

int table[102][102] = {0, };
Group group[1002];  //idx 1~K사용!
vector<int> samePosition[1002];
int M;  //격리시간
int K;  //미생물 군집 개수
int N;  //테이블크기
int answer = 0;

/// 군집의 이동방향을 변경
/// @param groupId 변경하려는 군집 번호
void changeDir(int groupId) {
    if(group[groupId].dir == 1) {
        group[groupId].dir = 2;
    } else if(group[groupId].dir == 2) {
        group[groupId].dir = 1;
    } else if(group[groupId].dir == 3) {
        group[groupId].dir = 4;
    } else {
        group[groupId].dir = 3;
    }
}

void simul(int timeCnt) {
    int row, col, groupId;
    int i, j;
    
    if(timeCnt == M) {  //종료조건
        for(i=1; i<=K; i++) {   //살아있는 군집에 대하여 미생물수들을 더해준다
            if(group[i].flag == 0) {
                answer += group[i].num;
            }
        }
        return;
    }   //종료조건
    else {  //시뮬레이션
        //살아있는 군집들의 이동 이후 행,열 정보를 업데이트한다
        for(i=1; i<=K; i++) {
            if(group[i].flag == 0) {
                table[group[i].row][group[i].col] = 0;

                if(group[i].dir == 1) { //상
                    group[i].row -= 1;
                } else if(group[i].dir == 2) {  //하
                    group[i].row += 1;
                } else if(group[i].dir == 3) {  //좌
                    group[i].col -=1;
                } else {    //우
                    group[i].col += 1;
                }
            }
        }
        // end 살아있는 군집들의 이동 이후 행,열 정보를 업데이트한다
        // 이동시킨 결과를 적용한다
        for(i=1; i<=K; i++) {
            if(group[i].flag == 0) {    // 살아있는 군집이면
                row = group[i].row; col = group[i].col;
                if(row == 0 || row == N-1 || col == 0 || col == N-1) {  //가장자리일경우
                    if(group[i].num / 2 == 0) { //군집 죽음
                        group[i].flag = 1;
                        group[i].num = 0;
                    } else {
                        group[i].num = group[i].num / 2;
                        changeDir(i);
                        table[row][col] = i;
                    }
                }//가장자리일경우
                else {  //가장자리 아닐경우
                    if(table[row][col] == 0) {  //빈 셀일경우
                        table[row][col] = i;
                    }//빈 셀일경우
                    else {  //다른 군집이 잇을경우
                        groupId = table[row][col];  //원래 있던 군집 번호
                        samePosition[groupId].push_back(i); //겹치는 군집번호들을 매단다
                    }//다른 군집이 잇을경우
                }//가장자리 아닐경우
            }//살아있는 군집이면
        }
        // end 이동시킨 결과를 적용한다
        
        //겹치는군집들에 대하여 정리한다
        for(i=1; i<=K; i++) {
            if(samePosition[i].size() > 0) {    //겹치는 포지션들은
                groupId = i;
                row = group[groupId].row;   col = group[groupId].col;
                int maxId = i;  //가장 쿤 군집아이디 알아내기
                int sameId;
                int totalNum = group[groupId].num;  //총 양을 구할때 사용
                for(j=0; j<samePosition[i].size(); j++) {   //겹치는것들중 가장 큰 군집 알아내기
                    sameId = samePosition[i][j];
                    if(group[sameId].num > group[maxId].num) {
                        maxId = sameId;
                    }
                    totalNum += group[sameId].num;
                }//겹치는것들중 가장 큰 군집 알아내기
                //가장 큰 군집으로 테이블 정리하고 방향 조정
                if(groupId != maxId) {  //원래 거가 가장 큰 군집아니면 죽이기
                    group[groupId].flag = 1;
                    group[groupId].num = 0;
                } else {    //원래거가 가장 큰 군집이면 미생물수 업데이트
                    group[groupId].num = totalNum;
                    table[row][col] = groupId;
                }
                for(j=0; j<samePosition[i].size(); j++) {
                    sameId = samePosition[i][j];
                    if(sameId == maxId) {   //가장 큰 군집에 총 미생물수 넣기
                        group[sameId].num = totalNum;
                        row = group[sameId].row;    col = group[sameId].col;
                        table[row][col] = sameId;
                    } else {    //가장 큰 군집이 아니면 죽이기
                        group[sameId].flag = 1;
                        group[sameId].num = 0;
                    }
                }
                //가장 큰 군집으로 테이블 정리하고 방향 조정
            }
            samePosition[i].clear();
        }
        // end 겹치는군집들에 대하여 정리한다

        //다음 시간에 대해 시뮬레이션 돌린다
        simul(timeCnt+1);
    }   //시뮬레이션
}


int main(void) {
    int T, t, row, col, num, dir;
    int i, j;
    
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d %d", &N, &M, &K);
        
        //초기화
        answer = 0;
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                table[i][j] = 0;
            }
        }
        
        for(i=1; i<=K; i++) {
            scanf("%d %d %d %d", &row, &col, &num, &dir);
            group[i].row = row;
            group[i].col = col;
            group[i].num = num;
            group[i].dir = dir;
            group[i].flag = 0;
            table[row][col] = i;
        }
    
        
        simul(0);
        
        printf("#%d %d\n", t, answer);
        
    }
    return 0;
}
