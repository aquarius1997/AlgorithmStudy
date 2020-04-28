//
//  PGS_네트워크.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/24.
//  Copyright © 2020 송혜경. All rights reserved.
//  10min *

#include <cstdio>
#include <vector>

using namespace std;

int visited[202] = {0, };

void dfs_visit(vector<vector<int>> computers, int node) {
    int i;
    
    visited[node] = 1;
    for(i=0; i<computers[node].size(); i++) {
        if(visited[i] == 0 && computers[node][i] == 1) {
            dfs_visit(computers, i);
        }
    }
}


int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    int i, j;
    
    for(i=0; i<computers.size(); i++) {
        for(j=0; j<computers[i].size(); j++) {
            if(visited[j] == 0 && computers[i][j] == 1) {
                answer++;
                dfs_visit(computers, i);
            }
        }
    }
    
    return answer;
}
