//
//  2110_공유기설치.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <cstdio>
#include <algorithm>

using namespace std;

int N, C;
int arr[200002] = {0,};

/// start와 end의 중간 거리(mid)로 몇 개의 공유기를 최대로 설치할 수 있는지 알아내어 그에 따라 이분탐색한다
/// @param start C개 이상 설치 가능한 거리
/// @param end C개 미만으로 설치 가능한 거리
/// 끝과 끝 사이의 거리가 8일 경우 [1, 2, 3, 4, 5, 6, 7, 8, 9] -> [start, 미정, 미정, ..., 미정, end] 로 시작하게 된다
/// mid값으로 설치할 때 C개 미만 설치 가능할 경우 [start, 미정, .., (거리 mid)end, end, ..., end]가 될것이며, 반대의 케이스는 [start, start, .., (거리 mid)start, 미정, ... 미정, end]가 될것이다
/// 따라서 start + 1 == end 일 경우 start가 정답이 된다
int binSearch(int start, int end) {
    int mid;    int temp;
    int cnt = 0;    int maxCnt = 0;
    int j;
    
    if(start >= end) {
        return -1;
    } else {
        if(start + 1 == end) {
            return start;
        } else {
            mid = (start + end) / 2;
            
            cnt = 1;
            temp = arr[0];  //최대 설치 개수를 알아낼 것이므로 첫번째 집으로 시작하면 된다
            j = 1;
            while(j<N) {
                if(arr[j] - temp < mid) {
                    j++;
                } else {
                    cnt++;
                    temp = arr[j];
                    j++;
                }
            }
            if(cnt > maxCnt) {
                maxCnt = cnt;
            }
            
            
            if(maxCnt < C) {
                return binSearch(start, mid);
            } else {
                return binSearch(mid, end);
            }
        }
    }
}

int main(void) {
    int maxDist;
    int i;
    
    scanf("%d %d", &N, &C);
    
    for(i=0; i<N; i++) {
        scanf("%d", &arr[i]);
    }
    
    sort(arr, arr+N);
    
    maxDist = arr[N-1] - arr[0];    //끝과 끝 사이의 거리를 알아낸다
    
    printf("%d", binSearch(1, maxDist+1));
    
    
    return 0;
}
