//
//  모의ST_활주로건설.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/26.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int N;
int road[22][22] = {0, };
int constructed[22][22] = {0, };    //해당 자리에 활주로 건설했으면 1. 만일 경사로 건설했으면 2
int X;
int cnt;

/// 입력받은 행 또는 열에 대하여 활주로 건설이 가능한지 확인한다
/// @param row 가로 검사시 필요. -1일 경우 세로 검사
/// @param col 세로 검사시 필요, -1일 경우 가로 검사
void construction(int row, int col) {
    int num;
    int i, j, k;
    
    if(row == -1) { //col열 검사
        num = road[0][col]; //첫번째 높이
        constructed[0][col] = 1;
        for(i=1; i<N;) {    //행 검사
            if(num == road[i][col]) {   //동일한 높이면
                constructed[i][col] = 1;
                i = i+1;
            }   //end 동일 높이
            else if(num == road[i][col] + 1) {   //높이가 1만큼 낮아졌으면
                constructed[i][col] = 2;
                for(k=1; k<X; k++) {    //경사로 만들기
                    if(i+k >= N) {  //범위벗어나면 종료
                        return;
                    } else {
                        if(road[i][col] != road[i+k][col]) {  //경사로 길이만큼 못만들면 종료
                            return;
                        }
                    }
                    constructed[i+k][col] = 2;
                }
                num = road[i][col]; //기준 높이 변경
                i = i + X;
            }   //end 높이가 1만큼 낮아졌으면
            else if(num == road[i][col] - 1) {  //높이가 1만큼 커졋으면
                for(k=1; k<=X; k++) {
                    if(i-k < 0) {   //범위벗어나면 종료
                        return;
                    } else {
                        if(road[i-k][col] != num || constructed[i-k][col] == 2) { //경사로 길이만큼 못만들거나 + 이미 경사로가 지어진곳이면 종료
                            return;
                        }
                    }
                    constructed[i-k][col] = 2;
                }
                num = road[i][col];
                constructed[i][col] = 1;
                i = i+1;
            }   //높이가 1만큼 커졋으면
            else {  //높이가 2이상으로 변화했으면 건설못함. 종료.
                return;
            }   //높이가 2이상으로 변화했으면 건설못함. 종료.
        }   // 행 검사
        
        cnt += 1;   //활주로 건설 가능
    }   //end if(row == -1)
    if(col == -1) { //row행 검사
        num = road[row][0]; //첫번째 높이
        constructed[row][0] = 1;
        for(j=1; j<N;) {    //행 검사
            if(num == road[row][j]) {   //동일한 높이면
                constructed[row][j] = 1;
                j = j+1;
            }   //end 동일 높이
            else if(num == road[row][j] + 1) {   //높이가 1만큼 낮아졌으면
                constructed[row][j] = 2;
                for(k=1; k<X; k++) {    //경사로 만들기
                    if(j+k >= N) {  //범위벗어나면 종료
                        return;
                    } else {
                        if(road[row][j] != road[row][j+k]) {  //경사로 길이만큼 못만들면 종료
                            return;
                        }
                    }
                    constructed[row][j+k] = 2;
                }
                num = road[row][j]; //기준 높이 변경
                j = j + X;
            }   //end 높이가 1만큼 낮아졌으면
            else if(num == road[row][j] - 1) {  //높이가 1만큼 커졋으면
                for(k=1; k<=X; k++) {
                    if(j-k < 0) {   //범위벗어나면 종료
                        return;
                    } else {
                        if(road[row][j-k] != num || constructed[row][j-k] == 2) { //경사로 길이만큼 못만들거나 + 이미 경사로가 지어진곳이면 종료
                            return;
                        }
                    }
                    constructed[row][j-k] = 2;
                }
                num = road[row][j];
                constructed[row][j] = 1;
                j = j+1;
            }   //높이가 1만큼 커졋으면
            else {  //높이가 2이상으로 변화했으면 건설못함. 종료.
                return;
            }   //높이가 2이상으로 변화했으면 건설못함. 종료.
        }   // 행 검사
        
        cnt += 1;   //활주로 건설 가능
    }   //end if(col == -1)
}

int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d", &N, &X);
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &road[i][j]);
            }
        }
        
        //초기화
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++){
                constructed[i][j] = 0;
            }
        }
        cnt = 0;
        
        //함수호출
        for(i=0; i<N; i++) {    //가로 건설
            construction(i, -1);
        }
        //초기화
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++){
                constructed[i][j] = 0;
            }
        }
        for(j=0; j<N; j++) {    //세로건설
            construction(-1, j);
        }
        
        printf("#%d %d\n", t, cnt);
    }
    
    return 0;
}
