//
//  PGS_큰수만들기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/14.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int makeLen = number.length() - k;
    int idx = 0;
    int maxN;
    int i, j;
    
    for(i=makeLen-1; i>=0; i--) {
        //숫자로 변환해서 가장 큰수를 초기화
        maxN = number[idx] - '0';
        
        //문자열 맨뒤에서 i개만큼 뺀 수들에 대하여 가장 큰 수 찾기
        for(j=idx; j<number.length() - i; j++) {
            if(number[j]-'0' > maxN) {
                maxN = number[j] - '0';
                idx = j;
            }
        }
        
        //가장 큰 수 찾음
        string temp = to_string(maxN);

        answer.append(temp);
        
        idx += 1;
    }
    
    return answer;
}



