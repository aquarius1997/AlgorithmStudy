//
//  PGS_숫자의표현.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    int sum;
    int i, j;
    
    for(i=1; i<=n; i++) {
        sum = 0;
        
        for(j=i; j<=n; j++) {
            sum += j;
            
            if(sum == n) {
                answer++;
            } else if(sum > n) {
                break;
            }
        }
    }
    return answer;
}
