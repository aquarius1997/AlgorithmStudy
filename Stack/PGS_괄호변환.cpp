//
//  PGS_괄호변환.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/19.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;


typedef struct StackType {
    int top;
    int arr[1002];
}StackType;

string make_nice(string p) {
    StackType s;
    string u, v, retstr;
    int open, close;
    int idx, len;
    int stackFlag;
    int i;
    
    open = close = stackFlag = 0;
    
    //빈 문자열일 경우
    if(p.length() == 0) {
        return p;
    }else {
        //균형잡힌 괄호 문자열 u, v로 분리
        for(i=0; i<p.length(); i++) {
            if(p[i] == '(') {
                open++;
            }else {
                close++;
            }
            
            //균형 잡힌 괄호 문자열 u의 범위를 찾아냄
            if(open == close) {
                break;
            }
        }
        
        //u가 string의 idx까지(포함)임을 표시
        idx = i;

        //문자열 u, v만들기
        len = p.length() - idx - 1;
        u = p.substr(0, (idx+1));
        //v가 빈 문자열일 경우
        if(idx == p.length()) {
            v = "";
        }else { //빈 문자열이 아닐 경우
            v = p.substr((idx+1), len);
        }
        
        s.top = -1; //스택 초기화
        
        //u가 올바른 문자열인지 확인
        for(i=0; i<=idx; i++) {
            if(p[i] == '(') {   //푸시
                s.arr[(++s.top)] = 1;
            }else {
                //올바른 문자열이 아닐 경우
                if(s.top == -1) {
                    stackFlag = 1;
                    break;
                }else {
                    s.top -= 1;
                }
            }
        }
            
        //u가 올바른 괄호 문자열 아니면
        if(stackFlag == 1) {
            string temp = "(";
            retstr = make_nice(v);
            temp.append(retstr);
            temp.append(")");
            
            //첫번째와마지막 문자 제거
            int cnt = u.length() - 2;
            u = u.substr(1, cnt);
            //괄호의 방향을 뒤집는다
            cnt = u.length();
            for(i=0; i<cnt; i++) {
                if(u[i] == '(') {
                    u[i] = ')';
                }else {
                    u[i] = '(';
                }
            }
            //temp 뒤에 붙인다
            temp.append(u);
            
            return temp;
            
        }else { //u가 올바른 괄호 문자열이면
            //문자열 v에 대해 1단계부터 수행
            retstr = make_nice(v);
            //수행 결과 문자열을 u에 이어붙인후 반환 !!!!
            u.append(retstr);
            return u;
        }

    }
}

string solution(string p) {
    string answer;
    
    answer = make_nice(p);
    
    return answer;
}
