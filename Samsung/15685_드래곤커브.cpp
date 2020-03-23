//
//  15685_드래곤커브.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/23.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int table[102][102] = {0, };    //드래곤 커브가 지나가면 1로 저장
int direction[1500] = {0, };
int lastIdx = -1;

/// 드래곤 커브를 그린다
/// @param x 시작 x 좌표
/// @param y 시작 y 좌표
/// @param d 시작 방향
/// @param g 세대
void dragon_curb(int x, int y, int d, int g) {
    
    //우선 방향정보를 저장한다
    ++lastIdx;  direction[lastIdx] = d;
    for(int i=1; i<=g; i++) {
        for(int j=lastIdx; j>=0; j--) {
            lastIdx += 1;
            direction[lastIdx] = ((direction[j] + 1) % 4);
        }
    }
    //방향에 따라 드래곤 커브가 지나가는 길을 표시한다
    table[y][x] = 1;    //시작점
    for(int i=0; i<=lastIdx; i++) {
        if(direction[i] == 0) { x += 1;}
        else if(direction[i] == 1) { y -= 1;}
        else if(direction[i] == 2) { x -= 1;}
        else { y += 1;}
        
        table[y][x] = 1;
    }
}

int main(void) {
    int N, x, y, d, g;
    int cnt = 0;
    
    scanf("%d", &N);
    for(int i=1; i<=N; i++) {
        scanf("%d %d %d %d", &x, &y, &d, &g);
        lastIdx = -1;
        dragon_curb(x, y, d, g);
    }
    
    //사각형의 개수 세기
    for(int i=0; i<101; i++) {
        for(int j=0; j<101; j++) {
            if(table[i][j] + table[i+1][j] + table[i][j+1] + table[i+1][j+1] == 4) {
                cnt++;
            }
        }
    }

    printf("%d", cnt);
    
    return 0;
}
