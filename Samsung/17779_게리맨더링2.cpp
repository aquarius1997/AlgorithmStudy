//
//  17779_게리맨더링2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/04.
//  Copyright © 2020 송혜경. All rights reserved.
//  1h 10min. ****

#include <cstdio>
using namespace std;

int g_d1 = 0;
int g_d2 = 0;
int g_N = 0;
int g_A[22][22] = {0, };
int g_line[22][22] = {0, };
int g_totalSum = 0;
int g_minDiff = 987987987;

/// 각 구역의 인구수를 구해, 최대 인구수와 최소 인구수의 차이를 구한다
/// @param row 시작 행
/// @param col 시작 열
void get_min_diff(int row, int col) {
    int area1Sum, area2Sum, area3Sum, area4Sum, area5Sum;
    int maxSum = 0;
    int minSum = 987987987;
    int r, c;
    
    area1Sum = area2Sum = area3Sum = area4Sum = area5Sum = 0;
    
    //구역1
    for(r=0; r<row; r++) {
        for(c=col; c>=0; c--) {
            area1Sum += g_A[r][c];
        }
    }
    for(r=row ;r<row+g_d1; r++) {
        for(c=0; c<g_N; c++) {
            if(g_line[r][c] == 5) { break; }
            else {
                area1Sum += g_A[r][c];
            }
        }
    }
    
    maxSum = minSum = area1Sum;
    
    //구역2
    for(r=0; r<row; r++) {
        for(c=g_N-1; c>col; c--) {
            area2Sum += g_A[r][c];
        }
    }
    for(r=row; r<=row+g_d2; r++) {
        for(c=g_N-1; c>=0; c--) {
            if(g_line[r][c] == 5) { break; }
            else {
                area2Sum += g_A[r][c];
            }
        }
    }
    
    if(area2Sum > maxSum) { maxSum = area2Sum; }
    if(area2Sum < minSum) { minSum = area2Sum; }
    
    //구역3
    for(r=g_N-1; r>row+g_d1+g_d2; r--) {
        for(c=0; c<col-g_d1+g_d2; c++) {
            area3Sum += g_A[r][c];
        }
    }
    for(r=row+g_d1+g_d2; r>=row+g_d1; r--) {
        for(c=0; c<g_N; c++) {
            if(g_line[r][c] == 5) { break;}
            else {
                area3Sum += g_A[r][c];
            }
        }
    }
    
    if(area3Sum > maxSum) { maxSum = area3Sum; }
    if(area3Sum < minSum) { minSum = area3Sum; }
    
    //구역4
    for(r=g_N-1; r>row+g_d1+g_d2; r--) {
        for(c=g_N-1; c>=col-g_d1+g_d2; c--) {
            area4Sum += g_A[r][c];
        }
    }
    for(r=row+g_d1+g_d2; r>row+g_d2; r--) {
        for(c=g_N-1; c>=0; c--) {
            if(g_line[r][c] == 5) { break; }
            else {
                area4Sum += g_A[r][c];
            }
        }
    }
    
    if(area4Sum > maxSum) { maxSum = area4Sum; }
    if(area4Sum < minSum) { minSum = area4Sum; }
    
    //구역5
    area5Sum = g_totalSum - (area1Sum + area2Sum + area3Sum + area4Sum);
    
    if(area5Sum > maxSum) { maxSum = area5Sum; }
    if(area5Sum < minSum) { minSum = area5Sum; }
    
    if(maxSum - minSum < g_minDiff) {
        g_minDiff = maxSum - minSum;
    }
}

void make_5_line(int row, int col) {
    int i;
    
    //5라인 그리기
    g_line[row][col] = 5;
    for(i=1; i<=g_d1; i++) {    //구역1과 맡닿은 라인
        g_line[row+i][col-i] = 5;
    }
    for(i=1; i<=g_d2; i++) {    //구역2와 맡닿은 라인
        g_line[row+i][col+i] = 5;
    }
    for(i=1; i<=g_d2; i++) {    //구역3과 맡닿은 라인
        g_line[row+g_d1+i][col-g_d1+i] = 5;
    }
    for(i=1; i<=g_d1; i++) {    //구역 4와 맡닿은 라인
        g_line[row+g_d2+i][col+g_d2-i] = 5;
    }
    
    //구역의 크기를 구해 최대 최소의 차이를 구하는 함수를 호출
    get_min_diff(row, col);
    
    //초기화
    g_line[row][col] = 0;
    for(i=1; i<=g_d1; i++) {    //구역1과 맡닿은 라인
        g_line[row+i][col-i] = 0;
    }
    for(i=1; i<=g_d2; i++) {    //구역2와 맡닿은 라인
        g_line[row+i][col+i] = 0;
    }
    for(i=1; i<=g_d2; i++) {    //구역3과 맡닿은 라인
        g_line[row+g_d1+i][col-g_d1+i] = 0;
    }
    for(i=1; i<=g_d1; i++) {    //구역 4와 맡닿은 라인
        g_line[row+g_d2+i][col+g_d2-i] = 0;
    }
}

/// g_d1과 g_d2의 길이를 바탕으로 세번째 구역과 4번째 구역이 범위 이내인지 확인한다. 범위 이내일 경우 5구역의 경계선을 만드는 함수를 호출
/// @param row 시작 행
/// @param col 시작 열
void area_3(int row, int col) {
    if(row + g_d1 + g_d2 < g_N) {
        if(col - g_d1 + g_d2 < g_N) {   //범위 이내
            make_5_line(row, col);
        }
    }
}

/// 2번째 구역의 범위를 확인하며 g_d2의 길이를 구한다
/// @param row 시작 행
/// @param col 시작 열
void area_2(int row, int col) {
    int i;
    
    for(i=1; ; i++) {
        if((row + i < g_N) && (col + i < g_N)) {
            g_d2 = i;
            area_3(row, col);
        } else { break; }
    }
}

/// 1번째 구역의 범위를 확인하며 g_d1의 길이를 구한다
/// @param row 시작 행
/// @param col 시작 열
void area_1(int row, int col) {
    int i;
    
    for(i=1; ; i++) {   //g_d1 의 유효한 길이를 확인
        if((row + i < g_N) && (col - i >= 0)) { //범위를 벗어나지 않으면 두번째 2번째 구역을 확인한다
            g_d1 = i;   //g_d1의 길이를 i로
            area_2(row, col);
        } else { break; }
    }
}

int main(void) {
    int i, j;
    
    scanf("%d", &g_N);
    //재현시 입력받기
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            scanf("%d", &g_A[i][j]);
            g_totalSum += g_A[i][j];    //전체 인구수
        }
    }
    
    for(i=0; i<g_N; i++) {
        for(j=0; j<g_N; j++) {
            area_1(i, j);
        }
    }
    
    printf("%d", g_minDiff);
    
    return 0;
}
