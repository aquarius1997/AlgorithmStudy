//
//  11054_가장긴바이토닉부분수열.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/15.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int main(void) {
    int inc[1002][2] = {0,};    //inc[i][0] : i인덱스를 포함하지 않았을 경우 가장 긴 증가하는 부분 수열의 길이, inc[i][1] : i인덱스를 포함할 경우 가장 긴 감소하는 부분수열의 길이
    int dec[1002][2] = {0,};    //dec[i][0] : i인덱스를 포함하지 않았을 경우 가장 긴 감소하는 부분수열의 길이, dec[i][1] : i인덱스를 포함할 경우 가장 긴 감소하는 부분수열의 길이
    int arr[1002] = {0,};   //입력배열
    int N;
    int incMax, decMax;
    int result, temp;
    int i, j;
    
    scanf("%d", &N);
    
    for(i=1; i<=N; i++) {
        scanf("%d", &arr[i]);
    }
    
    //base-case
    inc[1][0] = 0;  inc[1][1] = 1;
    dec[N][0] = 0;  dec[N][1] = 1;
    
    //induction step
    for(i=2; i<=N; i++) {
        //inc[i][1]을 구한다 : i번째 숫자를 포함할 때 가장 긴 증가하는 부분수열의 길이
        incMax = 0;
        for(j=i-1; j>0; j--) {
            //i숫자 왼쪽으로 arr[i]보다 작은값들에 대하여 가장 큰 inc[idx][1]을 찾는다
            if(arr[i] > arr[j]) {
                if(inc[j][1] > incMax) {
                    incMax = inc[j][1];
                }
            }
        }
        inc[i][1] = incMax + 1;
        
        //inc[i][0]을 구한다 : i번째 숫자를 포함하지 않을 때 가장 긴 증가하는 부분수열의 길이
        if(inc[i-1][0] > inc[i-1][1]) {
            inc[i][0] = inc[i-1][0];
        } else {
            inc[i][0] = inc[i-1][1];
        }
    }

    // !! dec은 N부터 왼쪽 방향으로 구해야함 (정확하게는 N->1 방향으로 가장 긴 증가하는 부분수열의 길이를 구하는 것임)
    for(i=N-1; i>0; i--) {
        //dec[i][1]을 구한다
        decMax = 0;
        for(j=i+1; j<=N; j++) {
            //i숫자 오른쪽으로 arr[i]보다 작은 값들에 대하여 가장 큰 dec[idx][1]을 찾는다
            if(arr[i] > arr[j]) {
                if(dec[j][1] > decMax) {
                    decMax = dec[j][1];
                }
            }
        }
        dec[i][1] = 1 + decMax;
        
        //dec[i][0]을 구한다
        if(dec[i+1][0] > dec[i+1][1]) {
            dec[i][0] = dec[i+1][0];
        } else {
            dec[i][0] = dec[i+1][1];
        }
    }
    
    result = 0;
    //i번째 숫자를 기준으로 [증가 + i번째 숫자 + 감소]하는 부분수열의 최대 길이를 구한다
    for(i=1; i<=N; i++) {
        temp = inc[i][1] + dec[i][1] - 1;
        if(temp > result) {
            result = temp;
        }
    }
    
    printf("%d", result);
    
    return 0;
}
