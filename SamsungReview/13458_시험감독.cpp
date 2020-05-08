//
//  13458_시험감독.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/08.
//  Copyright © 2020 송혜경. All rights reserved.
//  * 10min 0Fail

#include <cstdio>
using namespace std;

int main(void) {
    int N, B, C;
    int restNum = 0;
    long long totalCnt = 0;
    int rooms[1000002] ={0,};
    
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d", &rooms[i]);
    }
    scanf("%d %d", &B, &C);
    
    for(int i=0; i<N; i++) {
        restNum = rooms[i] - B; //총감독관 한명이 감시할 때, 나머지 감독하지 못하는 사람들의 수
        totalCnt += 1;
        if(restNum > 0) {
            //부감독관 몇명 필요한지 구하기
            if(restNum % C == 0) {
                totalCnt += (restNum / C);
            } else {
                totalCnt += (restNum / C + 1);
            }
        }
    }
    
    printf("%lld", totalCnt);

    return 0;
}
