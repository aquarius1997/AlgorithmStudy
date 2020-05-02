//
//  모의ST_등산로조성.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/02.
//  Copyright © 2020 송혜경. All rights reserved.
//  20min. *** (프로세스 잘 생각하면 무리 없음. 아주 좋은 문제같음)

#include <cstdio>
using namespace std;

int g_table[10][10] = {0,};
int g_visited[10][10] = {0,};
int g_K = 0;
int g_N = 0;
int g_maxDist = 0;

void bfs_moving(int r, int c, int flag, int dist) {
    int height = g_table[r][c]; //현재 위치의 높이
    int tempHeight = 0;
    int diff = 0;
    
    g_visited[r][c] = 1;
    
    //등산로 최대 거리 업데이트하기
    if(dist > g_maxDist) {
        g_maxDist = dist;
    }
    //상하좌우 확인
    if(r-1 >= 0) {
        if(g_visited[r-1][c] == 0) {    //방문한적없
            if(g_table[r-1][c] >= height) {            //깎아야 하는 경우
                diff = g_table[r-1][c] - (height - 1);  //깎아야 하는 높이
                if(diff <= g_K && flag == 0) {   //깎을 수 있으면
                    //잠시 높이 변경
                    tempHeight = g_table[r-1][c];
                    g_table[r-1][c] = height - 1;
                    //함수호출
                    bfs_moving(r-1, c, 1, dist+1);
                    //원상복구
                    g_table[r-1][c] = tempHeight;
                }
            } else {    //깎을 필요 없는 경우
                bfs_moving(r-1, c, flag, dist+1);
            }   //end 깎을 필요 없
        }   //방문한적업스면
    }
    if(r+1 < g_N) { //아래이동 확인
        if(g_visited[r+1][c] == 0) {    //방문안했으면
            if(g_table[r+1][c] >= height) {
                diff = g_table[r+1][c] - (height - 1);
                if(diff <= g_K && flag == 0) {
                    tempHeight = g_table[r+1][c];
                    g_table[r+1][c] = height - 1;
                    bfs_moving(r+1, c, 1, dist+1);
                    g_table[r+1][c] = tempHeight;
                }
            } else {
                bfs_moving(r+1, c, flag, dist+1);
            }
        }   //end 방문안했
    }
    if(c-1 >= 0) {  //왼쪽이동확인
        if(g_visited[r][c-1] == 0) {
            if(g_table[r][c-1] >= height) {
                diff = g_table[r][c-1] - (height - 1);
                if(diff <= g_K && flag == 0) {
                    tempHeight = g_table[r][c-1];
                    g_table[r][c-1] = height - 1;
                    bfs_moving(r, c-1, 1, dist+1);
                    g_table[r][c-1] = tempHeight;
                }
            } else {
                bfs_moving(r, c-1, flag, dist+1);
            }
        }
    }
    if(c+1 < g_N) { //오른쪽 이동 확인
        if(g_visited[r][c+1] == 0) {
            if(g_table[r][c+1] >= height) {
                diff = g_table[r][c+1] - (height - 1);
                if(diff <= g_K && flag == 0) {
                    tempHeight = g_table[r][c+1];
                    g_table[r][c+1] = height - 1;
                    bfs_moving(r, c+1, 1, dist+1);
                    g_table[r][c+1] = tempHeight;
                }
            } else {
                bfs_moving(r, c+1, flag, dist+1);
            }
        }
    }
    //end 상하좌우 확인
    
    
    g_visited[r][c] = 0;
}

int main(void) {
    int t, T;
    int maxHeight = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d", &g_N, &g_K);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                scanf("%d", &g_table[i][j]);
                if(g_table[i][j] > maxHeight) {
                    maxHeight = g_table[i][j];
                }
            }
        }
        
        //함수 호출
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                if(g_table[i][j] == maxHeight) {
                    bfs_moving(i, j, 0, 1);
                }
            }
        }
        
        //정답 출력
        printf("#%d %d\n", t, g_maxDist);
        
        //초기화
        g_maxDist = 0;
        maxHeight = 0;
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                g_visited[i][j] = 0;
            }
        }
    }
    
    return 0;
}
