//
//  모의ST_보물상자비밀번호.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/08.
//  Copyright © 2020 송혜경. All rights reserved.
//  ** (40min, F : 0)

#include <cstdio>
using namespace std;

int g_N = 0;    //입력으로 받는 숫자들의 개수
int g_K = 0;    //입력으로 받는 K
int g_value[40] = {0,};    //각 변으로 만들 수 있는 숫자들 저장(10진수)
int g_valueIdx = 0; //values배열의 인덱스
int g_number[30] = {0,};    //입력으로 받는 숫자들을 10진수로 저장
int g_tempValue[40] = {0, };    //g_value값을 정렬할때 사용
int g_KthNum = 0;   //K번째로 큰수

/// merge시킨다 (내림차순!)
/// @param s1 부분배열1의 시작인덱스
/// @param e1 부분배열1의 끝 인덱스
/// @param s2 부분배열2의 시작인덱스
/// @param e2 부분배열2의 끝 인덱스
void merging(int s1, int e1, int s2, int e2) {
    int idx = 0;
    int p = s1;
    int q = s2;
    int i = 0;
    
    while(p<=e1 && q<=e2) {
        if(g_value[p] > g_value[q]) {
            g_tempValue[idx] = g_value[p];
            idx++;
            p++;
        } else {
            g_tempValue[idx] = g_value[q];
            idx++;
            q++;
        }
    }
    
    while(p <= e1) {
        g_tempValue[idx] = g_value[p];
        idx++;
        p++;
    }
    
    while(q <= e2) {
        g_tempValue[idx] = g_value[q];
        idx++;
        q++;
    }
    
    for(i=0; i<idx; i++) {
        g_value[s1+i] = g_tempValue[i];
    }
}

/// 내림차순 정렬
/// @param start 합병정렬 시킬 시작 인덱스
/// @param end 합병정렬 시킬 마지막 인덱스
void merge_sort(int start, int end) {
    int mid = 0;
    
    if(start < end) {
        mid = (start + end) / 2;
        merge_sort(start, mid);
        merge_sort(mid+1, end);
        merging(start, mid, mid+1, end);
    }
}

void get_Kth_value(void) {
    int cnt = 1;
    int tempValue = -1;
    int i;
    
    //같은 숫자는 제외시키고 K번째로 큰 수를 찾느다
    for(i=0; i<g_valueIdx; i++) {
        if(tempValue == g_value[i]) {   //같은 숫자 제외
            continue;
        }
        if(cnt == g_K) {
            g_KthNum = g_value[i];
            break;
        }
        tempValue = g_value[i];
        cnt += 1;
    }
}

/// 보물상자를 회전시켜 생성가능한 숫자들을 모두 구한다
/// @param rotateCnt 현재까지 회전 시킨 횟수
/// @param endCnt 회전을 종료시킬 횟수
void get_values(int rotateCnt, int endCnt) {
    int tempNum = 0;
    int multi = 0;
    int tempMulti = 0;
    int i;
    
    if(rotateCnt == endCnt) {   //종료부
        return;
    } else {    //재귀호출부
        //10진수로 변환해서 저장
        multi = 1;
        for(i=0; i<endCnt-1; i++) {
            multi *= 16;
        }
        tempMulti = multi;
        tempNum = 0;
        //현재 숫자들을 구해서 g_value배열에 저장
        for(i=1; i<=g_N; i++) {
            tempNum += g_number[i] * tempMulti;
            if(tempMulti == 1) {
                g_value[g_valueIdx] = tempNum;
                g_valueIdx++;
                tempMulti = multi;
                tempNum = 0;
            } else {
                tempMulti /= 16;
            }
        }
        
        //회전시키기
        for(i=g_N; i>=1; i--) {
            g_number[i+1] = g_number[i];
        }
        g_number[1] = g_number[g_N+1];
        
        //재귀호출
        get_values(rotateCnt+1, endCnt);
    }
    //end 재귀호출부
}

int main(void) {
    int T, t;
    char str[31];
    int endCnt = 0;
    int i;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d", &g_N, &g_K);
        scanf("%s", str);
        
        //입력받은 숫자들을 10진수로 변환해서 저장
        for(i=0; i<g_N; i++) {
            if(str[i] >= '0' && str[i] <= '9') {
                g_number[i+1] = str[i] - '0';
            } else {
                g_number[i+1] = str[i] - 'A' + 10;
            }
        }
        
        //생성한 가능한 모든 숫자를 구한다
        endCnt = g_N / 4;
        g_valueIdx = 0;
        get_values(0, endCnt);
        //정렬
        merge_sort(0, g_valueIdx-1);
        //K번째 수 구하기
        get_Kth_value();
        
        //정답 출력
        printf("#%d %d\n", t, g_KthNum);
    }
    
    return 0;
}
