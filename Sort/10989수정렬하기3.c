//
//  10989수정렬하기3.c
//  AlgorithmGit
//
//  Created by 송혜경 on 31/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
int arr[10010] = {0, };

int main(void) {
    int N, num;
    int i;
    
    scanf("%d", &N);
    
    for( i=0; i<N; i++) {
        scanf("%d", &num);
        arr[num]++;
    }
    
    for( i=0; i<=10000; i++ ) {
        while(arr[i] > 0) {
            printf("%d\n", i);
            arr[i]--;
        }
    }
    
    return 0;
}
