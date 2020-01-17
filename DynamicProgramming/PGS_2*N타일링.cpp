//
//  2XN타일링.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/10/30.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    int T[60002] = {0, };
    
    //base-case
    T[1] = 1;
    T[2] = 2;
    
    //induction step
    for(int i=3; i<=n; i++) {
        T[i] = (T[i-1] + T[i-2]) % 1000000007;
    }
    
    answer = T[n];
    
    return answer;
}
