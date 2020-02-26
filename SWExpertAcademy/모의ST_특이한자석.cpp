//
//  모의ST_특이한자석.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/26.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int mags[5][10] = {0, };    //mag[1][1] : 1번자석의 첫번째 자성

/// 자석을 회전시킨다
/// @param magNum 회전시킬 자석
/// @param rotDir 자석의 회전 방향
void rotat(int magNum, int rotDir) {
    int i;
    
    if(rotDir == 1) {   //시계방향회전
        for(i=8; i>=1; i--) {
            mags[magNum][i+1]= mags[magNum][i];
        }
        mags[magNum][1] = mags[magNum][9];
    }//시계방향회전
    else {    //반시계방향 회전
        for(i=1; i<=8; i++) {
            mags[magNum][i-1] = mags[magNum][i];
        }
        mags[magNum][8] = mags[magNum][0];
    }//반시계방향 회전
}


/// 하나의 자석을 돌릴때, 다른 자석들에게 어떤 영향을 끼칠지 알아낸다
/// @param magNum 돌리고 싶은 자석
/// @param rotDir 자석을 회전시킬 방향 (1:시계, -1:반시계)
void simul(int magNum, int rotDir) {
    int left[5] = {0,};
    int right[5] = {0,};
    int dir[5] = {0, }; //모든 자석이 일단 회전안하는걸로 초기화
    int i;
    
    dir[magNum] = rotDir;   //인풋으로 들어온 자석은 무조건 회전
    
    for(i=1; i<=4; i++) {   //모든 자석에 대해
        left[i] = mags[i][7];   //왼쪽에 맡닿은 자석의 자성을 알아낸다
        right[i] = mags[i][3];  //오른쪽에 맡닿은 자석의 자성을 알아낸다
    }//모든 자석에 대해
    
    for(i=magNum+1; i<=4; i++) {  //오른쪽 자석들에 대하여
        if(left[i] != right[i-1]) { //서로 맡닿은 자성이 다르면
            if(dir[i-1] == -1) {    //반대방향으로 회전
                dir[i] = 1;
            } else {
                dir[i] = -1;
            }
        }
        else { //맡닿은 자성이 같으면 이후것도 살펴볼 필요없음
            break;
        }
    }//오른쪽 자석들에 대하여
    
    for(i=magNum-1; i>=1; i--) {    //왼쪽 자석들에 대하여
        if(right[i] != left[i+1]) { //서로 맡닿은 자성이 다르면 회전
            if(dir[i+1] == -1) {
                dir[i] = 1;
            } else {
                dir[i] = -1;
            }
        }
        else { //맡닿은 자성이 같으면 이후것도 살펴볼 필요없음
            break;
        }
    }//왼쪽 자석들에 대하여
    
    for(i=1; i<=4; i++) {   //회전하는 자석들에 대하여 회전시킨다
        if(dir[i] != 0) {
            rotat(i, dir[i]);
        }
    }
}

int main(void) {
    int T, t, K, magNum, rotDir;
    int result, number;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d", &K);
        
        for(i=1; i<=4; i++) {
            for(j=1; j<=8; j++) {
                scanf("%d", &mags[i][j]);
            }
        }
        
        for(i=0; i<K; i++) {    //회전하고 싶은 자석과 방향을 입력받아서 회전한다
            scanf("%d %d", &magNum, &rotDir);
            simul(magNum, rotDir);
        }
                
        result = 0;
        number = 1;
        for(i=1; i<=4; i++) {
            if(mags[i][1] == 0) {   //N극이면 0점
                result += 0;
            } else {    //S극이면
                result += number;
            }
            number = number*2;
        }
        
        printf("#%d %d\n", t, result);
    }
    
    return 0;
}
