//
//  모의ST_디저트카페.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/28.
//  Copyright © 2020 송혜경. All rights reserved.
//  *** 개 어이없는 실수로 삼십분잡아먹음. 아무리 봐도 예외, 프로세스 문제가 없으면 변수 값 변경시 실수했음을 살펴보자

#include <cstdio>
#include <queue>
using namespace std;

int visited[101] = {0, };   //방문한 디저트는 1로
int cafe[21][21] = {0, };
int maxNum = -1;
int N;
int d1, d2;


/// 오른쪽 위로 올라감
/// @param row 시작행
/// @param col 시작열
void simul4(int row, int col) {
    queue<int> temp;
    int cafeNum;
    int flag2 = 0;
    
    for(int d=1; d<d2; d++) {
        if(row-d >= 0 && col+d < N) {
            cafeNum = cafe[row-d][col+d];
            if(visited[cafeNum] == 1) {
                flag2 = 1;
                break;
            } else {
                visited[cafeNum] = 1;
                temp.push(cafeNum);
            }
        } else {
            flag2 = 1;
        }
    }
    
    if(flag2 == 0) {
        int dist = (d1+d2);
        dist *= 2;
        if(maxNum < dist) {
            maxNum = dist;
        }
    }
    
    while(!temp.empty()) {
        cafeNum = temp.front();
        temp.pop();
        visited[cafeNum] = 0;
    }
    
}


/// 왼쪽 위로 올라감
/// @param row 시작 행
/// @param col 시작 열
void simul3(int row, int col) {
    int cafeNum;
    int flag1 = 0;  //왼쪽위로 올라가면서 중복된 디저트가 없는지 확인하는플래그
    queue<int> temp;
    
    for(int d=1; d<=d1; d++) {
        if(row-d >= 0 && col-d >=0) {
            cafeNum = cafe[row-d][col-d];
            if(visited[cafeNum] == 1) {
                flag1 = 1;
                break;
            } else {
                visited[cafeNum] = 1;
                temp.push(cafeNum);
            }
        } else {
            flag1 = 1;
        }
    }
    
    if(flag1 == 0) {
        //시뮬4호출
        simul4(row-d1, col-d1);
    }
    while(!temp.empty()) {
        cafeNum = temp.front();
        temp.pop();
        visited[cafeNum] = 0;
    }

}

/// 왼쪽 아래로 내려감
/// @param row 시작행
/// @param col 시작 열
void simul2(int row, int col) {
    int cafeNum;
    queue<int> temp;
    
    for(int d=1; d<=N; d++) {
        if(row+d < N && col-d >= 0) {
            d2 = d;
            cafeNum = cafe[row+d][col-d];
            if(visited[cafeNum] == 0) { //방문안한카페면 다음시뮬
                visited[cafeNum] = 1;
                temp.push(cafeNum);
                simul3(row+d, col-d);
            } else {
                break;
            }
        }
    }
    
    while(!temp.empty()) {
        cafeNum = temp.front();
        temp.pop();
        visited[cafeNum] = 0;
    }
}

/// 오른쪽 아래로 내려감
/// @param row 시작행
/// @param col 시작열
void simul1(int row, int col) {
    int cafeNum;
    queue<int> temp;

    
    cafeNum = cafe[row][col];
    visited[cafeNum] = 1;
    
    for(int d=1; d<N; d++) {
        if(row+d < N && col+d < N) {
            d1 = d;
            cafeNum = cafe[row+d][col+d];
            if(visited[cafeNum] == 0) { //방문 안한 디저티 종류를 파는 카페면 다음 시뮬레이션 돌리기
                visited[cafeNum] = 1;
                temp.push(cafeNum);
                simul2(row+d, col+d);
            } else {
                break;
            }
        }
    }
    
    while(!temp.empty()) {
        cafeNum = temp.front();
        temp.pop();
        visited[cafeNum] = 0;
    }
    cafeNum = cafe[row][col];   //처음에 이 코드 안써서 계속 잘못된값나옴
    visited[cafeNum] = 0;
}


int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d", &N);
        
        maxNum = -1;
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &cafe[i][j]);
            }
        }
        
      //  simul1(0,2);
        //시물레이션
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                simul1(i, j);
            }
        }
        
        printf("#%d %d\n", t, maxNum);
    }
    
    return 0;
}
