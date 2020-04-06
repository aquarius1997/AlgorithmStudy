//
//  17140_이차원배열과연산.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** 처음에 시간 복잡도를 잘못 계산해서 꼬아서 풀려고 함. 시간 낭비 엄청했어 ㅠㅠㅠㅠ 바보

#include <cstdio>
using namespace std;

int numbers[102][102] = {0, };
int counting[102] = {0, };
int rNum = 0;   //행 개수
int cNum = 0;   //열 개수
int minTime = -1;    //연산 최소 시간
int r, c, k;

void simul(int timeCnt) {
    int idx = 0;
    int num;
    int maxCnt = 0;
    int i, j;
    
    //종료조건
    if(timeCnt > 100) {
        return;
    }
    if(r < rNum && c < cNum) {
        if(numbers[r][c] == k) {
            minTime = timeCnt;  return;
        }
    }
    
    //R연산
    if(rNum >= cNum) {
        maxCnt = 0;
        for(i=0; i<rNum; i++) { //각 행에 대하여 카운팅 배열에 숫자 카운트
            //숫자 카운트
            for(j=0; j<cNum; j++) {
                num = numbers[i][j];
                counting[num]++;
            }
            //counting 배열 가지고 정렬
            num = 1;
            idx = 0;
            while(num <= 100) {
                for(j=1; j<=100; j++) {
                    if(counting[j] == num) {
                        numbers[i][idx] = j;
                        idx++;
                        numbers[i][idx] = num;
                        idx++;
                    }
                    if(idx >= 100) { break;}
                }
                if(idx >= 100) { break;}
                num++;
            }
            for(j=idx; j<100; j++) {
                numbers[i][j] = 0;
            }
            for(j=0; j<101; j++) { counting[j] = 0; }
            if(idx > maxCnt) {
                maxCnt = idx;
            }
        }
        if(maxCnt > cNum) { //열 개수 업데이트
            cNum = maxCnt;
        }
    } else {    //C연산
        maxCnt = 0;
        for(j=0; j<cNum; j++) { //각 열에 대하여 카운팅 배열에 숫자 카운트
            for(i=0; i<rNum; i++) {
                num = numbers[i][j];
                counting[num]++;
            }
            //counting 배열로 정렬
            num = 1;
            idx = 0;
            while(num <= 100) {
                for(i=1; i<=100; i++) {
                    if(counting[i] == num) {
                        numbers[idx][j] = i;
                        idx++;
                        numbers[idx][j] = num;
                        idx++;
                    }
                    if(idx >= 100) { break;}
                }
                if(idx >= 100) { break;}
                num++;
            }
            for(i=idx; i<100; i++) {
                numbers[i][j] = 0;
            }
            for(i=0; i<101; i++) { counting[i] = 0; }
            if(idx > maxCnt) {
                maxCnt = idx;
            }
        }
        if(maxCnt > rNum) { //행 개수 업데이트
            rNum = maxCnt;
        }
    }
    
    //재귀호출
    simul(timeCnt+1);
}

int main(void) {
    int i, j;
    
    scanf("%d %d %d", &r, &c, &k);
    
    r -= 1;
    c -= 1;
    
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            scanf("%d", &numbers[i][j]);
        }
    }
    rNum = cNum = 3;
    
    simul(0);
    
    printf("%d", minTime);
    
    return 0;
}
