//
//  PGS_올바른괄호.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/25.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <iostream>

using namespace std;

typedef struct StackType {
    int top;
    int arr[100002];
}StackType;

bool solution(string s)
{
    bool answer = true;
    StackType stack;
    int i;
    
    //스택 초기화
    stack.top = -1;
    
    for(i=0; i<s.length(); i++) {
        if(s.at(i) == '(') {
            stack.arr[(++stack.top)] = 1;
        } else {    //닫는 괄호이면 스택에서 팝한다. 이때 예외에 대해서 미리 검사
            if(stack.top < 0) { //스택이 비어있을 경우
                answer = false;
                break;
            } else {
                stack.top = stack.top - 1;
            }
        }
    }
    
    if(stack.top >= 0) {    //스택이 비어있지 않을 경우
        answer = false;
    }

    return answer;
}
