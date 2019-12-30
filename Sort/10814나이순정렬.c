//
//  10814나이순정렬.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/30.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int tempAge[100002] = {0, };
int tempName[100002][102] = {0, };

/*
 merge_f : age와 name 각각의 부분배열을 정렬해서 합친다
 age : 나이를 저장한 배열
 name : 이름을 저장한 배열
 s1 : 부분배열1의 시작 인덱스,
 */
void merge_f(int age[100002], char name[100002][102], int s1, int e1, int s2, int e2) {
    int p = s1;
    int q = s2;
    int idx = 0;
    
    //나이 기준으로 오름차순 정렬
    while(p <= e1 && q <= e2) {
        if(age[p] < age[q]) {
            tempAge[idx] = age[p];
            strcpy(tempName[idx], name[p]);
            idx++;
            p++;
        } else if(age[q] < age[p]) {
            tempAge[idx] = age[q];
            strcpy(tempName[idx], name[q]);
            idx++;
            q++;
        } else {    //나이가 같을 경우 이름을 가입한 순으로 정렬
            if(p < q) {    //p가 q보다 먼저 가입했으면
                tempAge[idx] = age[p];
                strcpy(tempName[idx], name[p]);
                idx++;
                p++;
            } else {    //q가 p보다 먼저 가입했으면
                tempAge[idx] = age[q];
                strcpy(tempName[idx], name[q]);
                idx++;
                q++;
            }
        }
    }   //end while(p <= e1 && q <= e2)
    
    
    while(p <= e1) {
        tempAge[idx] = age[p];
        strcpy(tempName[idx], name[p]);
        idx++;
        p++;
    }
    
    while(q <= e2) {
        tempAge[idx] = age[q];
        strcpy(tempName[idx], name[q]);
        idx++;
        q++;
    }
    
    for(int i=0; i<idx; i++) {
        age[s1+i] = tempAge[i];
        strcpy(name[s1+i], tempName[i]);
    }
}

/*
 merge_sort : age와 name에 있는 데이터들을 정렬시킬 함수
 age : 나이를 저장한 배열
 name : 이름을 저장한 배열
 start : 정렬을 시작할 인덱스
 end : 정렬할 배열의 마지막 인덱스
 */
void merge_sort(int age[100002], char name[100002][102], int start, int end) {
    int mid;
    
    if(start < end) {
        mid = (start + end) / 2;
        merge_sort(age, name, start, mid);
        merge_sort(age, name, mid+1, end);
        merge_f(age, name, start, mid, mid+1, end);
    }
}

int main(void) {
    int age[100002];    char name[100002][102];   //한 사람의 age와 name에 대한 정보는 같은 인덱스에 저장된다
    int N;
    int i;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        scanf("%d %s", &age[i], name[i]);
    }
    
    merge_sort(age, name, 0, N-1);
    
    for(i=0; i<N; i++) {
        printf("%d %s\n", age[i], name[i]);
    }
    
    return 0;
}
