
//
//  11053_가장긴증가하는부분수열.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/14.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <stdio.h>

int main(void) {
    int T[1002][2] = {0, };    //T[i][0] : i번째 수를 포함했을 경우 답, T[i][1] : i번째 수 포함X
    int arr[1002] = {0, };  //입력 배열
    int N;
    int maxN;
    int i, j;
    
    scanf("%d", &N);
    
    for(i=1; i<=N; i++) {
        scanf("%d", &arr[i]);
    }

    /*
     T[i][0] : 자기 자신을 포함하므로 (0 ~ i-1)까지 자신보다 작은 값들에 대하여 확인해야한다.
     (idx : arr[i]보다 작은 값들의 인덱스)
     -> T[i][0] = 1 + MAX(T[idx][0], ..)
     T[i][1] : 자기 자신을 포함하지 않으므로 MAX(T[i-1][0], T[i-1][1])
     */
    T[1][0] = 1;    T[1][1] = 0;
    
    for(i=2; i<=N; i++) {
        maxN = 0;
        for(j=i-1; j>0; j--) {
            if(arr[j] < arr[i]) {   //i번째 값보다 작은 수들에 대하여
                if(maxN < T[j][0]) {    //최대 길이를 선택
                    maxN = T[j][0];
                }
            }
        }
        maxN += 1; //자기자신을 포함하므로 1을 더한다
        T[i][0] = maxN;
        
        //i번째 값을 포함하지 않을 경우
        if(T[i-1][0] > T[i-1][1]) {
            T[i][1] = T[i-1][0];
        } else {
            T[i][1] = T[i-1][1];
        }
    }
    
    if(T[N][0] > T[N][1]) {
        printf("%d", T[N][0]);
    } else {
        printf("%d", T[N][1]);
    }
    
    return 0;
}
