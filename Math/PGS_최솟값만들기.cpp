//
//  PGS_최솟값만들기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/05.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** 수학적 머리가 딸리는 내 잘못이지. BruteForce로 구하는데 자꾸 시간초과떠서 찾아봤더니 아주 간단한 문제였다.

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int solution(vector<int> A, vector<int> B)
{
    int answer = 0;
    int bLen = B.size();
    
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    for(int i=0; i<A.size(); i++) {
        answer += (A[i] * B[bLen-1-i]);
    }
    
    return answer;
}

