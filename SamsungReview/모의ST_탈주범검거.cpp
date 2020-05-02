//
//  모의ST_탈주범검거.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/02.
//  Copyright © 2020 송혜경. All rights reserved.
//  55min **** (프로세스 잘 생각해보기)

#include <cstdio>
#include <queue>
using namespace std;

int g_N = 0;
int g_M = 0;
int g_table[52][52] = {0,};
int g_visited[52][52] = {0,};
queue<int> Queue;

/// 범인의 첫번째 위치(맨홀위치)를 입력받아, 이동 가능한 구역들을 모두 이동시킨다. 그리고 g_visited배열에 해당 위치의 이동 시간을 저장한다
/// @param R 맨홀 행 위치
/// @param C 맨홀 열 위치
void move_bfs(int R, int C) {
    int r, c;
    int nextTime = 0;
    int kinds, nextKinds;
    
    //맨홀 시작
    g_visited[R][C] = 1;
    Queue.push(R);
    Queue.push(C);

    while(!Queue.empty()) {
        r = Queue.front();
        Queue.pop();
        c = Queue.front();
        Queue.pop();
        //현재 위치의 터널 모양을 알아낸다
        kinds = g_table[r][c];
        nextTime = g_visited[r][c] + 1;
        
        if(kinds == 1 || kinds == 2 || kinds == 4 || kinds == 7) {        //위로 움직일 수 있는 경우
            if(r-1 >= 0) {  //범위 확인
                if(g_visited[r-1][c] == 0) {  //방문 여부 확인
                    nextKinds = g_table[r-1][c];    //위쪽의 터널 모양 알아내기
                    if(nextKinds == 1 || nextKinds == 2 || nextKinds == 5 || nextKinds == 6) {
                        g_visited[r-1][c] = nextTime;
                        Queue.push(r-1);
                        Queue.push(c);
                    }
                }
            }
        }
        if(kinds == 1 || kinds == 2 || kinds == 5 || kinds == 6) {   //아래로 움직일 수 있는 경우
            if(r+1 < g_N) {
                if(g_visited[r+1][c] == 0) {
                    nextKinds = g_table[r+1][c];
                    if(nextKinds == 1 || nextKinds == 2 || nextKinds == 4 || nextKinds == 7) {
                        g_visited[r+1][c] = nextTime;
                        Queue.push(r+1);
                        Queue.push(c);
                    }
                }
            }
        }
        if(kinds == 1 || kinds == 3 || kinds == 6 || kinds == 7) {   //왼쪽으로 움직일 수 있는 경우
            if(c-1 >= 0) {
                if(g_visited[r][c-1] == 0) {
                    nextKinds = g_table[r][c-1];
                    if(nextKinds == 1 || nextKinds == 3 || nextKinds == 4 || nextKinds == 5) {
                        g_visited[r][c-1] = nextTime;
                        Queue.push(r);
                        Queue.push(c-1);
                    }
                }
            }
        }
        if(kinds == 1 || kinds == 3 || kinds == 4 || kinds == 5) {   //오른쪽으로 움직일 수 있는 경우
            if(c+1 < g_M) {
                if(g_visited[r][c+1] == 0) {
                    nextKinds = g_table[r][c+1];
                    if(nextKinds == 1 || nextKinds == 3 || nextKinds == 6 || nextKinds== 7) {
                        g_visited[r][c+1] = nextTime;
                        Queue.push(r);
                        Queue.push(c+1);
                    }
                }
            }
        }

    }   //end while

}

int main(void) {
    int T, t, R, C, L;
    int answer = 0;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d %d %d %d", &g_N, &g_M, &R, &C, &L);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_M; j++) {
                scanf("%d", &g_table[i][j]);
            }
        }
        
        //함수 호출
        move_bfs(R, C);
        //위치 개수 카운팅
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_M; j++) {
                if(g_visited[i][j] != 0 && g_visited[i][j] <= L) {
                    answer++;
                }
            }
        }
        
        //정답 출력
        printf("#%d %d\n", t, answer);
        
        //초기화
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_M; j++) {
                g_visited[i][j] = 0;
            }
        }
        answer = 0;
    }
    
    return 0;
}
