//
//  15650N과M_2.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/02.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

int arr[9] = {0, }; //수열을 저장할 배열
int visited[9] = {0, }; //방문 여부를 저장할 배열

/*
 arr[0] < arr[1] < arr[2] < ...  의 성질을 띈다는 것을 활용한다
 N : 입력으로 주어진 N
 M : 입력으로 주어진 M
 idx : 함수 호출로 인해 arr배열에 수열의 정보를 저장할 때, 저장하는 인덱스의 위치를 가리킨다
 */

void make_sequence(int N, int M, int idx) {
    int i;
    int num;    //arr[idx-1]의 값
    
    if(idx == M) {  //수열 만들었으면 출력
        for(i=0; i<idx; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        if(idx == 0) {  //수열의첫번째 숫자이면
            for(i=1; i<=N; i++) {
                visited[i] = 1;
                arr[idx] = i;
                make_sequence(N, M, idx+1);
                visited[i] = 0;
            }
        } else {    //수열의 첫번째 숫자가 아니면
            num = arr[idx-1];   //이전에 저장된 가장 큰 수를 알아내서
            for(i=num+1; i<=N; i++) {   //그거보다 큰 수를 저장할 수 있을 때만 수열정보 저장 + 재귀호출
                visited[i] = 1;
                arr[idx] = i;
                make_sequence(N, M, idx+1);
                visited[i] = 0;
            }
        }
    }
}


int main(void) {
    int N, M;
    
    scanf("%d %d", &N, &M);
    
    make_sequence(N, M, 0);
    
    return 0;
}
