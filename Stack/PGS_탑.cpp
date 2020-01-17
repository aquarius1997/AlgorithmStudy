//
//  PGS_탑.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/03.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer;
    vector<int> tempArr;
    int hLen = heights.size();
    int i, j;
    
    for(i=hLen-1; i>0; i--) {
        //왼쪽으로 자기보다 더 큰 탑이 있는지 확인한다
        for(j=i-1; j>=0; j--) {
            if(j == 0 && heights[j] <= heights[i]) {
                tempArr.push_back(0);
            }else if(heights[j] > heights[i]) {
                tempArr.push_back(j+1);
                break;
            }
        }
    }
    //첫번째 탑은 무조건 0
    tempArr.push_back(0);
    
    for(i=hLen-1; i>=0; i--) {
        answer.push_back(tempArr[i]);
    }
    
    return answer;
}

