//
//  10816_숫자카드2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/08.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
#include <algorithm>

using namespace std;

int card[500002] = {0,};
int rightIdx, leftIdx;

/// 구간 [start ~ end]에 대하여 숫자 num의 가장 오른쪽 인덱스를 알아낸다
/// @param start 검색 시작 인덱스
/// @param end 검색 마지막 인덱스
/// @param num 검색할 숫자
void find_right(int start, int end, int num) {
    int mid;
    
    if(start <= end) {
        mid = (start + end) / 2;
        
        if(card[mid] == num) {  //찾으려는 수가 가운데에 있으면 가장 오른쪽으로 업데이트하고 더 오른쪽으로 탐색
            if(rightIdx < mid) {
                rightIdx = mid;
            }
            find_right(mid+1, end, num);
        } else if(card[mid] > num) {    //가운데 숫자가 찾으려는 숫자보다 크면 왼쪽 구간 확인하기
            find_right(start, mid-1, num);
        }
    }
}

/// 구간[start ~ end]에 대하여 숫자 num의 가장 왼쪽 인덱스를 알아낸다
/// @param start 검색 시작 인덱스
/// @param end 검색 마지막 인덱스
/// @param num 검색 숫자
void find_left(int start, int end, int num) {
    int mid;
    
    if(start <= end) {
        mid = (start + end) / 2;
        
        if(card[mid] == num) {  //찾으려는 수가 가운데에 있으면 가장 왼쪽으로 업데이트하고 더 왼쪽으로 탐색
            if(leftIdx > mid) {
                leftIdx = mid;
            }
            find_left(start, mid-1, num);
        } else if(card[mid] < num) {    //가운데 숫자가 찾으려는 숫자보다 작으면 오른쪽 구간 확인
            find_left(mid+1, end, num);
        }
        
    }
}

/*
 card 배열에 대하여 숫자 num의 갯수를 찾아 리턴한다
 start : 검색 시작 인덱스
 end : 검색 마지막 인덱스
 num : 찾을 숫자
 return : num의 갯수
 */
int bn_search(int start, int end, int num) {
    int numCnt;
    int mid;
    
    if(start <= end) {
        mid = (start + end) / 2;    //중간 인덱스 알아내기
        
        if(card[mid] == num) {  //찾으려는 숫자가 가운데에 있으면
            rightIdx = leftIdx = mid;
            find_right(mid+1, end, num);    //가장 오른쪽 인덱스를 알아낸다
            find_left(start, mid-1, num);   //가장 왼쪽 인덱스를 알아낸다
            numCnt = rightIdx - leftIdx + 1;
            
            return numCnt;
        } else if(card[mid] > num) {    //중간인덱스의 숫자가 찾으려는 숫자보다 크면
            return bn_search(start, mid-1, num);
        } else {    //중간 인덱스의 숫자가 찾으려는 숫자보다 작으면
            return bn_search(mid+1, end, num);
        }
    } else {    //찾으려는 숫자가 없으면
        return 0;
    }
}


int main(void) {
    int N, M;
    int num, result;
    int i;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%d", &card[i]);
    }
    
    
    scanf("%d", &M);

    
    // 1. 정렬한다
    sort(card, card+N);

    // 2. 이진탐색을 수행한다
    for(i=0; i<M; i++) {
        scanf("%d", &num);
        result = bn_search(0, N-1, num);
        printf("%d ", result);
    }
    
    return 0;
}
