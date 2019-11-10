//
//  5.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/09.
//  Copyright © 2019 송혜경. All rights reserved.
//.이것도 효율성 0점 맞음, 정확성만 100

#include <string>
#include <vector>

using namespace std;
int arr[200002] = {0, };


int solution(vector<int> stones, int k) {
    int answer = 0;
    int cnt = 0;
    int rr = 1;
    int flag = 0;
    int i, j;

    
    while(1) {
        for(i=0; i<stones.size(); i++) {
            if(stones[i] > 0) {
                stones[i] -= 1;
            }
            if(stones[i] == 0) {
                cnt = 1;
                if(i+cnt < stones.size()) {
                    while(stones[i+cnt] - 1 <= 0) {
                        stones[i+cnt] = 0;
                        
                        cnt += 1;
                        if(i+cnt >= stones.size()) {
                            if(cnt >= k) {
                                answer = rr;
                                flag = 1;
                            }
                            break;
                        }
                    }
                }
                
                if(cnt >= k) {
                    answer = rr;
                    flag = 1;
                    break;
                }
                i = (i + cnt - 1);
            }
        }
        if(flag == 1) {
            break;
        }
        rr += 1;
    }
    
    //필요없는 코드같으
    if(rr == stones.size()+1) {
        rr = stones.size();
    }
        
    return answer;
}


