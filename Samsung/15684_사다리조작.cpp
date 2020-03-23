//
//  15684_사다리조작.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
using namespace std;

int table[32][12] = {0, };
int N, H, M;
int flag = 0;   //조건 만족하면 1
int answer = -1;

/// num개의 사다리를 추가한다.
/// @param num 추가해야하는 총 개수
/// @param num_cnt 현재까지 추가한 개수
void making_ladder(int num, int num_cnt, int row, int col) {
    //사다리 놓기
    if(num != 0) {
        table[row][col] = 1;    table[row][col+1] = 2;
    }
    //num개를 다 놨으면 조건 확인
    if(num == num_cnt) {
        int is_ok = 0;
        int c;
        for(int j=1; j<=N; j++) {   //사다리를 하나씩 타고 내려온다
            c = j;
            for(int i=1; i<=H; i++) {
                if(table[i][c] == 1) {  //오른쪽으로 이동해야하면
                    c = c+1;    //옆 사다리로 이동
                    continue;
                }
                if(table[i][c] == 2) {  //왼쪽으로 이동해야하면
                    c = c-1;
                    continue;
                }
            }
            if(c != j) {    //원래 위치로 돌아오지 않으면
                is_ok = 1;  break;
            }
        }
        if(is_ok == 0) {    //모든 사다리가 원래 위치로 돌아오면
            flag = 1;
        }
    } else {
        //하나 더 추가하는 함수 호출
        for(int j=col+1; j<=N; j++) {
            if(table[row][j] == 0 && j+1 <= N) {
                if(table[row][j+1] == 0) {
                    making_ladder(num, num_cnt+1, row, j);
                }
            }
        }
        for(int i=row+1; i<=H; i++) {
            for(int j=0; j<=N; j++) {
                if(table[i][j] == 0 && j+1 <= N) {
                    if(table[i][j+1] == 0) {
                        making_ladder(num, num_cnt+1, i, j);
                    }
                }
            }
        }
    }
    //초기화
    if(num != 0) {
        table[row][col] = 0;    table[row][col+1] = 0;
    }
}

/// 사다리를 추가해서 조건을 만족하는지 확인
/// @param num 추가한 사다리의 개수
void simul(int num) {
    int flag2 = 0;
    if(num > 3) { return; };  //3개보다 많이 추가해야 할 경우

    if(num == 0) {
        making_ladder(0, 0, 1, 1);
        if(flag == 1) {
            answer = num;
        }
        flag2 = 1;
    } else {
        for(int i=1; i<=H; i++) {
            for(int j=1; j<=N; j++) {
                if(table[i][j] == 0 && j+1 <= N) {
                    if(table[i][j+1] == 0) {    //사다리 놓는 함수를 호출
                        flag2 = 1;
                        making_ladder(num, 1, i, j);
                        if(flag == 1) { //조건 만족
                            answer = num;   break;
                        }
                    }
                }
            }
            if(flag == 1) { break; }    //조건 만족
        }
    }
    
    if(flag2 == 0) {    //사다리를 놓는 함수를 호출 못함
        return;
    }
    if(flag == 0) { //사다리를 1개 더 추가한다
        simul(num+1);
    }
}


int main(void) {
    int a, b;
    scanf("%d %d %d", &N, &M, &H);
    
    for(int i=1; i<=M; i++) {   //기본 가로선
        scanf("%d %d", &a, &b);
        table[a][b] = 1;    //R
        table[a][b+1] = 2;  //L
    }
    //사다리 놓기
    simul(0);
    
    printf("%d", answer);
    
    return 0;
}
