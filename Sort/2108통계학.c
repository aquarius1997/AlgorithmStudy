//
//  2108통계학.c
//  AlgorithmGit
//
//  Created by 송혜경 on 31/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

int arr[500002] = {0, };
//최빈값을 구하기 위하여 음수와 양수를 두개의 카운팅 배열로 나눈다
int minus_arr[4002] = {0, };
int plus_arr[4002] = {0, };
int temp[500002] = {0, };


void merge(int s1, int e1, int s2, int e2) {
    int idx = 0;
    int p, q;   int i;
    
    p = s1; q = s2;
    
    while( p<=e1 && q<=e2 ) {
        if(arr[p] < arr[q]) {
            temp[idx++] = arr[p++];
        }else {
            temp[idx++] = arr[q++];
        }
    }
    
    if(p > e1) {
        for( i=q; i<=e2; i++ )
            temp[idx++] = arr[i];
    }
    if(q > e2) {
        for( i=p; i<=e1; i++ )
            temp[idx++] = arr[i];
    }
    
    for(i=0; i<idx; i++)
        arr[s1+i] = temp[i];
}


void merge_sort(int start, int end) {
    int mid;
    
    if(start < end) {
        mid = (start + end)/ 2;
        
        merge_sort(start, mid);
        merge_sort(mid+1, end);
        merge(start, mid, mid+1, end);
    }
}

int main(void) {
    int N;  int sum = 0;
    int temp;
    int max, max_idx1, max_idx2;
    int count = 0;
    int result1, result2, result3, result4;
    int i;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%d", &arr[i]);
        
        //음수면 minus_arr 카운팅 배열을 카운팅
        if(arr[i] < 0) {
            temp = arr[i] * (-1);
            minus_arr[temp]++;
        }else {
            //0보다 크거나 같은 수이면 plus_arr 카운팅 배열을 카운팅
            plus_arr[(arr[i])]++;
        }
        
        //산술평균을 구하기 위한 합계
        sum += arr[i];
    }
    
    //arr배열 정렬
    merge_sort(0, N-1);
    
    //------------- 산술 평균을 구하기 위한 과정 --------------//
    //반올림을 해야할 경우를 위해 double 자료형으로 나눗셈의 결과를 알아낸다
    double result1_t = (double)sum / N;
    int dd = sum / N;
    result1 = sum / N;
    //소수점자리의 숫자를 계산한다
    result1_t -= dd;

    
    if(result1_t < 0) {
        //반올림해야할경우
        if(result1_t <= -0.5) {
            result1--;
        }
    }else {
        //반올림해야할경우
        if(result1_t >= 0.5) {
            result1++;
        }
    }
    //---------- End 산술 평균을 구하기 위한 과정 -------------//

    result2 = arr[(N/2)];   //중앙값
    result4 = arr[N-1] - arr[0];    //범위

    
    //최빈값을 구하기 위해 가장 많이 나타나는 값의 인덱스를 구한다
    max = minus_arr[1]; max_idx1 = 1;
    for(i=1; i<4002; i++) {
        if(minus_arr[i] >= max) {
            max_idx1 = i;
            max = minus_arr[i];
        }
    }
    
    max = plus_arr[0];  max_idx2 = 0;
    for(i=0; i<4002; i++) {
        if(plus_arr[i] >= max) {
            max_idx2 = i;
            max = plus_arr[i];
        }
    }
    
    //최빈값이 여러개 있을 경우를 위한 과정
    if(minus_arr[max_idx1] > plus_arr[max_idx2]){
        max = minus_arr[max_idx1];
        result3 = max_idx1 * (-1);
    }else {
        max = plus_arr[max_idx2];
        result3 = max_idx2;
    }
    
    //최빈값이 여러개 있을경우 두번째로 작은 값을 result3에 저장한다
    for(i=4000; i>=1; i--) {
        if(minus_arr[i] == max) {
            count++;
            if(count == 2) {
                result3 = i * (-1);
                break;
            }
        }
    }
    
    for(i=0; i<4002; i++) {
        if(plus_arr[i] == max) {
            count++;
            if(count == 2) {
                result3 = i;
                break;
            }
        }
    }
    
    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
    printf("%d\n", result4);
    
    return 0;
}
