//
//  13458_시험감독.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/09.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <cstdio>
using namespace std;

int aArr[1000001] = {0, };

int main(void) {
    int N, B, C, A;
    int restCnt=0;
    int cNum = 0;
    long long answer = 0;
    
    scanf("%d", &N);
    
    for(int i=1; i<=N; i++) {
        scanf("%d", &aArr[i]);
    }
    
    scanf("%d %d", &B, &C);
    
    for(int i=1; i<=N; i++) {
        if(aArr[i] <= B) {  //총감독관 한명으로 되면
            answer += 1;
            continue;
        } else {
            answer += 1;    //총감독관 한명 추가하고
            restCnt = aArr[i] - B;
            if(restCnt <= C) {  //부감독관 1명 추가로 끝나면
                answer += 1;
                continue;
            } else {
                cNum = restCnt / C;
                restCnt = restCnt % C;
                answer += cNum;
                if(restCnt > 0) {
                    answer += 1;
                }
            }
        }
    }
    
    printf("%lld", answer);
    
    return 0;
}
