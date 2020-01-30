//
//  2110_공유기설치.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <stdio.h>

int N, C;
int arr[200002] = {0,};

int main(void) {
    int i;
    
    scanf("%d %d", &N, &C);
    
    for(i=0; i<N; i++) {
        scanf("%d", &arr[i]);
    }
    
    
    return 0;
}
