//
//  모의ST_특이한자석.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/20.
//  Copyright © 2020 송혜경. All rights reserved.
//**

#include <cstdio>
using namespace std;

int g_magnets[5][10] = {0, };   //각 자석의 자성정보 저장

void rotation(int magnetNum, int direc) {
    int i;
    
    if(direc == 1) {    //시계방향 회전
        for(i=8; i>=1; i--) {
            g_magnets[magnetNum][i+1] = g_magnets[magnetNum][i];
        }
        g_magnets[magnetNum][1] = g_magnets[magnetNum][9];
    } else {    //반시계방향 회전
        for(i=1; i<=8; i++) {
            g_magnets[magnetNum][i-1] = g_magnets[magnetNum][i];
        }
        g_magnets[magnetNum][8] = g_magnets[magnetNum][0];
    }
}

void simul(int magnetNum, int direc) {
    int rotationDirec[5] = {0,};    //각 자석의 회전 정보 저장 (0 : 회전안함)
    int i;
    
    //입력으로 들어온 자석은 무조건 회전
    rotationDirec[magnetNum] = direc;
    
    //오른쪽 톱니들 확인
    for(i=magnetNum+1; i<=4; i++) {
        if(g_magnets[i-1][3] != g_magnets[i][7]) {
            rotationDirec[i] = rotationDirec[i-1] * (-1);   //반대방향으로 회전함
        } else {    //회전안하면 그다음 확인하면안됨
            break;
        }
    }
    //왼쪽 톱니들 확인
    for(i=magnetNum-1; i>=1; i--) {
        if(g_magnets[i+1][7] != g_magnets[i][3]) {
            rotationDirec[i] = rotationDirec[i+1] * (-1);
        } else {
            break;
        }
    }
    
    //회전하는 톱니들 회전시키기
    for(i=1; i<=4; i++) {
        if(rotationDirec[i] != 0) { //회전하는 톱니는 회전시킨다
            rotation(i, rotationDirec[i]);
        }
    }
}

int main(void) {
    int K, T, t;
    int magnetNum, direc;
    int cnt = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d", &K);
        //자성정보입력
        for(i=1; i<=4; i++) {
            for(j=1; j<=8; j++) {
                scanf("%d", &g_magnets[i][j]);
            }
        }
        //회전시키기
        for(i=0; i<K; i++) {
            scanf("%d %d", &magnetNum, &direc);
            simul(magnetNum, direc);
        }
        
        //정답계싼하기
        if(g_magnets[1][1] == 1) { cnt += 1; }
        if(g_magnets[2][1] == 1) { cnt += 2; }
        if(g_magnets[3][1] == 1) { cnt += 4; }
        if(g_magnets[4][1] == 1) { cnt += 8; }
        
        //출력
        printf("#%d %d\n", t, cnt);
        
        //초기화
        cnt = 0;
        
    }
    
    return 0;
}
