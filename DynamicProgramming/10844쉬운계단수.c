//
//  10844쉬운계단수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
#define mod 1000000000


int main(void) {
    //arr[i][j] : 숫자 i로 시작하면서 길이j일때 계단수
    int arr[10][105] = {0, };
    int N;
    int sum = 0;
    int i, j;
    
    scanf("%d", &N);
    
    //base case
    for(i=0; i<10; i++) {
        arr[i][1] = 1;
        
        if(i == 0 || i == 9)
            arr[i][2] = 1;
        else
            arr[i][2] = 2;
    }
    
    //induction step
    for(j=3; j<=N; j++) {
        arr[0][j] = arr[1][j-1] % mod;
        for(i=1; i<=8; i++) {
            arr[i][j] = (arr[i-1][j-1] + arr[i+1][j-1]) % mod;
        }
        arr[9][j] = arr[8][j-1] % mod;
    }
    
    for(i=1; i<=9; i++){
        sum = (sum + arr[i][N]) % mod;
    }
    
    printf("%d", sum);
    
    return 0;
}

