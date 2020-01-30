//
//  11279_최대힙.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/23.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <stdio.h>

typedef struct HeapType {
    int arr[100002];    //트리 구조니깐 인덱스 1부터 시작해야함을 유의
    int idx;
}HeapType;

HeapType h;

void insert_heap(int element) {
    int parentNode;
    int elementIdx;
    int temp;
    int i;
    
    //트리 마지막에 요소를 집어넣는다
    h.arr[(h.idx)] = element;
    elementIdx = h.idx;
    h.idx++;
    
    //최대 힙 만들기
    for(i=elementIdx; i>1; i=i/2){
        parentNode = h.arr[(i/2)];
        
        if(parentNode < h.arr[i]) { //자식노드가 더 크면 자리 바꿔
            temp = h.arr[i];
            h.arr[i] = parentNode;
            h.arr[(i/2)] = temp;
        } else {
            break;
        }
    }
}

int pop_heap(void) {
    int element;
    int bigger, biggerIdx;
    int eIdx;
    int temp;
    
    if(h.idx == 1) {    //힙이 비어있을 경우
        element = 0;
    } else {
        element = h.arr[1]; //루트 요소가 최대값
        
        h.arr[1] = h.arr[(h.idx-1)];    //마지막 요소를 루트에 넣고 최대 힙을
        h.idx--;
        
        
        eIdx = 1;
        while(1) {
            //왼쪽, 오른쪽 자식 노드가 있을 경우
            if(eIdx*2+1 < h.idx) {
                //어떤 자식 노드가 더 큰지 알아내고
                if(h.arr[eIdx*2] > h.arr[eIdx*2+1]) {
                    bigger = h.arr[eIdx*2];
                    biggerIdx = eIdx*2;
                } else {
                    bigger = h.arr[eIdx*2+1];
                    biggerIdx = eIdx*2+1;
                }
                
                if(h.arr[eIdx] < bigger) {  //맥스힙으로 만들어야할 경우
                    temp = h.arr[eIdx];
                    h.arr[eIdx] = h.arr[biggerIdx];
                    h.arr[biggerIdx] = temp;
                    
                    eIdx = biggerIdx;
                } else {
                    break;
                }
            } else if(eIdx*2 < h.idx) { //왼쪽 자식 노드만 있을 경우
                if(h.arr[eIdx*2] > h.arr[eIdx]) {   //맥스힙으로 만들어야할 경우
                    temp = h.arr[eIdx];
                    h.arr[eIdx] = h.arr[eIdx*2];
                    h.arr[eIdx*2] = temp;
                    
                    eIdx = eIdx*2;
                } else {
                    break;
                }
            } else {
                break;
            }
        }   //end while
    }
    
    
    return element;
}

int main(void) {
    int N, op;
    int element;
    int i;
    
    scanf("%d", &N);
    
    //init queue
    h.idx = 1;
    
    for(i=0; i<N; i++) {
        scanf("%d", &op);
        
        if(op != 0) {//push
            insert_heap(op);
        } else {
            element = pop_heap();
            printf("%d\n", element);
        }
    }
    
    return 0;
}
