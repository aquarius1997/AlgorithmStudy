//
//  D6_영준이의진짜BFS.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/05.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****
//  다시 풀어야함 -> Segment tree 알고리즘 학습하기!

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef struct TreeNode {
    int parent;
    int depth;
} TreeNode;


int main(void) {
    int t, T;
    int nodeNum, parentN;
    queue<int> Queue;
    int currentN, nextN, node;
    int currentParent, nextParent;
    int diff;
    int distance = 0;
    
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d", &nodeNum);
        
        vector<vector<int>> graph(nodeNum+2);
        TreeNode tree[100002];

        tree[1].parent = -1;
        tree[1].depth = 0;
        
        for(int i=2; i<=nodeNum; i++) {
            scanf("%d", &parentN);
            
            //tree, graph초기화
            tree[i].parent = parentN;
            tree[i].depth = tree[parentN].depth + 1;
            graph[parentN].push_back(i);
        }
        
        Queue.push(1);
        currentN = 1;
        
        while(!Queue.empty()) {
            node = Queue.front();   Queue.pop();
            
            for(int i=0; i<graph[node].size(); i++) {
                nextN = graph[node][i];
                
                if(i == 0) {
                    if(tree[nextN].parent == currentN) {
                        distance += 1;
                    } else {
                        if(tree[currentN].depth == tree[nextN].depth) {
                            currentParent = tree[currentN].parent;
                            nextParent = tree[nextN].parent;
                            distance += 2;
                            
                            while(1) {
                                if(currentParent == nextParent) {
                                    break;
                                }
                                currentParent = tree[currentParent].parent;
                                nextParent = tree[nextParent].parent;
                                distance += 2;

                            }
                        } else if(tree[nextN].depth > tree[currentN].depth) {
                            diff = (tree[nextN].depth - tree[currentN].depth);
                            nextParent = tree[nextN].parent;
                            for(int j=1; j<diff; j++) {
                                nextParent = tree[nextParent].parent;
                            }
                            distance += diff;
                            
                            currentParent = tree[currentN].parent;
                            nextParent = tree[nextParent].parent;
                            distance += 2;
                            
                            while(1) {
                                if(currentParent == nextParent) {
                                    break;
                                }
                                currentParent = tree[currentParent].parent;
                                nextParent = tree[nextParent].parent;
                                distance += 2;

                            }
                        }
                    }
                } else {
                    distance += 2;
                }
                
                currentN = nextN;
                Queue.push(nextN);
                
                
            }
        }
        
        printf("#%d %d\n", t, distance);
        
        
        distance = 0;
    }
    
    return 0;
}

