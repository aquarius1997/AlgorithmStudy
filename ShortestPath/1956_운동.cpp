//
//  1956_운동.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
#include <queue>
#include <vector>
#define MAXN    401
#define INFI    987987987
using namespace std;

int main(void) {
    vector<int> Graph[MAXN];
    vector<int> weight[MAXN];   //간선의 가중치 저장
    queue<int> Queue;
    int dist[MAXN][MAXN] = {0,};
    int V, E, a, b, c;
    int inNode, nextNode;
    int minCycle = INFI;
    
    scanf("%d %d", &V, &E);
    
    //최단 거리를 일단 무한대로 잡아둔다
    for(int i=1; i<=V; i++) {
        for(int j=1; j<=V; j++) {
            dist[i][j] = INFI;
        }
    }
    
    for(int i=0; i<E; i++) {
        scanf("%d %d %d", &a, &b, &c);
        //방향그래프임에 유의
        Graph[a].push_back(b);
        weight[a].push_back(c);
    }
    
    for(int i=1; i<=V; i++) {   //각 노드들에 대해 최단거리를 알아낸다
        Queue.push(i);  //시작노드 푸시
        
        while(!Queue.empty()) {
            inNode = Queue.front(); Queue.pop();
            
            for(int j=0; j<Graph[inNode].size(); j++) {
                nextNode = Graph[inNode][j];
                
            
                if(inNode == i) {
                    dist[i][nextNode] = weight[inNode][j];
                    Queue.push(nextNode);
                } else {
                    //최단거리 업데이트 가능하면
                    if(dist[i][nextNode] > dist[i][inNode] + weight[inNode][j]) {
                        dist[i][nextNode] = dist[i][inNode] + weight[inNode][j];
                        if(nextNode != i) {
                            Queue.push(nextNode);
                        }
                    }
                }
            }
        }
    }
    

    for(int i=1; i<=V; i++) {
        if(dist[i][i] < minCycle) {
            minCycle = dist[i][i];
        }
    }
    
    if(minCycle == INFI) {
        minCycle = -1;
    }
    
    printf("%d", minCycle);

    return 0;
}
