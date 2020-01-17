//
//  15650N과M_3.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/02.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int arr[9] = {0, }; //수열을 저장할 배열

/*
 N : 입력으로 주어진 N
 M : 입력으로 주어진 M
 idx : 함수 호출로 인해 arr배열에 수열의 정보를 저장할 때, 저장하는 인덱스의 위치를 가리킨다
 */

void make_sequence(int N, int M, int idx) {
    int i;
    
    if(idx == M) {  //수열 만들었으면 출력
        for(i=0; i<idx; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        for(i=1; i<=N; i++) {
            arr[idx] = i;
            make_sequence(N, M, idx+1);
        }
    }
}


int main(void) {
    int N, M;
    
    scanf("%d %d", &N, &M);
    
    make_sequence(N, M, 0);
    
    return 0;
}
