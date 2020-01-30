//
//  1697_숨바꼭질.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/30.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
#include <queue>
using namespace std;


int dist[100002] = {0, };
int N, K;

void min_dist(void) {
    queue<int> Queue;
    int x;
    int d;
    
    Queue.push(N);
    
    while(!Queue.empty()) {
        x = Queue.front();  Queue.pop();
        d = dist[x]+1;
        
        if(x-1 >= 0) {
            if(dist[x-1] == 0 || dist[x-1] > d) {   //아직 안 간 루트이거나 더 최소로 갈 수 있으면
                dist[x-1] = d;
                Queue.push(x-1);
            }
        }
        if(x+1 <= 100000) {
            if(dist[x+1] == 0 || dist[x+1] > d) {
                dist[x+1] = d;
                Queue.push(x+1);
            }
        }
        if(x*2 <= 100000) {
            if(dist[x*2] == 0 || dist[x*2] > d) {
                dist[x*2] = d;
                Queue.push(x*2);
            }
        }
    }
}

int main(void) {
    
    scanf("%d %d", &N, &K);
    
    dist[N] = 1;
    
    min_dist();
    
    printf("%d", dist[K]-1);
    
    return 0;
}
