//
//  PGS_주식가격.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/08.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    int flag = 0;
    
    for(int i=0; i<prices.size(); i++) {
        //마지막은 무조건 0
        if(i == prices.size() - 1) {
            answer.push_back(0);
        }else {
            int cnt;
            
            for(int j=i+1; j<prices.size(); j++) {
                cnt = j-i;
                if(prices[j] >= prices[i]) {
                    flag = 1;
                }else {
                    break;
                }
            }

            answer.push_back(cnt);
    
        }
    }
    
    return answer;
}
