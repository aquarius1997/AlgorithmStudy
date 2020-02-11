//
//  PGS_다음큰숫자.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <string>
#include <vector>

using namespace std;

/// 숫자 n을 2진수로 변환했을 때, 1의 개수를 리턴한다
/// @param n 2진수로 변환할 숫자
int numOfOne(int n) {
    int tempN = n;
    int cnt = 0;
    
    while(tempN > 1) {
        if(tempN % 2 == 1) {
            cnt++;
        }
        tempN /= 2;
    }
    
    cnt++;
    
    return cnt;
}

int solution(int n) {
    int answer = 0;
    int cnt;
    int number;
    
    cnt = numOfOne(n);
    number = n+1;
    
    while(1) {
        if(cnt == numOfOne(number)) {
            break;
        }
        number++;
    }
    
    answer = number;
    
    return answer;
}
