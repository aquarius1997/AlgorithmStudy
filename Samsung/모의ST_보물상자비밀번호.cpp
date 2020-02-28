//
//  모의ST_보물상자비밀번호.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/06.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <stdio.h>
#include <string.h>

char tempArr[30][10];

void merging(int s1, int e1, int s2, int e2, char numbers[30][10]) {
    int p, q;   int idx = 0;
    
    p = s1; q = s2;
    
    while(p <= e1 && q <= e2) {
        if(strcmp(numbers[p], numbers[q]) > 0) {
            strcpy(tempArr[idx], numbers[p]);
            idx++;  p++;
        } else {
            strcpy(tempArr[idx], numbers[q]);
            idx++;  q++;
        }
    }
    
    while(p <= e1) {
        strcpy(tempArr[idx], numbers[p]);
        idx++;  p++;
    }
    while(q <= e2) {
        strcpy(tempArr[idx], numbers[q]);
        idx++;  q++;
    }
    
    for(int i=0; i<idx; i++) {
        strcpy(numbers[s1+i], tempArr[i]);
    }
}

void merge_sort(int start, int end, char numbers[30][10]) {
    int mid;
    
    if(start < end) {
        mid = (start + end) / 2;
        merge_sort(start, mid, numbers);
        merge_sort(mid+1, end, numbers);
        merging(start, mid, mid+1, end, numbers);
    }
}

int main(void) {
    char input[30];
    char numbers[30][10];
    char isSame[10];
    int numLen;
    int numIdx = 0;
    int cnt = 0;    int kCnt, flag;
    long answer = 0;
    int sixteen = 1;

    int t, T, N, K;

    scanf("%d", &T);

    for(t = 1; t <= T; t++) {
        scanf("%d %d", &N, &K);
        scanf("%s",input);
    
        numLen = N / 4;
        cnt = numIdx = 0;
        
        for(int k=0; k<(numLen); k++) {
            //numbers배열에 숫자를 나눠 저장
            for(int i=0; i<N; i++) {
                if(cnt < numLen) {
                    numbers[numIdx][cnt] = input[i];
                }
                cnt++;
                if(cnt == numLen) {
                    numbers[numIdx][cnt] = '\0'; //문자열로 만들어주고
                    cnt = 0;
                    numIdx++;
                }
            }
            
            //rotate
            for(int i=N-1; i>=0; i--) {
                input[i+1] = input[i];
            }
            input[0] = input[N];
            input[N] = '\0';
        }

        //numbers 문자열 정렬
        merge_sort(0, numIdx-1, numbers);
        
        //1개는 이미 세고
        for(int i=0; i<numLen; i++) {
            isSame[i] = numbers[0][i];
        }
        kCnt = 1;
        for(int i=1; i<numIdx; i++) {
            flag = 0;
            if(kCnt == K) {
                break;
            } else {
                //같은 수인지 확인한다
                for(int j=0; j<numLen; j++) {
                    if(isSame[j] != numbers[i][j]) {    //하나라도 다르면
                        flag = 1;
                    }
                    isSame[j] = numbers[i][j];
                }
                if(flag == 1) { //다른수이면
                    kCnt++;
                }
            }
        }
        
        
        //10진수로 변환해서 출력한다
        sixteen = 1;
        answer = 0;
        for(int i=numLen-1; i>=0; i--) {
            if(isSame[i] >= '0' && isSame[i] <= '9') {
                answer = answer + (isSame[i] - '0') * sixteen;
            } else {
                answer = answer + (isSame[i] - 'A' + 10) * sixteen;
            }
            sixteen = sixteen * 16;
        }
        
        printf("#%d %ld\n", t, answer);
    }
    return 0;
}

