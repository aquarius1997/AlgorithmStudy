//
//  14499_주사위굴리기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/08.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
using namespace std;

int g_N = 0;
int g_M = 0;
int g_table[22][22] = {0,};
int g_dice[7] = {0,};

/// 오른쪽으로 굴린다
void rolling_right(void) {
    int temp = g_dice[6];
    g_dice[6] = g_dice[3];
    g_dice[3] = g_dice[1];
    g_dice[1] = g_dice[4];
    g_dice[4] = temp;
}

/// 왼쪽으로 굴린다
void rolling_left(void) {
    int temp = g_dice[6];
    g_dice[6] = g_dice[4];
    g_dice[4] = g_dice[1];
    g_dice[1] = g_dice[3];
    g_dice[3] = temp;
}

/// 위로 굴린다
void rolling_up(void) {
    int temp = g_dice[6];
    g_dice[6] = g_dice[2];
    g_dice[2] = g_dice[1];
    g_dice[1] = g_dice[5];
    g_dice[5] = temp;
}

/// 아래로 굴린다
void rolling_down(void) {
    int temp = g_dice[6];
    g_dice[6] = g_dice[5];
    g_dice[5] = g_dice[1];
    g_dice[1] = g_dice[2];
    g_dice[2] = temp;
}


int main(void) {
    int K, x, y, dir;
    int i, j;
    
    scanf("%d %d %d %d %d", &g_N, &g_M, &x, &y, &K);
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_M; j++) {
            scanf("%d", &g_table[i][j]);
        }
    }
    for(i=0; i<K; i++) {
        scanf("%d", &dir);  //움직이려는 방향 알아내기
        if(dir == 1) {  //동
            if(y+1 < g_M) {
                y = y + 1;
                rolling_right();
                if(g_table[x][y] == 0) { g_table[x][y] = g_dice[6]; }
                else { g_dice[6] = g_table[x][y]; g_table[x][y] = 0; }
                printf("%d\n", g_dice[1]);
            }
        } else if(dir == 2) { //서
            if(y-1 >= 0) {
                y = y - 1;
                rolling_left();
                if(g_table[x][y] == 0) { g_table[x][y] = g_dice[6]; }
                else { g_dice[6] = g_table[x][y]; g_table[x][y] = 0; }
                printf("%d\n", g_dice[1]);
            }
        } else if(dir == 3) { //북
            if(x-1 >= 0) {
                x = x-1;
                rolling_up();
                if(g_table[x][y] == 0) { g_table[x][y] = g_dice[6]; }
                else { g_dice[6] = g_table[x][y]; g_table[x][y] = 0; }
                printf("%d\n", g_dice[1]);
            }
        } else {    //남
            if(x+1 < g_N) {
                x = x+1;
                rolling_down();
                if(g_table[x][y] == 0) { g_table[x][y] = g_dice[6]; }
                else { g_dice[6] = g_table[x][y]; g_table[x][y] = 0; }
                printf("%d\n", g_dice[1]);
            }
        }
    }
    
    return 0;
}
