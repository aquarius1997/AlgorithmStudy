//
//  1967_트리의노드.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/11.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 10002;    //트리의 최대 노드 개수
vector<int> nodes[MAXN];    //nodes[i] -> i번 노드의 자식 노드 정보를 저장한다
vector<int> weights[MAXN];  //weights[i] -> i번 노드와 자식간의 가중치 정보를 저장한다
int visited[MAXN] = {0, };  //dfs 방문 여부를 표시한다
int flag = 0;
int diameterNode;
int diameter = 0;

/// node의 인접정점에 대하여 dfs탐색을 수행한다. dfs탐색을 수행하며 가장 깊은 노드의 번호와 가장 깊은 거리를 알아낸다.
/// @param node dfs탐색을 수행할 노드의 번호
/// @param dist 처음 dfs_f를 호출한 노드번호로부터 node까지의 거리
void dfs_f(int node, int dist) {
    int childNode, distance;
    int i;
    
    visited[node] = 1;  //방문함을 표시
    
    if(dist > diameter) {   //가장 멀리 있는 노드일 경우
        if(flag == 0) { //부모노드로부터 가장 멀리 있는 노드의 번호를 알려고 했던 것이라면
            diameterNode = node;
        }
        diameter = dist;
    }
    
    for(i=0; i<nodes[node].size(); i++) {
        childNode = nodes[node][i]; //자식 노드 번호
        distance = weights[node][i];    //자식 노드와의 거리
        
        if(visited[childNode] == 0) {   //방문하지 않은 자식노드는 방문
            dfs_f(childNode, dist+distance);
        }
    }
    
    visited[node] = 0;  //이후 visited 초기화 없이 재사용하기 위해 0으로 저장
}

int main(void) {
    int n;
    int parent, child, weight;
    int i;
    
    scanf("%d", &n);
    
    for(i=0; i<n-1; i++) {
        scanf("%d %d %d", &parent, &child, &weight);
        
        //양방향 그래프
        nodes[parent].push_back(child);
        nodes[child].push_back(parent);
        weights[parent].push_back(weight);
        weights[child].push_back(weight);
    }
    
    dfs_f(1, 0);    //루트로부터 가장 멀리있는 노드의 번호을 알아내고
    diameter = 0;   //diameter초기화
    flag = 1;
    dfs_f(diameterNode, 0); //diameterNode로부터 가장 먼 거리가 트리의 지름이다
    
    printf("%d", diameter);
    
    return 0;
}
