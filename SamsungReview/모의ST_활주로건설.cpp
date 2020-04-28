//
//  모의ST_활주로건설.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <cstdio>

int g_table[22][22] = {0, };
int g_constructed[22][22] = {0, };  //이미 경사로를 놓은 위치는 1로 저장
int g_X = 0;    //경사로 길이
int g_N = 0;    //테이블 크기

int construction(void) {
    int flag = 0;   //건설 가능 여부 플래그
    int cnt = 0;    //건설 가능한 경우의 수 카운팅
    int h = 0;
    int i, j, k;
    
    //가로로 건설
    for(i=0; i<g_N; i++) {
        h = g_table[i][0];  //높이 초기화
        flag = 0;   //건설 가능 불가능시 1로 저장
        //1) 해당 행에 대하여 활주로 건설 시작
        for(j=1; j<g_N;) {
            if(g_table[i][j] == h) {    //높이 동일
                j++;
            } else if(g_table[i][j] == (h+1)){  //1만큼 높아지면
                //현재 위치 이전으로 X길이만큼 길이 동일한지 확인
                for(k=0; k<g_X; k++) {
                    if(j-1-k < 0 ) {    //범위 밖이면 불가능
                        flag = 1;   break;
                    } else if(g_table[i][j-1-k] != g_table[i][j-1] || g_constructed[i][j-1-k] == 1) {   //이미 활주로를 건설했거나 높이 일정하지 않으면 불가능
                        flag = 1;   break;
                    }
                }
                if(flag == 1) { break; }    //건설 불가능
                else {  //건설하기
                    for(k=0; k<g_X; k++) {
                        g_constructed[i][j-1-k] = 1;
                    }
                    //기준 높이 저장, 루프 카운팅
                    h = g_table[i][j];
                    j++;
                }   //건설하기
            } else if(g_table[i][j] == (h-1)) { //1만큼 낮아졌으면
                //현재 위치를 포함해서 앞으로 X길이만큼 길이 동일한지 확인
                for(k=0; k<g_X; k++) {
                    if(j+k > g_N) { //범위밖 불가능
                        flag = 1;   break;
                    } else if(g_table[i][j+k] != g_table[i][j] || g_constructed[i][j+k] == 1) { //이미 활주로를 건설했거나 높이가 일정하지 않으면 불가능
                        flag = 1;   break;
                    }
                }
                if(flag == 1) { break; }    //건설불가능
                else {  //건설하기
                    for(k=0; k<g_X; k++) {
                        g_constructed[i][j+k] = 1;
                    }
                    //기준 높이 저장, 루프 카운팅
                    h = g_table[i][j];
                    j = j + g_X;
                }
            } else { //건설불가능
                flag = 1;   break;
            }
        }
        //end 1)
        if(flag == 0) { //해당 행에 대해 건설 가능한 경우
            cnt++;
        }
    }
    //end 가로로 건설
    
    //constructed배열 초기화
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            g_constructed[i][j] = 0;
        }
    }
    
    //세로로 건설
    for(j=0; j<g_N; j++) {
        h = g_table[0][j];  //높이 초기화
        flag = 0;   //건설 가능 불가능시 1로 저장
        //1) 해당 열에 대하여 활주로 건설 시작
        for(i=1; i<g_N;) {
            if(g_table[i][j] == h) {    //높이 동일
                i++;
            } else if(g_table[i][j] == (h+1)){  //1만큼 높아지면
                //현재 위치 이전으로 X길이만큼 길이 동일한지 확인
                for(k=0; k<g_X; k++) {
                    if(i-1-k < 0 ) {    //범위 밖이면 불가능
                        flag = 1;   break;
                    } else if(g_table[i-1-k][j] != g_table[i-1][j] || g_constructed[i-1-k][j] == 1) {   //이미 활주로를 건설했거나 높이 일정하지 않으면 불가능
                        flag = 1;   break;
                    }
                }
                if(flag == 1) { break; }    //건설 불가능
                else {  //건설하기
                    for(k=0; k<g_X; k++) {
                        g_constructed[i-1-k][j] = 1;
                    }
                    //기준 높이 저장, 루프 카운팅
                    h = g_table[i][j];
                    i++;
                }   //건설하기
            } else if(g_table[i][j] == (h-1)) { //1만큼 낮아졌으면
                //현재 위치를 포함해서 앞으로 X길이만큼 길이 동일한지 확인
                for(k=0; k<g_X; k++) {
                    if(i+k > g_N) { //범위밖 불가능
                        flag = 1;   break;
                    } else if(g_table[i+k][j] != g_table[i][j] || g_constructed[i+k][j] == 1) { //이미 활주로를 건설했거나 높이가 일정하지 않으면 불가능
                        flag = 1;   break;
                    }
                }
                if(flag == 1) { break; }    //건설불가능
                else {  //건설하기
                    for(k=0; k<g_X; k++) {
                        g_constructed[i+k][j] = 1;
                    }
                    //기준 높이 저장, 루프 카운팅
                    h = g_table[i][j];
                    i = i + g_X;
                }
            } else { //건설불가능
                flag = 1;   break;
            }
        }
        //end 1)
        if(flag == 0) { //해당 행에 대해 건설 가능한 경우
            cnt++;
        }
    }
    //end 세로로 건설
    
    //경우의 수 리턴
    return cnt;
}

int main(void) {
    int answer = 0; //정답
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //1. 입력받기
        scanf("%d %d", &g_N, &g_X);
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                scanf("%d", &g_table[i][j]);
            }
        }
        //end 1
        
        //2.함수호출
        answer = construction();
        
        //3. 정답출력
        printf("#%d %d\n", t, answer);
        
        //4. 초기화
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                g_constructed[i][j] = 0;
            }
        }
    }
    
    
    return 0;
}
