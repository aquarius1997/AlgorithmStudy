//
//  PGS_쇠막대기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/08.
//  Copyright © 2019 송혜경. All rights reserved.
//
/*
 여는괄호이면 push
 닫는괄호이면 pop, 쇠막대기수+1
 레이저면 쇠막대기수 + 스택요소의개수
 */

#include <string>
#include <vector>

using namespace std;

typedef struct StackType {
    int top;
    int arr[100002];
}StackType;

int solution(string arrangement) {
    StackType s;
    int answer = 0;
    int len = arrangement.length();
    
    //스택 초기화
    s.top = -1;
    
    for(int i=0; i<len; i++) {
        //여는 괄호이면 스택에 push
        if(arrangement[i] == '(') {
            s.arr[++(s.top)] = 1;
        }else if(arrangement[i] == ')') {
            if(arrangement[i-1] == '(') {   //레이저이면
                //이전 여는 괄호는 막대기가 아닌 레이저이므로 pop
                s.top -= 1;
                //스택 요소 수만큼 막대 수 누적
                answer += (s.top + 1);
            }else { //레이저아니면
                //막대수 +1 하고 pop
                answer += 1;
                s.top -= 1;
            }
        }
    }
    
    return answer;
}
