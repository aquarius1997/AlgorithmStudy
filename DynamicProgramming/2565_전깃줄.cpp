
//
//  2565_전깃줄.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <stdio.h>
#define MAXN(a, b)   (((a) > (b)) ? (a) : (b))

int main(void) {
    int N, a, b;
    int arr[502] = {0, }; //arr[1]=2 -> A 1번과 B 2번이 연결되어 있음
    int incLIS[502][2] = {0, }; //incLIS[i][0] : i번째 전기줄을 포함했을 때 LIS, i번째 전기줄을 포함하지 않았을 때 LIS
    int maxNum = 0;
    int incMax;
    int i, j;
    
    scanf("%d", &N);
    
    for(i=1; i<=N; i++) {
        scanf("%d %d", &a, &b);
        arr[a] = b;
    }
    
    //LIS 구하기
    //base-case
    i = 1;
    while(arr[i] == 0) {
        incLIS[i][0] = incLIS[i][1] = 0;
        i++;
    }
    incLIS[i][0] = 1;
    incLIS[i][1] = 0;
    i += 1;
    //induection step
    for(; i<=500; i++) {
        maxNum = 0;
        
        if(arr[i] == 0) {
            incLIS[i][0] = incLIS[i-1][0];
            incLIS[i][1] = incLIS[i-1][1];
            continue;
        }
        
        for(j=i-1; j>=1; j--) {
            if(arr[i] > arr[j] && arr[j] != 0) {
                if(incLIS[j][0] > maxNum) {
                    maxNum = incLIS[j][0];
                }
            }
        }
        
        incLIS[i][0] = 1 + maxNum;
        
        incLIS[i][1] = MAXN(incLIS[i-1][0], incLIS[i-1][1]);
    }


    incMax = MAXN(incLIS[500][0], incLIS[500][1]);

    printf("%d", N-incMax);
    return 0;
}
