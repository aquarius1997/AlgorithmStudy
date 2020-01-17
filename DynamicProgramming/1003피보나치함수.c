//
//  1003피보나치함수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

//fib_call[i][0] : fibonacci[i]를 호출했을 때, fibonacci[0]이 호출되는 수
//fib_call[i][1] : fibonacci[i]를 호출했을 때, fibonacci[1]이 호출되는 수
int fib_call[50][2] = {0, };

int main(void) {
    int T;
    int N;
    int t, i;
    
    scanf("%d", &T);
    
    for(t=0; t<T; t++){
        scanf("%d", &N);
        
        //base case
        fib_call[0][0] = 1; fib_call[0][1] = 0;
        fib_call[1][0] = 0; fib_call[1][1] = 1;
        
        for(i=2; i<=N; i++) {
            fib_call[i][0] = fib_call[i-1][0] + fib_call[i-2][0];
            fib_call[i][1] = fib_call[i-1][1] + fib_call[i-2][1];
        }
        
        printf("%d %d\n", fib_call[N][0], fib_call[N][1]);
    }
}
