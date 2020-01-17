//
//  1920수찾기.c
//  AlgorithmGit
//
//  Created by 송혜경 on 31/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//  정렬 알고리즘 : merge sort를 사용해서 오름차순 정렬
int arr[100002] = {0, };

//이진탐색
int binary_search(int num, int start, int end) {
    int mid;
    
    if(start <= end) {
        mid = (start + end) / 2;
        
        if(arr[mid] == num) {
            return 1;
        }else if(arr[mid] < num) {
            return binary_search(num, mid+1, end);
        }else {
            return binary_search(num, start, mid-1);
        }
    }
    
    return 0;
}

//병합
void merge(int s1, int e1, int s2, int e2) {
    int temp[100002] = {0, };   int idx = 0;
    int p, q;
    int i;
    
    p = s1; q = s2;
    
    while(p <= e1 && q <= e2) {
        if( arr[p] < arr[q] )
            temp[idx++] = arr[p++];
        else
            temp[idx++] = arr[q++];
    } // end while
    
    if(p > e1) {
        for( i=q; i<=e2; i++ ) {
            temp[idx++] = arr[i];
        }
    }
    
    if(q > e2) {
        for( i=p; i<=e1; i++ ) {
            temp[idx++] = arr[i];
        }
    }
    
    for( i=0; i<idx; i++ ) {
        arr[s1+i] = temp[i];
    }
}

//합병정렬
void merge_sort(int start, int end) {
    int mid;
    
    if( start < end ) {
        mid = (start + end)/2;
        
        merge_sort(start, mid);
        merge_sort(mid+1, end);
        merge(start, mid, mid+1, end);
    }
}

#include <stdio.h>

int main(void) {
    int N, M, searchNum;
    int result;
    int i;
    
    scanf("%d", &N);
    
    for( i=0; i<N; i++ ) {
        scanf("%d", &arr[i]);
    }
    
    merge_sort(0, N-1);
    
    scanf("%d", &M);
    
    for( i=0; i<M; i++ ) {
        scanf("%d", &searchNum);
        
        result = binary_search(searchNum, 0, N-1);
        printf("%d\n", result);
    }
    
    return 0;
}
