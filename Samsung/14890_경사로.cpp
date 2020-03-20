//
//  14890_경사로.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/19.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int N, L;
int road[102][102] = {0, };
int constructed[102][102] = {0, };  //가로 경사로가 지어진 곳은 1로 저장, 세로 경사로가 지어진 곳은 2로 저장
int cnt = 0;

/// 가로 세로로 총 몇개의 길을 만들 수 있는지 알아낸다
void constructing(void) {
    //가로로 몇 개 만들 수 있는 지 확인
    for(int row=0; row<N; row++) {
        int height = road[row][0];  //첫번째 높이 구하고
        int j=1;
        for(; j<N;) {
            //높이가 이전과 동일해, 경사로를 쌓을 필요 없을 경우
            if(height == road[row][j]) {
                j++;
                continue;
            }
            //높이가 이전과 달라, 경사로를 쌓아야 할 경우 차이가 1인지 먼저 확인한다
            else {
                //높이가 1 낮아진 경우
                if(height == road[row][j] + 1) {
                    height = road[row][j];
                    int flag = 0;
                    if(j+L-1 >= N) {    //범위를 벗어날 경우
                        break;
                    }
                    //L길이만큼 경사로를 만들 수 있는지 확인한다
                    for(int l=0; l<L; l++) {
                        if(constructed[row][j+l] != 1 && height == (road[row][j+l])) {  //가로로 경사로 지어진 적 없고 길이가 연속되면
                            constructed[row][j+l] = 1;  //경사로 만든것을 표시
                        } else {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1) { //경사로 만들기 불가능함
                        break;
                    } else {    //경사로 만들기 가능함
                        j = j+L;
                    }
                }
                //높이가 1 높아진 경우
                else if(height == road[row][j] - 1) {
                    height = road[row][j];
                    int flag = 0;
                    if(j-L < 0) {   //경사로 쌓을 수 있는 범위를 벗어나면
                        break;
                    }
                    for(int l=0; l<L; l++) {
                        if(constructed[row][j-1-l] != 1 && (road[row][j-1] == road[row][j-1-l])) {
                            constructed[row][j-1-l] = 1;
                        } else {    //경사로 만들기 불가능함
                            flag = 1;   break;
                        }
                    }
                    if(flag == 1) { //경사로 만들기 불가능함
                        break;
                    } else {
                        j++;
                    }
                }
                //높이 차이가 2 이상인 경우
                else {
                    break;
                }
            }
            //end 높이가 이전과 달라, 경사로를 쌓아야 할 경우 차이가 1인지 먼저 확인한다

        }
        if(j == N) {    //길을 만들 수 있는 경우
            cnt++;
        }
    }
    //세로로 몇 개 만들 수 있는 지 확인
    for(int col=0; col<N; col++) {
        int height = road[0][col];  //첫번째 높이 구하고
        int i = 1;
        for(; i<N;) {
            //높이가 이전과 동일해, 경사로를 쌓을 필요 없을 경우
            if(height == road[i][col]) {
                i++;
                continue;
            }
            //높이가 이전과 달라, 경사로를 쌓아야 할 경우 차이가 1인지 먼저 확인한다
            else {
                //높이가 1 낮아진 경우
                if(height == road[i][col] + 1) {
                    height = road[i][col];
                    int flag = 0;
                    if(i+L-1 >= N) {    //범위를 벗어날 경우
                        break;
                    }
                    //L길이만큼 경사로를 만들 수 있는지 확인한다
                    for(int l=0; l<L; l++) {
                        if(constructed[i+l][col] != 2 && height == (road[i+l][col])) {  //세로로 경사로 지어진 적 없고 길이가 연속되면
                            constructed[i+l][col] = 2;  //경사로 만든것을 표시
                        } else {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1) { //경사로 만들기 불가능함
                        break;
                    } else {    //경사로 만들기 가능함
                        i = i+L;
                    }
                }
                //높이가 1 높아진 경우
                else if(height == road[i][col] - 1) {
                    height = road[i][col];
                    int flag = 0;
                    if(i-L < 0) {   //경사로 쌓을 수 있는 범위를 벗어나면
                        break;
                    }
                    for(int l=0; l<L; l++) {
                        if(constructed[i-1-l][col] != 2 && (road[i-1][col] == road[i-1-l][col])) {
                            constructed[i-1-l][col] = 2;
                        } else {    //경사로 만들기 불가능함
                            flag = 1;   break;
                        }
                    }
                    if(flag == 1) { //경사로 만들기 불가능함
                        break;
                    } else {
                        i++;
                    }
                }
                //높이 차이가 2 이상인 경우
                else {
                    break;
                }
            }
            //end 높이가 이전과 달라, 경사로를 쌓아야 할 경우 차이가 1인지 먼저 확인한다
        }
        if(i == N) {    //길을 만들 수 있는 경우
            cnt++;
        }
    }
    //end 세로로 몇 개 만들 수 있는 지 확인
}


int main(void) {
    scanf("%d %d", &N, &L);
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d", &road[i][j]);
        }
    }
    
    constructing();
    
    printf("%d", cnt);
    
    return 0;
}
