//
//  12015_가장긴증가하는부분수열2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/27.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <vector>
using namespace std;

int arr[1000001] = {0, };
vector<int> L;

/// L배열에 대하여 element의 lower bound를 구한다
/// @param element 값을 넣을 원소
/// @param start 확인할 시작인덱스
/// @param end 확인할 마지막 인덱스

int get_lower_bound(int start, int end, int element) {
    int mid;
    
    if(start <= end) {
        if(start == end) {
            return start;
        } else {
            mid = (start + end) / 2;
            if(L[mid] > element) {
                return get_lower_bound(start, mid, element);
            } else if (L[mid] < element) {
                
                return get_lower_bound(mid+1, end, element);
            } else {
                return mid;
            }
        }
    } else {
        return -2;
    }
}

int main(void) {
    int N;  int lLen, idx;
    int i;
    
    scanf("%d", &N);

    for(i=0; i<N; i++) {
        scanf("%d", &arr[i]);
    }
    
    L.push_back(arr[0]);    //첫번째 원소는 넣기
    
    for(i=1; i<N; i++) {
        lLen = L.size();
        if(L[lLen-1] < arr[i]) {    //현재 원소가 L의 마지막 원소보다 크면
            L.push_back(arr[i]);
        } else {
            idx = get_lower_bound(0, lLen-1, arr[i]);   //현재 원소의 lower bound 인덱스를 알아낸다
            L[idx] = arr[i];    //해당 인덱스에 현재 원소를 저장한다
        }
    }
    
    printf("%d", L.size());

    return 0;
}
