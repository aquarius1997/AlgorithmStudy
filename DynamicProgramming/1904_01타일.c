//
//  1904_01타일.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/07.
//  Copyright © 2020 송혜경. All rights reserved.
// **

#include <stdio.h>
/*
 T[A] : 길이 A로 만들 수 있는 2진 수열의 개수
 */
int T[1000002] = {0, };

int main(void) {
    int N;
    int i;
    
    scanf("%d", &N);

    //base-case
    T[1] = 1;
    T[2] = 2;
    
    //induction step
    for(i=3; i<=N; i++) {
        //수열의 개수는 00타일에, i-2길이로 만들 수 있는 수열들을 이어붙인 것과
        //1타일에 i-1길이로 만들 수 있는 수열들을 이어붙인 것들의 총 개수이다
        T[i] = (T[i-2] + T[i-1]) % 15746;
    }
    
    printf("%d", T[N]);
    
    return 0;
}
