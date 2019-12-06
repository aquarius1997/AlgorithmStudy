//
//  PGS_더맵게.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/05.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int> pq;
    int answer = 0;
    int cnt = 0;
    int i;
    
    //우선순위 큐에 스코빌 지수를 -1 곱해서 넣는다. -> min-heap으로 구현해야하므로
    for(i=0; i<scoville.size(); i++) {
        pq.push((scoville[i] * -1));
    }
    
    while(1) {
        
        if(pq.size() <= 1) {    //모든 음식의 스코빌 지수를 K이상으로 만들 수 없을 경우
            if((pq.top() * -1) >= K) {
                answer = cnt;
            } else {
                answer = -1;
            }
            break;
        } else {
            if((pq.top() * -1) < K) {  //모든 음식의 스코빌 지수가 K 이상이 아니면
                //새 음식을 만든다
                int scov1 = pq.top() * -1;   pq.pop();
                int scov2 = pq.top() * -1;   pq.pop();
                
                int newScov = scov1 + (scov2 * 2);
                
                pq.push((newScov * -1));   //새로은 음식의 스코빌 지수를 우선순위큐에 삽입한다
                cnt += 1;
            } else {    //모든 음식의 스코빌 지수가 K 이상이면
                answer = cnt;
                break;
            }
        }
    }

    
    return answer;
}

