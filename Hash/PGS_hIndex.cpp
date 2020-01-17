//
//  PGS_hIndex.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/06.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;



void merge(int s1, int e1, int s2, int e2, int arr[1002]) {
    int temp[1002]; int idx = 0;
    int p, q;
    int i;
    
    p = s1; q = s2;
    
    while(p <= e1 && q <= e2) {
        if(arr[p] < arr[q]) {
            temp[idx++] = arr[p++];
        } else {
            temp[idx++] = arr[q++];
        }
    }
    
    for(i=p; i<=e1; i++) {
        temp[idx++] = arr[i];
    }
    
    for(i=q; i<=e2; i++) {
        temp[idx++] = arr[i];
    }
    
    for(i=0; i<idx; i++) {
        arr[s1+i] = temp[i];
    }
}

void merge_sort(int start, int end, int arr[1002]) {
    int mid;
    
    if(start < end) {
        mid = (start + end) / 2;
        merge_sort(start, mid, arr);
        merge_sort(mid+1, end, arr);
        merge(start, mid, mid+1, end, arr);
    }
}

int solution(vector<int> citations) {
    int arr[1002] = {0, };
    int answer = 0;
    int arrLen; int num;
    int flag = 0;
    int i, j;
    
    for(i=0; i<citations.size(); i++) {
        arr[i] = citations[i];
    }
    
    arrLen = citations.size();
    
    //정렬
    merge_sort(0, arrLen-1, arr);
    
    for(i=0; i<arrLen; i++) {
        printf("%d ", arr[i]);
    }
    
    for(i=0; i<arrLen; i++) {
        //현재 논문의 인용수
        num = arr[i];
        //num번 이상 인용된 논문의 개수가 num편 이상이면
        if(arrLen - i >= num) {
            answer = num;
        } else {
            break;
        }
    }
    
    for(i=0; i<=10000; i++) {
        flag = 0;
        for(j=0; j<arrLen; j++) {
            if(arr[j] >= i) {   //h가 i일 때, i번 이상 인용된 논문이  몇개인지 확인
                num = arrLen - j;
                
                if(num >= i) {  //h번 이상 인용된 논문이 h개 이상이면
                    answer = num;
                    flag = 1;   //최댓값을 확인하기 위해
                    break;
                }
            }
        }
        if(flag == 0) {
            break;
        }
    }
    
    return answer;
}

int main(void) {
    vector<int> citations;
    
    citations.push_back(3);
    citations.push_back(2);
    citations.push_back(5);
    citations.push_back(1);
    citations.push_back(6);
    
    solution(citations);
    
    return 0;
}
