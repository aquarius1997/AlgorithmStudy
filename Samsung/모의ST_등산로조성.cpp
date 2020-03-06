//
//  모의ST_등산로조성.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/02.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <cstdio>
using namespace std;

int table[10][10] = {0, };
int visited[10][10] = {0, };
int N;
int K;
int flag = 0;   //이미 1번 깎았으면 1로
int maxDist = 0;

/// DFS로 등산로를 알아낸다
/// @param row 현재 행 위치
/// @param col 현재 열 위치
/// @param dist 현재까지 등산로의 길이
void simul(int row, int col, int dist) {
    int tempH;
    
    visited[row][col] = 1;  //방문
    
    if(maxDist < dist) {    //가장 긴 등산로 업데이트
        maxDist = dist;
    }
    
    if(row-1 >= 0) {    //위쪽으로 확인
        if(visited[row-1][col] == 0) {  //방문안하고
            if(table[row-1][col] < table[row][col]) {   //나보다 낮으면
                simul(row-1, col, dist+1);
            } //나보다 낮으면
            else {  //나보다 높거나 같으면
                if(flag == 0) { //다른데 깎은적 없으면
                    //나보다 더 낮게 만들수 있는지 확인
                    if(table[row-1][col] - K < table[row][col]) {   //더 낮게 만들수있으면 나보다 딱 1더작게만든다
                        tempH = table[row-1][col];
                        table[row-1][col] = table[row][col] - 1;
                        flag = 1;   //깎음 표시
                        simul(row-1, col, dist+1);
                        //원상복구
                        flag = 0;
                        table[row-1][col] = tempH;
                    }
                }//다른데 깎은적 없으면
            }//나보다 높거나 같으면
        }//방문안하고
    }//위쪽으로 확인
    if(row+1 < N) { //아래쪽확인
        if(visited[row+1][col] == 0) {  //방문안하고
            if(table[row+1][col] < table[row][col]) {   //나보다 낮으면
                simul(row+1, col, dist+1);
            } //나보다 낮으면
            else {  //나보다 높거나 같으면
                if(flag == 0) { //다른데 깎은적 없으면
                    //나보다 더 낮게 만들수 있는지 확인
                    if(table[row+1][col] - K < table[row][col]) {   //더 낮게 만들수있으면 나보다 딱 1더작게만든다
                        tempH = table[row+1][col];
                        table[row+1][col] = table[row][col] - 1;
                        flag = 1;   //깎음 표시
                        simul(row+1, col, dist+1);
                        //원상복구
                        flag = 0;
                        table[row+1][col] = tempH;
                    }
                }//다른데 깎은적 없으면
            }//나보다 높거나 같으면
        }//방문안하고
    }//아래쪽확인
    if(col-1 >= 0) {    //왼쪽확인
        if(visited[row][col-1] == 0) {  //방문안하고
            if(table[row][col-1] < table[row][col]) {   //나보다 낮으면
                simul(row, col-1, dist+1);
            } //나보다 낮으면
            else {  //나보다 높거나 같으면
                if(flag == 0) { //다른데 깎은적 없으면
                    //나보다 더 낮게 만들수 있는지 확인
                    if(table[row][col-1] - K < table[row][col]) {   //더 낮게 만들수있으면 나보다 딱 1더작게만든다
                        tempH = table[row][col-1];
                        table[row][col-1] = table[row][col] - 1;
                        flag = 1;   //깎음 표시
                        simul(row, col-1, dist+1);
                        //원상복구
                        flag = 0;
                        table[row][col-1] = tempH;
                    }
                }//다른데 깎은적 없으면
            }//나보다 높거나 같으면
        }//방문안하고
    } //왼쪽확인
    if(col+1 < N) { //오른쪽확인
        if(visited[row][col+1] == 0) {  //방문안하고
            if(table[row][col+1] < table[row][col]) {   //나보다 낮으면
                simul(row, col+1, dist+1);
            } //나보다 낮으면
            else {  //나보다 높거나 같으면
                if(flag == 0) { //다른데 깎은적 없으면
                    //나보다 더 낮게 만들수 있는지 확인
                    if(table[row][col+1] - K < table[row][col]) {   //더 낮게 만들수있으면 나보다 딱 1더작게만든다
                        tempH = table[row][col+1];
                        table[row][col+1] = table[row][col] - 1;
                        flag = 1;   //깎음 표시
                        simul(row, col+1, dist+1);
                        //원상복구
                        flag = 0;
                        table[row][col+1] = tempH;
                    }
                }//다른데 깎은적 없으면
            }//나보다 높거나 같으면
        }//방문안하고
    } //오른쪽확인
    
    visited[row][col] = 0;
}


int main(void) {
    int T, t;
    int maxH;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d", &N, &K);
        
        maxH = 0;
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &table[i][j]);
                if(table[i][j] > maxH) {    //가장 높은 봉우리 높이 알아내기
                    maxH = table[i][j];
                }
                visited[i][j] = 0;
            }
        }
        
        //초기화
        flag = 0;
        maxDist = 0;
        
        //함수호출
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(table[i][j] == maxH) {
                    simul(i, j, 1);
                }
            }
        }
        
        printf("#%d %d\n", t, maxDist);
        
        //정답출력
    
    }
    
    return 0;
}
