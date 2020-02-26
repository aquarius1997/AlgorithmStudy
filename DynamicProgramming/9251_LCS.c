//
//  9251_LCS.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/25.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <stdio.h>
#include <string.h>
#define MAXN(a, b)  (((a) > (b)) ? (a) : (b))

int main(void) {
    char str1[1010];
    char str2[1010];
    int T[1010][1010] = {0, };
    int str1Len, str2Len;
    int i, j;
        
    scanf("%s", str1);
    scanf("%s", str2);
    
    str1Len = strlen(str1);
    str2Len = strlen(str2);
    
    for(i=0; i<str2Len; i++) {
        for(j=0; j<str1Len; j++) {
            if(str2[i] != str1[j]) {    //다른문자면
                T[i+1][j+1] = MAXN(T[i][j+1], T[i+1][j]);
            } else {    //이 부분 코드 잘못짰었음
                T[i+1][j+1] = T[i][j] + 1;
            }
        }
    }
    
    for(i=0; i<=str2Len; i++) {
        for(j=0; j<=str1Len; j++) {
            printf("%3d", T[i][j]);
        }
        printf("\n");
    }
    printf("%d", T[str2Len][str1Len]);

    
    return 0;
}
