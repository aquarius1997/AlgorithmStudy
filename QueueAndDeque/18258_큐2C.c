//
//  18258_큐2C.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/16.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>
#include <string.h>
/// !!! 처음 const int ARRSIZE = 2000001; 로 했을 때, "error: variably modified ‘arr’ at file scope" 에러가 발생했음.
/// 찾아보니 C의 const 상수(constant)를 의미하는 것이 아닌 "readonly"의 특성을 띈다. 더 상세히 알자면 const는 runtime object이므로 할당에 사용할 수 없고 #define은 compile-time의 상수로서 사용되므로 #define을 사용해야한다.
#define ARRSIZE 2000001

typedef struct QueueType {
    int arr[ARRSIZE];
    int front, rear;
    int cnt;
}QueueType;

void initQueue(QueueType *q) {
    q->front = q->rear = 0;
    q->cnt = 0;
}

void push(QueueType *q, int element) {
    q->arr[q->rear] = element;
    q->rear = (q->rear + 1) % ARRSIZE;
    q->cnt += 1;
}

int pop(QueueType *q) {
    int element;
    if(q->cnt == 0) {
        return -1;
    }
    element = q->arr[q->front];
    q->front = (q->front + 1) % ARRSIZE;
    q->cnt -= 1;
    
    return element;
}

int size(QueueType *q) {
    return (q->cnt);
}

int isEmpty(QueueType *q) {
    if(q->cnt == 0) {
        return 1;
    } else {
        return 0;
    }
}

int front(QueueType *q) {
    if(q->cnt == 0) {
        return -1;
    }
    return (q->arr[q->front]);
}

int back(QueueType *q) {
    if(q->cnt == 0) {
        return -1;
    }
    if(q->rear == 0) {
        return (q->arr[ARRSIZE-1]);
    }
    return (q->arr[(q->rear - 1)]);
}

int main(void) {
    QueueType q;
    char op[10];
    int N, element;
    int i;
    
    scanf("%d", &N);
    
    initQueue(&q);
    
    for(i=0; i<N; i++) {
        scanf("%s", op);
        
        if(strcmp(op, "push") == 0) {
            scanf("%d", &element);
            push(&q, element);
        } else if(strcmp(op, "pop") == 0) {
            element = pop(&q);
            printf("%d\n", element);
        } else if(strcmp(op, "size") == 0) {
            element = size(&q);
            printf("%d\n", element);
        } else if(strcmp(op, "empty") == 0) {
            element = isEmpty(&q);
            printf("%d\n", element);
        } else if(strcmp(op, "front") == 0) {
            element = front(&q);
            printf("%d\n", element);
        } else {
            element = back(&q);
            printf("%d\n", element);
        }
        
    }
    
    return 0;
}
