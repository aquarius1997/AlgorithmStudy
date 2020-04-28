//
//  PGS_test1.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/21.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<vector<int>> persons;
    vector<int> person1;
    vector<int> person2;
    vector<int> person3;
    vector<int> cnts;
    int answersIdx, personIdx;
    int maxCnt = 0;
    int cnt = 0;
    int i;
    
    //첫번째 수포자의반복되는 숫자 배열
    for(i=1; i<=5; i++) {
        person1.push_back(i);
    }
        
    //두번째 수포자의 반복되는 숫자 배열
    for(i=1; i<=5; i++) {
        if(i != 2) {
            person2.push_back(2);
            person2.push_back(i);
        }
    }
    
    //세번째 수포자의 반복되는 숫자 배열
    for(i=0; i<2; i++) {
        person3.push_back(3);
    }
    for(i=0; i<2; i++) {
        person3.push_back(1);
    }
    for(i=0; i<2; i++) {
        person3.push_back(2);
    }
    for(i=0; i<2; i++) {
        person3.push_back(4);
    }
    for(i=0; i<2; i++) {
        person3.push_back(5);
    }
    
    persons.push_back(person1);
    persons.push_back(person2);
    persons.push_back(person3);
    
    
    //각 사람당 문제를 맞춘 개수 구하기
    for(i=0; i<3; i++) {
        cnt = 0;
        //문제 개수만큼 확인
        answersIdx = personIdx = 0;
        while(true) {
            if(answers[answersIdx] == persons[i][personIdx]) {
                printf("%d\n", persons[i][personIdx]);
                cnt++;
            }
            personIdx++;
            answersIdx++;
            //종료조건
            if(answersIdx == answers.size()) { break; }
            //범위 이내에서 반복확인하도록
            if(personIdx == persons[i].size()) {
                personIdx = 0;
            }
        }
        
        cnts.push_back(cnt);
    }
    
    //max값알아내고
    for(i=0; i<3; i++) {
        if(cnts[i] > maxCnt) { maxCnt = cnts[i];}
    }
    
    //max인 사람들 순서대로 푸시
    for(i=0; i<3; i++) {
        if(maxCnt == cnts[i]) {
            answer.push_back(i+1);
        }
    }
    
    return answer;
}


int main(void) {
    vector<int> answer;
    
    answer.push_back(1);
    answer.push_back(2);
    answer.push_back(3);
    answer.push_back(4);
    answer.push_back(5);
    
    vector<int> a = solution(answer);
    
    for(int i=0; i<a.size(); i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
