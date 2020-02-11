//
//  PGS_최댓값과최솟값.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    int num = 0;
    int minN = 987987987;   int maxN = -987987987;
    int minusFlag = 0;
    string answer = "";
    
    for(int i=0; i<s.length(); i++) {
        if(s[i] == ' ') {
            if(minusFlag == 1) {
                num *= -1;
            }
            if(minN > num) {
                minN = num;
            }
            if(maxN < num) {
                maxN = num;
            }
            
            num = 0;
            minusFlag = 0;
        } else if(s[i] == '-') {
            minusFlag = 1;
        } else {
            if(num == 0) {
                num = s[i] - '0';

            } else {
                num *= 10;
                num += (s[i] - '0');
            }
        }
    }
    
    if(minusFlag == 1) {
        num *= -1;
    }
    
    if(minN > num) {
        minN = num;
    }
    if(maxN < num) {
        maxN = num;
    }
    
    string tempStr = to_string(minN);
    answer.append(tempStr);
    
    answer.append(" ");
    
    tempStr = to_string(maxN);
    answer.append(tempStr);
    
    return answer;
}

