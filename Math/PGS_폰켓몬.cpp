//
//  PGS_폰켓몬.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <vector>
using namespace std;

int solution(vector<int> nums)
{
    int cntArr[200001] = {0, };
    int cnt = 0;
    int answer = 0;
    
    for(int i=0; i<nums.size(); i++) {
        if(cntArr[(nums[i])] == 0) {
            cntArr[(nums[i])]++;
            cnt++;
        }
    }
    
    if(cnt > nums.size()/2) {
        cnt = nums.size()/2;
    }
    
    answer = cnt;
    return answer;
}
