//
//  12100_2048Easy.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/06.
//  Copyright © 2020 송혜경. All rights reserved.
// 50min, FailCnt : 0   ****

#include <cstdio>
using namespace std;

int g_table[22][22] ={0,};
int g_N = 0;
int g_max = 0;


void dfs_simul(int cnt) {
    int tempT[22][22] = {0,};
    int startIdx, compIdx, currentValue;
    int flag = 0;
    int i, j;
    
    if(cnt >= 5) {
        //정답구하고
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_N; j++) {
                if(g_table[i][j] > g_max) {
                    g_max = g_table[i][j];
                }
            }
        }
        
        return;
    }
    //임시 저장
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            tempT[i][j] = g_table[i][j];
        }
    }
    
    //1. 위로 스윕
    for(j=0; j<g_N; j++) {    //열들에대해
        startIdx = 0;   //값이 안바뀐 인덱스 저장
        for(i=1; i<g_N; i++) {  //위쪽에서 부터
            if(g_table[i][j] != 0) {    //숫자 있으면
                flag = 0;   //같은숫자 찾아서 업데이트하면 1로 변경
                currentValue = g_table[i][j];   //이동시킬 요소의 값
                compIdx = i-1;   // 값을 비교할 인덱스
                while(compIdx >= startIdx) {    //위로 올라가며 값 비교
                    if(g_table[compIdx][j] == currentValue) { //값이 같은거 찾으면
                        g_table[compIdx][j] *= 2;
                        g_table[i][j] = 0;
                        startIdx = compIdx+1;
                        flag = 1;
                        break;
                    }//값이 같은거 찾으면
                    compIdx--;
                }   //위로 올라가며 값 비교
                if(flag == 0) {   //값 같은거 없었으면 가장 위로 올리기
                    if(g_table[startIdx][j] == 0) { //빈곳이면
                        g_table[startIdx][j] = currentValue;
                        g_table[i][j] = 0;
                    } else {    //빈곡아니면
                        if(startIdx+1 != i) {
                            g_table[startIdx+1][j] = currentValue;
                            g_table[i][j] = 0;
                        }
                        startIdx = startIdx+1;
                    }
                }//값 같은거 없었으면 가장 위로 올리기
            }   //숫자 있으면
        }//위쪽에서 부터
    }   //end 열들에 대해
    //재귀호출
    dfs_simul(cnt+1);
    //원상복구
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            g_table[i][j] = tempT[i][j];
        }
    }
    
    //2. 아래로 스윕
    for(j=0; j<g_N; j++) {    //열들에대해
        startIdx = g_N-1;   //값이 안바뀐 인덱스 저장
        for(i=g_N-2; i>=0; i--) {  //아래쪽에서 부터
            if(g_table[i][j] != 0) {    //숫자 있으면
                flag = 0;   //같은숫자 찾아서 업데이트하면 1로 변경
                currentValue = g_table[i][j];   //이동시킬 요소의 값
                compIdx = i+1;   // 값을 비교할 인덱스
                while(compIdx <= startIdx) {    //아래로 올라가며 값 비교
                    if(g_table[compIdx][j] == currentValue) { //값이 같은거 찾으면
                        g_table[compIdx][j] *= 2;
                        g_table[i][j] = 0;
                        startIdx = compIdx-1;
                        flag = 1;
                        break;
                    }//값이 같은거 찾으면
                    compIdx++;
                }   //아래로 올라가며 값 비교
                if(flag == 0) {   //값 같은거 없었으면 가장 위로 올리기
                    if(g_table[startIdx][j] == 0) { //빈곳이면
                        g_table[startIdx][j] = currentValue;
                        g_table[i][j] = 0;
                    } else {    //빈곡아니면
                        if(startIdx-1 != i) {   //이동한경우
                            g_table[startIdx-1][j] = currentValue;
                            g_table[i][j] = 0;
                        }
                        startIdx = startIdx-1;
                    }
                }//값 같은거 없었으면 가장 위로 올리기
            }   //숫자 있으면
        }//위쪽에서 부터
    }   //end 열들에 대해
    dfs_simul(cnt+1);
    //원상복구
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            g_table[i][j] = tempT[i][j];
        }
    }
    
    //3. 왼쪽으로 스윕
    //1. 위로 스윕
    for(i=0; i<g_N; i++) {    //행들에대해
        startIdx = 0;   //값이 안바뀐 인덱스 저장
        for(j=1; j<g_N; j++) {  //왼쪽에서 부터
            if(g_table[i][j] != 0) {    //숫자 있으면
                flag = 0;   //같은숫자 찾아서 업데이트하면 1로 변경
                currentValue = g_table[i][j];   //이동시킬 요소의 값
                compIdx = j-1;   // 값을 비교할 인덱스
                while(compIdx >= startIdx) {    //왼쪽으로 이동하며 값 비교
                    if(g_table[i][compIdx] == currentValue) { //값이 같은거 찾으면
                        g_table[i][compIdx] *= 2;
                        g_table[i][j] = 0;
                        startIdx = compIdx+1;
                        flag = 1;
                        break;
                    }//값이 같은거 찾으면
                    compIdx--;
                }   //왼쪽으로 이동하며 값 비교
                if(flag == 0) {   //값 같은거 없었으면 가장 왼쪽으로 옮기기
                    if(g_table[i][startIdx] == 0) { //빈곳이면
                        g_table[i][startIdx] = currentValue;
                        g_table[i][j] = 0;
                    } else {    //빈곡아니면
                        if(startIdx+1 != j) {
                            g_table[i][startIdx+1] = currentValue;
                            g_table[i][j] = 0;
                        }
                        startIdx = startIdx+1;
                    }
                }//값 같은거 없었으면 가장 왼쪽으로 옮기기
            }   //숫자 있으면
        }//왼쪽에서 부터
    }   //end 행들에 대해
    //재귀호출
    dfs_simul(cnt+1);
    //원상복구
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            g_table[i][j] = tempT[i][j];
        }
    }
    
    //4. 오른쪽으로 스윕
    for(i=0; i<g_N; i++) {    //행들에대해
        startIdx = g_N-1;   //값이 안바뀐 인덱스 저장
        for(j=g_N-2; j>=0; j--) {  //오른쪽에서 부터
            if(g_table[i][j] != 0) {    //숫자 있으면
                flag = 0;   //같은숫자 찾아서 업데이트하면 1로 변경
                currentValue = g_table[i][j];   //이동시킬 요소의 값
                compIdx = j+1;   // 값을 비교할 인덱스
                while(compIdx <= startIdx) {    //오른쪽으로 이동하며 값 비교
                    if(g_table[i][compIdx] == currentValue) { //값이 같은거 찾으면
                        g_table[i][compIdx] *= 2;
                        g_table[i][j] = 0;
                        startIdx = compIdx-1;
                        flag = 1;
                        break;
                    }//값이 같은거 찾으면
                    compIdx++;
                }   //왼쪽으로 이동하며 값 비교
                if(flag == 0) {   //값 같은거 없었으면 가장 오른쪽으로 옮기기
                    if(g_table[i][startIdx] == 0) { //빈곳이면
                        g_table[i][startIdx] = currentValue;
                        g_table[i][j] = 0;
                    } else {    //빈곡아니면
                        if(startIdx-1 != j) {
                            g_table[i][startIdx-1] = currentValue;
                            g_table[i][j] = 0;
                        }
                        startIdx = startIdx-1;
                    }
                }//값 같은거 없었으면 가장 왼쪽으로 옮기기
            }   //숫자 있으면
        }//왼쪽에서 부터
    }   //end 행들에 대해
    //재귀호출
    dfs_simul(cnt+1);
    //원상복구
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            g_table[i][j] = tempT[i][j];
        }
    }
}



int main(void) {
    int i, j;
    
    scanf("%d", &g_N);
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            scanf("%d", &g_table[i][j]);
        }
    }
    
    dfs_simul(0);
    
    printf("%d", g_max);
    
    return 0;
}
