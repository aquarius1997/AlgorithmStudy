//
//  2156_포도주시식.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/07.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <stdio.h>
#define MAXW(a, b)  (((a) > (b)) ? a : b)

int main(void) {
    int wine[10002] = {0, };    //입력으로 받은 포도주의 양
    int T[10002] = {0,};    //T[i] ; 포도주 잔이 i개 있을 때, 가장 많이 먹을 수 있는 양을 저장
    int first, second, third;
    int n, i;
    
    scanf("%d", &n);
    
    for(i=1; i<=n; i++) {
        scanf("%d", &wine[i]);
    }
    
    //base-case
    T[1] = wine[1];
    T[2] = wine[1] + wine[2];
    T[3] = MAXW((MAXW(wine[1]+wine[2], wine[2]+wine[3])), wine[1] + wine[3]);
    
    //induction-step
    /*연속으로 세잔을 마실 수 없으므로 고려해야 하는 경우의 수는
     1) i번째 와인을 마시지 않아 i-1개를 최대로 마실 수 있는 경우
     2) i번째 와인을 마시고 i-1번째 와인을 마시지 않은 상태에서 i-2개를 최대로 마실 수 있는 경우
     3) i, i-1번째 와인을 마시고 i-2번째 와인을 마시지 않은 상태에서 i-3개를 최대로 마실 수 있는 경우
     이고 이 세가지 경우의 수들 중 최대를 구하면 된다
     */
    for(i=4; i<=n; i++) {
        first = T[i-1];
        second = wine[i] + T[i-2];
        third = wine[i] + wine[i-1] + T[i-3];
        
        T[i] = MAXW((MAXW(first, second)), third);
    }
    
    printf("%d", T[n]);
    
    return 0;
}
