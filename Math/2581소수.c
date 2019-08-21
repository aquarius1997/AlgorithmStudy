//
//  2581소수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 21/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int main(void) {
    int N, M;
    int n_sqrt;
    int min = 987987987;    int sum = 0;
    int p_flag = 0;
    int i, j;
    
    scanf("%d %d", &M, &N);
    
    for(i = M; i <= N; i++) {
        if( i == 1 )
            continue;
        
        n_sqrt = (int)(sqrt(i));
        p_flag = 0;
        
        for(j=2; j <= n_sqrt; j++) {
            // 소수가 아닐 경우
            if( i % j == 0 ) {
                p_flag = 1;
                break;
            }
        }
        
        //소수
        if(p_flag == 0) {
            sum += i;
            if( min > i ) {
                min = i;
            }
        }
    }
    
    if( sum == 0 ) {
        printf("-1\n");
    }else {
        printf("%d\n", sum);
        printf("%d\n", min);
    }
    
    return 0;
}
