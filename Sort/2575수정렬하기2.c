//
//  2575수정렬하기2.c
//  AlgorithmGit
//
//  Created by 송혜경 on 21/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

//==================================================
// 합병정렬을 위해 임시로 값을 저장하는 temp배열은
// 반드시 전역변수로 설정해야한다
// 만일 merge함수 안에 temp배열을 선언한다면
// 크기가 N인 배열의 메모리를 할당할 때 O(N)의 시간이 걸리기 때문에
// 총 O(N^2)이 되기 때문이다
//===================================================

#include <stdio.h>

int N;
int arr[1000001] = {0, };
int temp[1000001] = {0, };

void merge(int s1, int e1, int s2, int e2) {
    int p, q;
    int index = 0;
    int i;
    
    p = s1; q = s2;
    
    while(p <= e1 && q <= e2) {
        if(arr[p] < arr[q]) {
            temp[index++] = arr[p++];
        }else{
            temp[index++] = arr[q++];
        }
    }
    
    if(p > e1) {
        for(i = q; i <= e2; i++)
            temp[index++] = arr[i];
    }
    else {
        for(i = p; i <= e1; i++)
            temp[index++] = arr[i];
    }
    
    
    for(i=0; i<index; i++) {
        arr[s1+i] = temp[i];
    }
}

void merge_sort(int start, int end) {
    int mid;
    
    if(start < end) {
        mid = (start+end) / 2;
        merge_sort(start, mid);
        merge_sort(mid+1, end);
        merge(start, mid, mid+1, end);
    }
}

int main(void) {
    int i;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%d", &arr[i]);
    }
    
    merge_sort(0, N-1);
    
    for(i=0; i<N; i++) {
        printf("%d\n", arr[i]);
    }
    
    return 0;
}
