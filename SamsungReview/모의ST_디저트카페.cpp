//
//  모의ST_디저트카페.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  1h 30min. ***** 예외사항 처리

#include <cstdio>
using namespace std;

int g_visited[102] = {0,};    //먹은 디저트 번호는 1로 저장
int g_table[22][22] = {0,};
int g_N = 0;
int g_max = -1;

void get_last(int r, int c, int d1, int d2) {
    int d = 1;
    int endD;
    int element, td;
    int breakFlag = 0;
    
    for(d=1; d<=d1; d++) {
        if(r+d2+d >= g_N || c+d2-d < 0) {
            breakFlag = 1;
        } else {
            element = g_table[r+d2+d][c+d2-d];
            if(g_visited[element] == 1) {
                breakFlag = 1;
            } else {
                g_visited[element] = 1;
            }
        }
        
        if(breakFlag == 1) {
            break;
        }
    }
    
    endD = d;
    
    if(breakFlag == 0) {
        for(d=1; d<d2; d++) {
            if(r+d1+d >= g_N || c-d1+d >= g_N) {
                breakFlag = 1;
            } else {
                element = g_table[r+d1+d][c-d1+d];
                if(g_visited[element] == 1) {
                    breakFlag = 1;
                } else {
                    g_visited[element] = 1;
                }
            }
            
            if(breakFlag == 1) {
                break;
            }
        }
            
        if(breakFlag == 0) {
            if((d1+1)*2 + (d2+1)*2 - 4 > g_max) {
                g_max =(d1+1)*2 + (d2+1)*2 - 4;
            }
        }
        
        for(td=1; td<d; td++) {
            element = g_table[r+d1+td][c-d1+td];
            g_visited[element] = 0;
        }
    }

    //초기화
    for(td=1; td<endD; td++) {
        element = g_table[r+d2+td][c+d2-td];
        g_visited[element] = 0;
    }

}

void get_d2(int r, int c, int d1) {
    int d2 = 1;
    int d;
    int element;
    int breakFlag = 0;
    
    while(1) {
        if(r+d2 >= g_N || c+d2 >= g_N) {
            breakFlag = 1;
        } else {
            element = g_table[r+d2][c+d2];
            if(g_visited[element] == 0) {   //디저트 안겹침
                g_visited[element] = 1;
                //호출
                get_last(r, c, d1, d2);
            } else { //겹침
                breakFlag = 1;
            }
        }
        
        if(breakFlag == 1) {
            for(d=1; d<d2; d++) {
                element = g_table[r+d][c+d];
                g_visited[element] = 0;
            }
            break;
        }
        d2++;
    }//end while(1)
}

int main(void) {
    int t, T;
    int element;
    int breakFlag = 0;
    int i, j, d, td;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d", &g_N);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                scanf("%d", &g_table[i][j]);
            }
        }
        
        //시뮬레이션
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                //출발점으로부터 시작
                breakFlag = 0;
                d = 1;
                element = g_table[i][j];
                g_visited[element] = 1;
                
                while(1) {
                    if(i+d >= g_N || j-d < 0) { //범위 벗어나면
                        breakFlag = 1;
                    } else {
                        element = g_table[i+d][j-d];
                        if(g_visited[element] == 0) {   //디저트 종류 안겹치면
                            g_visited[element] = 1;
                            get_d2(i, j, d);
                        } else {
                            breakFlag = 1;
                        }
                    }
                    
                    if(breakFlag == 1) {    //visited초기화하고 루프 나감
                        for(td=1; td<d; td++) {
                            element = g_table[i+td][j-td];
                            g_visited[element] = 0;
                        }
                        break;
                    }
                    d++;
                }   //end while(1)
                
                element = g_table[i][j];
                g_visited[element] = 0;
            }
        }
        
        //정답출력
        printf("#%d %d\n", t, g_max);
        
        //초기화
        g_max = -1;
    }
    
    return 0;
}
