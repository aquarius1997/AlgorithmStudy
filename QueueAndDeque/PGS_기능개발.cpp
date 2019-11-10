//
//  PGS_기능개발.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/08.
//  Copyright © 2019 송혜경. All rights reserved.
//

/*
 1. 완료될 날짜를 순서대로 큐에 삽입
 2. 큐가 빌때까지 반복
    1) 큐에서 pop 한걸 number라고 치면
    2) 큐의 front값이 number보다 작거나 같을 경우 큐에서 pop
    3) 이때 pop한 개수를 카운팅
    4) 큐의 front값이 number보다 크면 카운팅 한 수를 answer에 push_back
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> Queue;
    int remain, temp, number, cnt;
    int i;
    
    
    // progresses와 speeds에 대하여 완료될 날짜를 순서대로 구한다
    for(i=0; i<progresses.size(); i++) {
        //남은 기능 구현량
        remain = 100 - progresses[i];
        
        if(speeds[i] > remain) {
            temp = 1;
        }else {
            //작업일 구하기
            temp = (remain / speeds[i]);
            if(remain % speeds[i] != 0) {
                temp += 1;
            }
        }
        
        printf("temp : %d\n", temp);
        
        //작업일을 큐에 삽입
        Queue.push(temp);
    }
        
    
    //큐가 빌때까지 반복
    while(!Queue.empty()) {

        cnt = 0;
        //큐의 front 값을 알아낸다
        number = Queue.front(); Queue.pop();
        cnt += 1;

        //number보다 큐의 front값이 작거나 같을때까지 pop한다
        while(Queue.front() <= number && !Queue.empty()) {
            Queue.pop();
            cnt += 1;
        }

        //큐에서 뺀 개수(cnt)를 answer에 push_back
        answer.push_back(cnt);

    }

    return answer;
}

int main(void) {
    vector <int> v1;
    vector <int> v2;
    vector <int> an;
    
    v1.push_back(93);
    v1.push_back(30);
    v1.push_back(55);
    
    v2.push_back(1);
    v2.push_back(30);
    v2.push_back(5);
    
    an = solution(v1, v2);
    
    for(int i=0; i<an.size(); i++) {
        printf("%d ", an[i]);
    }
    
    return 0;
}
