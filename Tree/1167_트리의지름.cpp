//
//  1167_트리의지름.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/09.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***** 수학적 지식이 딸리는 나의 멍청한 두뇌가 죄지

/*
 처음엔 모든 정점에 대하여 dfs 탐색을 수행해 시간초과가 남
 트리의 개넘이 중요!!
 
 하나의 정점에서 가장 멀리 있는 정점은 원의 지름 부분에 해당하는 정점이다.
 따라서 원의 지름 부분에 해당하는 정점을 알아내서 이를 기준으로 가장 깊이(멀리) 존재하는 정점을 알아내면 그것이 또 다른 원의 지름부분에 해당하는 정점이므로
 이 둘 사이의 거리를 알아내면 된다. -> 2번의 DFS
 */

#include <cstdio>
#include <vector>

using namespace std;

vector<int> nodes[100002];  //nodes[i][j] : i노드와 인접 노드인 노드의 번호를 저장한다
vector<int> nodes_dis[100002];  //nodes_dis[i][j] : i노드와 인접노드간의 거리를 저장한다
int visited[100002] = {0, };
int flag = 0;
int startNode;
int maxDist = 0;

/// node와 연결된 (방문하지 않은) 인접정점들에 대하여 DFS 탐색을 수행한다
/// @param node dfs탐색 경로에 포함되는 노드
/// @param dist 시작정점으로 부터 node까지의 거리
void dfs_f(int node, int dist) {
    int w;
    int nextNode, distance;
    
    visited[node] = 1;
    
    //트리의 지름을 구한다
    if(dist > maxDist) {
        maxDist = dist;
        if(flag == 0) {
            startNode = node;
        }
    }
    
    //모든 인접정점들에 대하여
    for(w=0; w<nodes[node].size(); w++) {
        nextNode = nodes[node][w];  //인접정점 번호
        distance = nodes_dis[node][w];  //해당 인접정점과의 거리
        
        if(visited[nextNode] == 0) {    //인접정점으로 아직 방문안했으면 인접정점을 기준으로 dfs탐색
            dfs_f(nextNode, dist+distance);
        }
    }
    
    visited[node] = 0;
}

int main(void) {
    int V, v;
    int u, w, d;
    
    scanf("%d", &V);
    
    for(v=1; v<=V; v++) {   //V개의 정점들에 대하여 반복
        scanf("%d", &u);    //시작 정점 번호 입력
        while(1) {
            scanf("%d", &w); //목적지 정점 번호 입력
            if(w == -1){
                break;
            }
            scanf("%d", &d); //정점 u, w간의 거리 입력
            
            nodes[u].push_back(w);  //목적지 정점과
            nodes_dis[u].push_back(d);  //해당 목적지 정점까지의 거리를 삽입
        }
    }
    
    //임의의 한 정점으로 부터 가장 멀리 떨어진 정점을 찾음
    dfs_f(1, 0);
    
    flag = 1;
    maxDist = 0;
    
    //위에서 찾은 정점을 기준으로 가장 먼 거리를 찾으면 된다
    dfs_f(startNode, 0);
    
    printf("%d", maxDist);
    
    return 0;
}

