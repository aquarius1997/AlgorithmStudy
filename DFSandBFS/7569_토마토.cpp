//
//  7569_토마토.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/23.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>

using namespace std;

int tomato[102][102][102];  //tomato[i][j][k] -> i번째통의 j행 k열의 토마토
int tempTomato[102][102][102] = {0, };
int N, M, H;
int result;

/// BFS로 토마토를 익힌다
/// @param day 현재 일 수
void xday(int day) {
    int i, j, k;
    int isSame = 0;
    int flag = 0;   //모든 토마토가 익었을 경우 0
    
    for(i=1; i<=H; i++) {
        for(j=1; j<=N; j++) {
            for(k=1; k<=M; k++) {
                if(tomato[i][j][k] == 1) {  //익은 토마토가 있으면
                    
                    //상하좌우위아래 익힌다
                    if(tomato[i][j-1][k] != -1) {
                        tempTomato[i][j-1][k] = 1;
                    }
                    if(tomato[i][j+1][k] != -1) {
                        tempTomato[i][j+1][k] = 1;
                    }
                    if(tomato[i][j][k-1] != -1) {
                        tempTomato[i][j][k-1] = 1;
                    }
                    if(tomato[i][j][k+1] != -1) {
                        tempTomato[i][j][k+1] = 1;
                    }
                    if(tomato[i+1][j][k] != -1) {
                        tempTomato[i+1][j][k] = 1;
                    }
                    if(tomato[i-1][j][k] != -1) {
                        tempTomato[i-1][j][k] = 1;
                    }
                    
                    
                }
            }
        }
    }
    
    for(i=1; i<=H; i++) {
        for(j=1; j<=N; j++) {
            for(k=1; k<=M; k++) {
                if(tempTomato[i][j][k] == 0) {  //익지 않은 토마토가 있을 경우
                    flag = 1;
                }
                if(tempTomato[i][j][k] != tomato[i][j][k]) {    //달라진 토마토가 하나라도 있으면
                    isSame = 1;
                }
                tomato[i][j][k] = tempTomato[i][j][k];
            }
        }
    }
    
    if(flag == 1 && isSame == 0) {
        result = -1;
    }else if(flag == 1 && isSame == 1) {
        xday(day+1);
    } else if(flag == 0) {
        result = day;
    }
}


int main(void) {
    int flag = 0;   //처음부터 모두 익었을 경우 0
    int i, j, k;
    
    scanf("%d %d %d", &M, &N, &H);
    
    for(i=1; i<=H; i++) {
        for(j=1; j<=N; j++) {
            for(k=1; k<=M; k++) {
                scanf("%d", &tomato[i][j][k]);
                
                if(tomato[i][j][k] == 0) {  //하나라도 익지 않은 토마토가 있을경우
                    flag = 1;
                }
            }
        }
    }
    
    if(flag == 0) { //처음부터 모든 토마토가 익어있을 경우
        printf("0");
    } else {
        xday(1);
    }
    
    printf("%d", result);
    
    return 0;
}
