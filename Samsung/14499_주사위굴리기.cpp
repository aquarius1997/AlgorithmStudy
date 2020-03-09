//
//  14499_주사위굴리기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/09.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <cstdio>
using namespace std;

int N, M;
int table[21][21] = {0, };
int dice[7] = {0, };


void rolling(int dir) {
    int temp;
    if(dir == 3) {  //위
        temp = dice[2];
        dice[2] = dice[1];  dice[1] = dice[5];  dice[5] = dice[6];  dice[6] = temp;
    } else if(dir == 4) {//아래
        temp = dice[6];
        dice[6] = dice[5];  dice[5] = dice[1];  dice[1] = dice[2];  dice[2] = temp;
    } else if(dir == 2) {   //왼
        temp = dice[6];
        dice[6] = dice[4];  dice[4] = dice[1];  dice[1] = dice[3];  dice[3] = temp;
    } else {
        temp = dice[6];
        dice[6] = dice[3];  dice[3] = dice[1];  dice[1] = dice[4];  dice[4] = temp;
    }
}

int main(void) {
    int x, y, K, dir;
    int i, j;
    
    scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
    
    for(i=0; i<N; i++) {
        for(j=0; j<M; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    for(i=0; i<K; i++) {
        scanf("%d", &dir);  //이동방향 입력으로 받는다
        //굴렸을때 범위가 안넘어가면 현재 위치 변경시키고 나머지 연산 실행
        if(dir == 1) {  //오른쪽
            if(y+1 < M) {
                y += 1;
                rolling(1);
                if(table[x][y] == 0) {
                    table[x][y] = dice[6];
                } else {
                    dice[6] = table[x][y];
                    table[x][y] = 0;
                }
                printf("%d\n", dice[1]);
            }
        } else if(dir == 2) {   //왼
            if(y-1 >= 0) {
                y -= 1;
                rolling(2);
                if(table[x][y] == 0) {
                    table[x][y] = dice[6];
                } else {
                    dice[6] = table[x][y];
                    table[x][y] = 0;
                }
                printf("%d\n", dice[1]);
            }
        } else if(dir == 3) {   //위
            if(x-1 >= 0) {
                x -= 1;
                rolling(3);
                if(table[x][y] == 0) {
                    table[x][y] = dice[6];
                } else {
                    dice[6] = table[x][y];
                    table[x][y] = 0;
                }
                printf("%d\n", dice[1]);
            }
        } else if(dir == 4) {   //아래
            if(x+1 < N) {
                x += 1;
                rolling(4);
                if(table[x][y] == 0) {
                    table[x][y] = dice[6];
                } else {
                    dice[6] = table[x][y];
                    table[x][y] = 0;
                }
                printf("%d\n", dice[1]);
            }
        }
    }
    
    return 0;
}
