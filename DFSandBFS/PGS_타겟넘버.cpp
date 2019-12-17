//
//  PGS_타겟넘버.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/12.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

int cnt = 0;

void dfs(vector<int> numbers, int idx, int sum, int target) {
    
    //종료조건
    if(idx == numbers.size()) {
        if(target == sum) {
            cnt++;
        }
        return;
    } else {
        //현재수를 더해서 넘겨준다
        dfs(numbers, idx+1, sum + numbers[idx], target);
        //현재수를 빼서 넘겨준다
        dfs(numbers, idx+1, sum - numbers[idx], target);
    }
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int i;
    
    cnt = 0;
    //end init
    
    dfs(numbers, 0, 0, target);
    
    
    answer = cnt;
    
    return answer;
}
