//
//  PGS_구명보트.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/08.
//  Copyright © 2019 송혜경. All rights reserved.
// ***

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//내가 merge_sort 만들어서 돌리니깐 시간초과여서 걍 sort 사용함 ㅋ

int solution(vector<int> people, int limit) {
    int arr[50002] = {0, };
    int answer = 0;
    int cnt = 0;
    int i, j;

 
    for(int i=0; i<people.size(); i++) {
        arr[i] = people[i];
    }

    sort(arr, arr+(people.size()));
    
    for(i=0; i<people.size(); i++) {
        printf("%d ", arr[i]);
    }

    i = 0;  j = people.size()-1;    //i : 첫번째 인덱스를 가리킴, j : 마지막 인덱스를 가리킴
 
    while(i < j) {
        //두개 더해서 초과이면 현재 보트에 남아있는 사람중 가장 무거운 사람만 태운다
        if(arr[i] + arr[j] > limit) {
            cnt += 1;
            j--;
        } else {    //두명 더해서 limit 이하이면 현재 보트에 남아있는 사람 중 가장 무거운 사람과 가장
            //가벼운 사람을 태운다
            cnt += 1;
            i++;
            j--;
        }
    }
    //마지막 한명이 남아있으면
    if(i == j) {
        cnt += 1;
    }
    
    answer = cnt;
    
    return answer;
}

int main(void) {
    vector<int> people;
    
    people.push_back(2);
    people.push_back(5);
    people.push_back(1);
    people.push_back(8);
    people.push_back(7);
    
    
    solution(people, 100);
    return 0;
}
