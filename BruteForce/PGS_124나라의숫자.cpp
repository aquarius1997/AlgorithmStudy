//
//  PGS_124나라의숫자.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/06.
//  Copyright © 2019 송혜경. All rights reserved.
//  바보같이 순열방식으로 풂. 더 빨리풀수있는데


#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

int result[20] = {0, }; //숫자 n을 124나라의 숫자로 바꾼 수
int cnt = 0;
string temp = "";

void make_num(int n, int a, int idx) {
    
    //길이 a로 124 숫자를 만들면
    if(idx == a) {
        
        cnt += 1;
        
        //cnt가 찾으려는 10진수 n이랑 같으면 해당 124숫자가 정답이다
        if(cnt == n) {
            for(int i=0; i<idx; i++) {
                //printf("%d", result[i]);
                ostringstream o;
                o << result[i];
                temp.append(o.str());
            }
            temp[idx] = '\n';
            return;
        }
    }else {
        result[idx] = 1;
        make_num(n, a, idx+1);
        result[idx] = 2;
        make_num(n, a, idx+1);
        result[idx] = 4;
        make_num(n, a, idx+1);
    }
}


void len_a(int n, int a) {
    int temp = 3;
    int num = 3;
    
    while(n > num) {
        
        temp *= 3;
        
        num += temp;
        
        a += 1;
    }
    
    cnt = num - temp;
    
    make_num(n, a, 0);
}

string solution(int n) {
    string answer = "";
    
    len_a(n, 1);
    
    answer.append(temp);
    
    return answer;
}

int main(void) {
    solution(5);
    
    return 0;
}
