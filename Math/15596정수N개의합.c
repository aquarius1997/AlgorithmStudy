//
//  15596정수N개의합.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/26.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

//입력으로 n개의 요소를 가진 a 배열이 들어온다.
//a배열의 합계를 구해 리턴
long long sum(int *a, int n) {
    long long answer = 0;
    int i;
    
    for(i=0; i<n; i++) {
        answer += a[i];
    }
    
    return answer;
}
