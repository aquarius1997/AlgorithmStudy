//
//  PGS_라면공장.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/17.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
    priority_queue<int> pq;
    int datesIdx = 0;
    
    for(int i=0; i<=k-1; i++) {
        //해당 날짜에 공급이 되면 일단 힙에 추가
        if(datesIdx < dates.size()) {
            if(dates[datesIdx] == i) {
                pq.push(supplies[datesIdx]);
                datesIdx++;
            }
        }
        
        //현재 밀가루 수량이 0이면 힙에 있는 공급량들 중 가장 큰거를 빼내서 추가한다
        if(stock == 0) {
            int maxSupply = pq.top();
            pq.pop();
            stock += maxSupply;
            answer++;
        }
        
        //밀가루 1톤 소비
        stock -= 1;
    }
    return answer;
}


int main(void) {
    int stock = 4;
    vector<int> dates; vector<int> supplies;
    int k = 100;

    
    dates.push_back(1);
    dates.push_back(2);
    dates.push_back(3);
    dates.push_back(4);

    supplies.push_back(10);
    supplies.push_back(40);
    supplies.push_back(30);
    supplies.push_back(20);

    
    int a = solution(stock, dates, supplies, k);
    
    printf("%d", a);
    
    return 0;
}
