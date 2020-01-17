//
//  PGS_124나라의숫자.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/07.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string solution(int n) {
    string answer = "";
    int number[20] = {0, }; int idx = 0;
    
    int rest;
    
    while(n > 3) {
        rest = n % 3;
        
        //나머지가 0일 경우 4로 저장
        if(rest == 0) {
            number[idx++] = 4;
            n = n/3;
            n = n-1;
        }else {
            number[idx++] = rest;
            n = n/3;
        }
        
    }
    
    if(n == 3) {
        number[idx++] = 4;
    }else {
        number[idx++] = n;
    }
    
    for(int i=idx-1; i>=0; i--) {
        if(number[i] == 1) {
            answer.append("1");
        }else if(number[i] == 2) {
            answer.append("2");
        }else {
            answer.append("4");
        }
    }
    
    return answer;
}

int main(void) {
    int num;
    string result;
    
    while(num != 0) {
        scanf("%d", &num);
        
        result = solution(num);
        
        cout << result << endl;
    }
    
    return 0;
}
