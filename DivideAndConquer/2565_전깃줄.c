
//
//  2565_전깃줄.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****(실패)

#include <stdio.h>
#define MAXN(a, b)  (((a) > (b)) ? (a) : (b))

int main(void) {
    int T[502] = {0, }; //T[i] = j -> i에서 j까지 전깃줄이 연결되어있음. 연결된 전깃줄 없을 경우 0
    int M[502][2] = {0,};   //M[i][0] : i전기줄을 포함하지않을 경우 최대 전기줄 설치 개수, M[i][1] : i전기줄을 포함할 경우 최대 전기줄 개수
    int N, a, b;
    int tempMax;
    
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d %d", &a, &b);
        T[a] = b;
    }
    
    //base-case
    M[0][0] = M[0][1] = 0;
    M[1][0] = 0;
    M[1][1] = 1;
    
    for(int i=2; i<=500; i++) {
        
        if(T[i] == 0) {
            M[i][0] = M[i-1][0];
            M[i][1] = M[i-1][1];
        } else {
            M[i][0] = MAXN(M[i-1][0], M[i-1][1]);
            
            tempMax = 0;
            for(int j=i-1; j>=0; j--) {
                if(T[j] <= T[i]) {
                    if(tempMax < M[j][1] + 1) {
                        tempMax = M[j][1] + 1;
                    }
                }
            }
            M[i][1] = tempMax;
        }

    }
    
    
    printf("%d", N - MAXN(M[500][0], M[500][1]));
    
    return 0;
}
