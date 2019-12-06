//
//  라이브러리를사용한힙.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/05.
//  Copyright © 2019 송혜경. All rights reserved.
//  MAXHEAP

#include <cstdio>
#include <queue>
using namespace std;


int main(void) {
    priority_queue<int> pq;
    int N;
    
    scanf("%d", &N);
    
    for(int i=0; i<N; i++) {
        int in;
        
        scanf("%d", &in);
        
        pq.push(in);
    }
    
    while(!pq.empty()) {
        printf("%d ", pq.top());
        pq.pop();
    }
    
    return 0;
}
