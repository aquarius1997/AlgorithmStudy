//
//  2748피보나치수2.c
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

long fib[100] = {0, };
int N;

int main(void) {
    int i;
    
    scanf("%d", &N);
    
    //base  case
    fib[0] = 0; fib[1] = 1;
    //induction step
    for(i=2; i<=N; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    printf("%ld", fib[N]);
    return 0;
}
