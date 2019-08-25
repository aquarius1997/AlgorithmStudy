//
//  10845Queue.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <cstdio>
#include <string.h>
#include <queue>
using namespace std;

queue <int> Queue;

int main(void) {
    int N, X;  char operation[10];
    int i;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%s", operation);
        
        if(strcmp(operation, "push") == 0){
            
            scanf("%d", &X);
            Queue.push(X);
            
        }else if(strcmp(operation, "pop") == 0) {
            
            if(Queue.empty()) {
                printf("-1\n");
            }else {
                printf("%d\n", Queue.front());
                Queue.pop();
            }
            
        }else if(strcmp(operation, "size") == 0) {
            
            printf("%d\n", (int)Queue.size());
            
        }else if(strcmp(operation, "empty") == 0) {
            
            if(Queue.empty() == 1) {
                printf("1\n");
            }else {
                printf("0\n");
            }
            
        }else if(strcmp(operation, "front") == 0) {
            
            if(Queue.empty()) {
                printf("-1\n");
            }else {
                printf("%d\n", Queue.front());
            }
            
        }else {
            
            if(Queue.empty()) {
                printf("-1\n");
            }else {
                printf("%d\n", Queue.back());
            }
            
        }
    }
    
    return 0;
}
