//
//  1260DFS와BFS.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

vector <int> Graph[1010];
int visited[1010] = {0, };  //방문 여부를 저장할 배열
int N, M, V;

//시작 정점을 입력받는다
void dfs_func(int v) {
    int i;
    int min_v;  //방문안한 최소 정점
    int flag;   //인접 정점에 대해 모두 방문했는지 여부를 살핀다
    
    visited[v] = 1;
    printf("%d ", v);
    
    do{
        flag = 0;
        min_v = 987987987;
        
        for(i=0; i<Graph[v].size(); i++) {
            //방문 안한 정점중 최소 정점을 찾는다
            if(visited[(Graph[v][i])] == 0) {
                flag = 1;
                if(min_v > Graph[v][i])
                    min_v = Graph[v][i];
            }
        }
        
        if(flag == 1){
            //방문안한 최소 정점에 대해 dfs_func호출
            dfs_func(min_v);
        }
        
    }while(flag == 1);
}

void bfs_func(int v) {
    queue <int>Queue;
    int front_n;
    int flag, min_v;
    int i;
    
    Queue.push(v);
    visited[v] = 1;
    
    //큐가 빌때까지 반복
    while(!Queue.empty()) {
        front_n = Queue.front();
        Queue.pop();
        printf("%d ", front_n);
        
        do{
            flag = 0;
            min_v = 987987987;
            
            //모든 인접노드들에 대하여 방문안한 최소 노드를 찾는다
            for(i=0; i<Graph[front_n].size(); i++) {
                if(visited[(Graph[front_n][i])] == 0) {
                    flag = 1;
                    if(min_v > Graph[front_n][i])
                        min_v = Graph[front_n][i];
                }
            }
            
            if(flag == 1){
                Queue.push(min_v);
                visited[min_v] = 1;
            }
            
        }while(flag == 1);
        
    }
}

int main(void) {
    int i;
    int u, v;
    
    scanf("%d %d %d", &N, &M, &V);
    
    //그래프의 정보를 입력받는다
    for(i=0; i<M; i++) {
        scanf("%d %d", &u, &v);
        
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    
    dfs_func(V);
    
    for(i=0; i<1010; i++)
        visited[i] = 0;
    
    printf("\n");
    
    bfs_func(V);
    
    return 0;
    
}
