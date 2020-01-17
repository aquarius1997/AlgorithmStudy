//
//  10870피보나치수5.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/26.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

int fibo(int n) {
    if(n == 0) {
        return 0;
    } else if(n == 1 || n == 2) {
        return 1;
    } else {
        return fibo(n-1) + fibo(n-2);
    }
}
int main(void) {
    int n;
    
    scanf("%d", &n);
    
    printf("%d", fibo(n));
    
    return 0;
}
