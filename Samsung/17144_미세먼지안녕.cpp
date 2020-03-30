//
//  17144_미세먼지안녕.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/30.
//  Copyright © 2020 송혜경. All rights reserved.
//  40min. *

#include <cstdio>
using namespace std;

int R, C, T;   //테이블크기, 시간
int table[52][52] = {0, };
int tempTable[52][52] = {0,};   //미세먼지 확산 시킬 때 사용하는 배열
int cleanerOne = 0;
int cleanerTwo = 0;

///  미세먼지를 확산 시킨다
void spread(void) {
    int spreadCnt = 0;  //상하좌우 확산된 칸의 개수
    int spreadAmount = 0;   //상하좌우 확산 시킬 양
    int i, j;
    
    for(i=0; i<R; i++) {
        for(j=0; j<C; j++) {
            if(table[i][j] > 0) {   //미세먼지 있으면 확산
                spreadCnt = 0;
                spreadAmount = table[i][j] / 5;
                
                //상하좌우 확인
                if(i-1 >= 0) {
                    if(table[i-1][j] != -1) {   //공기청정기 없는지 확인
                        spreadCnt++;
                        tempTable[i-1][j] += spreadAmount;
                    }
                }
                if(i+1 < R) {
                    if(table[i+1][j] != -1) {
                        spreadCnt++;
                        tempTable[i+1][j] += spreadAmount;
                    }
                }
                if(j-1 >= 0) {
                    if(table[i][j-1] != -1) {
                        spreadCnt++;
                        tempTable[i][j-1] += spreadAmount;
                    }
                }
                if(j+1 < C) {
                    if(table[i][j+1] != -1) {
                        spreadCnt++;
                        tempTable[i][j+1] += spreadAmount;
                    }
                }
                //end 상하좌우 확인
                //현재 위치 미세 먼지양 누적
                tempTable[i][j] += (table[i][j] - (spreadAmount * spreadCnt));
            }
            //end 미세먼지 있는 칸
        }
    }
    //end 확산
    
    //확산 결과를 table에 저장하고 tempTable초기화
    for(i=0; i<R; i++) {
        for(j=0; j<C; j++) {
            if(table[i][j] > -1) {  //공기청정기 있는 칸은 제외하기
                table[i][j] = tempTable[i][j];
            }
            tempTable[i][j] = 0;
        }
    }
}

/// seconds 초 이후 상태를 저장
/// @param seconds 여태까지 흐른 시간
void simul(int seconds) {
    int i, j;
    
    if(seconds == T) {  //종료
        return;
    }
    
    spread();
    //위쪽 공기 청정기를 돌린다
    for(i=cleanerOne-2; i>=0; i--) {
        table[i+1][0] = table[i][0];
    }
    for(j=1; j<C; j++) {
        table[0][j-1] = table[0][j];
    }
    for(i=1; i<=cleanerOne; i++) {
        table[i-1][C-1] = table[i][C-1];
    }
    for(j=C-2; j>=1; j--) {
        table[cleanerOne][j+1] = table[cleanerOne][j];
    }
    table[cleanerOne][1] = 0;   //깨끗한 공기
    //end 위쪽 공기 청정기 돌린다
    
    //아래쪽 공기청정기를 돌린다
    for(i=cleanerTwo+2; i<R; i++) {
        table[i-1][0] = table[i][0];
    }
    for(j=1; j<C; j++) {
        table[R-1][j-1] = table[R-1][j];
    }
    for(i=R-2; i>=cleanerTwo; i--) {
        table[i+1][C-1] = table[i][C-1];
    }
    for(j=C-2; j>=1; j--) {
        table[cleanerTwo][j+1] = table[cleanerTwo][j];
    }
    table[cleanerTwo][1] = 0;   //깨끗한 공기
    //end 아래 공기청정기 돌리기
    
    //재귀호출
    simul(seconds+1);
}

int main(void) {
    int totalCnt = 0;
    int flag = 0;   //위쪽 공기청정기 정보 저장하면 1로 변경
    int i, j;
    
    scanf("%d %d %d", &R, &C, &T);
    for(i=0; i<R; i++) {
        for(j=0; j<C; j++) {
            scanf("%d", &table[i][j]);
            if(table[i][j] == -1) {
                if(flag == 0) {
                    cleanerOne = i;
                    flag = 1;
                } else {
                    cleanerTwo = i;
                }
            }
        }
    }
    
    //시뮬레이션 호출
    simul(0);
    
    //전체 먼지의 양 구하기
    for(i=0; i<R; i++) {
        for(j=0; j<C; j++) {
            if(table[i][j] > 0) {
                totalCnt += table[i][j];
            }
        }
    }
    
    //정답 출력
    printf("%d", totalCnt);
    
    return 0;
}
