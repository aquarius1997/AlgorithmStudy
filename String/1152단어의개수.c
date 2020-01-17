//
//  1152단어의개수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 25/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    char str[1000010];
    int start_idx, end_idx;
    int len;    int count = 0;
    int i;
    
    //scanf말고 fgets사용
    fgets(str, 1000010, stdin);
    
    //fgets으로 받은 문자열은 마지막에 \n 캐릭터가 같이 들어옴을 유의
    len = (int)strlen(str);
    
    //문자열 시작과 마지막에 공백이 있는지 먼저 확인해서 시작 index, 끝 index를 구한다
    if(str[0] == ' ')
        start_idx = 1;
    else
        start_idx = 0;
    
    if(str[len-2] == ' ')
        end_idx = len-3;
    else
        end_idx = len-2;
    
    //시작index ~ 끝 index까지 단어를 체크하며 개수를 count한다
    for(i = start_idx; i<=end_idx; i++) {
        if(str[i] == ' ')
            count++;
    }
    
    //공백+엔터 일경우 예외처리
    if(str[end_idx] != ' ' && end_idx >= 0)
        count++;
    
    printf("%d", count);
    
    return 0;
}
