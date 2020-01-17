//
//  11651좌표정렬하기2.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/30.
//  Copyright © 2019 송혜경. All rights reserved.
// **

#include <stdio.h>

int temp[100002][2] = {0, };    //merge_f에서 사용할 임시 배열

/*
 coordinates : merge할 좌표 배열
 s1 : 부분배열1의 첫번째 인덱스, e1 : 부분배열1의 마지막 인덱스
 s2 : 부분배열2의 첫번째 인덱스, e2 : 부분배열2의 마지막 인덱스
 */
void merge_f(int coordinates[100002][2], int s1, int e1, int s2, int e2) {
    int idx = 0;
    int p = s1; int q = s2;
    int i;
    
    while(p <= e1 && q <= e2) {
        //y값을 기준으로 오름차순 정렬
        if(coordinates[p][1] < coordinates[q][1]) {
            temp[idx][0] = coordinates[p][0];
            temp[idx][1] = coordinates[p][1];
            p++;
            idx++;
        } else if(coordinates[p][1] > coordinates[q][1]){
            temp[idx][0] = coordinates[q][0];
            temp[idx][1] = coordinates[q][1];
            q++;
            idx++;
        } else {    //y값이 동일하면 x값으로 정렬
            if(coordinates[p][0] < coordinates[q][0]) {
                temp[idx][0] = coordinates[p][0];
                temp[idx][1] = coordinates[p][1];
                idx++;
                p++;
            } else {
                temp[idx][0] = coordinates[q][0];
                temp[idx][1] = coordinates[q][1];
                idx++;
                q++;
            }
            
        }
    }
    
    while(p <= e1) {
        temp[idx][0] = coordinates[p][0];
        temp[idx][1] = coordinates[p][1];
        idx++;
        p++;
    }
    
    while(q <= e2) {
        temp[idx][0] = coordinates[q][0];
        temp[idx][1] = coordinates[q][1];
        idx++;
        q++;
    }
    
    for(i=0; i<idx; i++) {
        coordinates[s1+i][0] = temp[i][0];
        coordinates[s1+i][1] = temp[i][1];
    }
}

/*
 coordinates : 정렬할 좌표 배열
 start : 정렬할 배열의 첫번째 인덱스
 end : 정렬할 배열의 마지막 인덱스
 */
void merge_sort(int coordinates[100002][2], int start, int end) {
    int mid;
    
    if(start < end) {
        mid = (start + end) / 2;
        
        merge_sort(coordinates, start, mid);
        merge_sort(coordinates, mid+1, end);
        merge_f(coordinates, start, mid, mid+1, end);
    }
}

int main(void) {
    int coordinates[100002][2]; //좌표 저장. coordinates[i][0] : i번째 점의 x좌표, [i][1] : y좌표
    int N;
    int x, y;   //입력으로 (x, y)좌표를 받을 때 사용
    int i;
    
    scanf("%d", &N);
    
    //입력받은 좌표 정보를 coordinates배열에 저장
    for(i=0; i<N; i++) {
        scanf("%d %d", &x, &y);
        
        coordinates[i][0] = x;
        coordinates[i][1] = y;
    }
    
    merge_sort(coordinates, 0, N-1);
    
    for(i=0; i<N; i++) {
        printf("%d %d\n", coordinates[i][0], coordinates[i][1]);
    }
    
    return 0;
}
