//
//  2908상수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/26.
//  Copyright © 2019 송혜경. All rights reserved.
// *

#include <stdio.h>

int main(void) {
    char A[4];
    char B[4];
    char biggerN[4];
    int i, j;
    
    scanf("%s", A);
    scanf("%s", B);

    
    for(i=2; i>=0; i--) {
        if((A[i] - '0') == (B[i] - '0')) {  //둘이 같으면 다음 자릿수 비교
            continue;
        } else if((A[i] - '0') > (B[i] - '0')) {    //A가 더 크면
            for(j=2; j>=0; j--) {   //더 큰수는 A이므로 biggerN에 저장
                biggerN[2-j] = A[j];
            }
            break;
        } else {
            for(j=2; j>=0; j--) {   //더 큰수는 B이므로 biggerN에 저장
                biggerN[2-j] = B[j];
            }
            break;
        }
    }
    biggerN[3] = '\0';
    
    printf("%s", biggerN);
    
    return 0;
}
