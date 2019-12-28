//
//  11720숫자의합.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/26.
//  Copyright © 2019 송혜경. All rights reserved.
// *

#include <stdio.h>
#include <string.h>

int main(void) {
    int N;
    char inputStr[102];
    int result = 0;
    int i;
    
    scanf("%d", &N);
    scanf("%s", inputStr);
    
    for(i=0; i<N; i++) {    //각 자리수를 더함
        result += (inputStr[i] - '0');
    }
    
    printf("%d", result);
    
    return 0;
}
