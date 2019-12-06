//
//  힙구현.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/05.
//  Copyright © 2019 송혜경. All rights reserved.
//  MAX_HEAP 구현

// !!! Heap은 인덱스 1번부터 시작함에 유의
#include <stdio.h>
const int MAXN = 100;

typedef struct PriorityQueue {
    int data[MAXN];
    int len = 1;    //len은 원소의 마지막을 가리킴
    
    //1. 맨 끝에 값을 push
    //2. 부모노드와 비교하며 우선순위큐를 만든다
    void push(int x) {
        int idx;
        
        data[len] = x;
        idx = len;  //방금 삽입한 노드의 위치 저장
        len++;
        
        while(idx > 1) {    //루트가 아닐때까지 부모랑 비교하며 위치 조정을 반복한다
            if(data[idx] > data[idx/2]) {   //자식노드가 더 크면 위치 바꿈
                int temp = data[idx/2];
                data[idx/2] = data[idx];
                data[idx] = temp;
                
                idx = idx/2;
            } else break;
        }
    }   //end push function
    
    //1. 요소 pop : 루트노드 제거
    //2. 마지막 요소를 루트노드로 가져오고 크기를 -1 한다
    //3. 우선순위 큐로 만든다
    void pop() {
        int idx;
        int childIdx;
        
        data[1] = data[len-1];
        len--;
        
        idx = 1;
        
        // 1. 왼쪽과 오른쪽 자식이 있는지 확인한다
        // 2. 자식들 중에서 우선순위가 높은 자식을 알아내서
        // 3. 해당 자식노드와 자리를 바꾼다
        while(1) {
            childIdx = -1;
            
            //자식노드가 있는지 확인하는 과정
            if(idx*2 >= len) {  //자식노드가 없을 경우
                break;
            } else if((idx*2 < len && idx*2 >= 1) && idx*2+1 >= len) { //왼쪽 자식만 존재할 경우
                childIdx = idx*2;
            } else {    //왼쪽, 오른쪽 자식이 모두 존재할경우
                //어떤 자식이 더 큰지 알아냄
                if(data[idx*2] > data[idx*2 + 1]) { //왼쪽 자식이 더 클때
                    childIdx = idx*2;
                } else { //오른쪽 자식이 더 크면
                    childIdx = idx*2 + 1;
                }
            }
            
            if(data[idx] < data[childIdx]) {    //자식노드가 더 클 경우 자리 바꿈
                int temp = data[idx];
                data[idx] = data[childIdx];
                data[childIdx] = temp;
                
                idx = childIdx;
            } else break;
        }
    }   //end pop function
    
    int top() {
        return data[1];
    }
    
}PriorityQueue;

int main(void) {
    PriorityQueue q;
    
    q.push(5);
    q.push(3);
    q.push(1);
    q.push(2);
    q.push(10);
    q.push(4);
    
    printf("%d\n", q.top());
    q.pop();
    
    printf("%d\n", q.top());
    q.pop();
    
    printf("%d\n", q.top());
    q.pop();
    
    printf("%d\n", q.top());
    q.pop();
    
    printf("%d\n", q.top());
    q.pop();
    
    printf("%d\n", q.top());
    q.pop();
    
    return 0;
}

