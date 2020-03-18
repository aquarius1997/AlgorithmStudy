//
//  14888_연산자끼워놓기.cpp
//  temppp
//
//  Created by 송혜경 on 2020/03/18.
//  Copyright © 2020 송혜경. All rights reserved.
// 30min. ***

#include <cstdio>
using namespace std;


int minN = 2000000000;
int maxN = -2000000000;
int plus, minus, divi, multi;
int visited[102] = {0, };
int number[102] = {0, };
int operator_arr[102] = {0, };  //1:덧셈, 2:뺄셈, 3:곱셈, 4:나눗셈
int N;

/// 연산자 순열을 만든다
/// @param idx 연산자 인덱스
/// @param plusCnt 현재까지 사용한 덧셈 연산자 수
/// @param minusCnt 현재까지 사용한 뺄셈 연산자 수
/// @param multiCnt 현재까지 사용한 곱셈 연산자 수
/// @param divCnt 현재까지 사용한 나눗셈 연산자 수
void makeOper(int idx, int plusCnt, int minusCnt, int multiCnt, int divCnt) {
    int temp = 0;
    if((plusCnt + minusCnt + multiCnt + divCnt) == N-1) {   //N-1개의 연산자를 만들면 계산
        temp = number[0];
        for(int i=0; i<N-1; i++) {
            if(operator_arr[i] == 1) {  //덧셈
                temp += number[i+1];
            } else if(operator_arr[i] == 2) {   //뺄셈
                temp -= number[i+1];
            } else if(operator_arr[i] == 3) {   //곱셈
                temp *= number[i+1];
            } else {    //나눗셈
                temp /= number[i+1];
            }
        }
        if(temp < minN) {   //최솟값 업데이트
            minN = temp;
        }
        if(temp > maxN) {   //최대값 업데이트
            maxN = temp;
        }
    } else {
        visited[idx] = 1;
        
        if(plusCnt + 1 <= plus) {   //덧셈 연산자를 사용할 수 있으면
            operator_arr[idx] = 1;
            for(int i=idx+1; i<N; i++) {
                if(visited[i] == 0) {
                    makeOper(i, plusCnt+1, minusCnt, multiCnt, divCnt);
                }
            }
        }
        if(minusCnt + 1 <= minus) {
            operator_arr[idx] = 2;
            for(int i=idx+1; i<N; i++) {
                if(visited[i] == 0) {
                    makeOper(i, plusCnt, minusCnt+1, multiCnt, divCnt);
                }
            }
        }
        if(multiCnt + 1 <= multi) {
            operator_arr[idx] = 3;
            for(int i=idx+1; i<N; i++) {
                if(visited[i] == 0) {
                    makeOper(i, plusCnt, minusCnt, multiCnt+1, divCnt);
                }
            }
        }
        if(divCnt + 1 <= divi) {
            operator_arr[idx] = 4;
            for(int i=idx+1; i<N; i++) {
                if(visited[i] == 0) {
                    makeOper(i, plusCnt, minusCnt, multiCnt, divCnt+1);
                }
            }
        }
        
        visited[idx] = 0;
    }
}

int main(void) {
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d", &number[i]);
    }
    scanf("%d %d %d %d", &plus, &minus, &multi, &divi);
    
    makeOper(0, 0, 0, 0, 0);

    printf("%d\n%d", maxN, minN);
    
    return 0;
}
