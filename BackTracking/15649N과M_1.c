//
//  15649N과M_1.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/02.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>
int arr[9] = {0, }; //수열을 만들때 사용하는 배열
int visited[9] = {0, }; //수열을 만들때 사용하는 숫자가 중복되지 않도록 사용 여부를 저장한다
/*
 N : 입력 N
 M : 입력 M
 idx : 함수가 호출되면 idx에 해당하는 인덱스에 수열의 정보를 저장한다
 */
void make_sequence(int N, int M, int idx) {
    int i;
    
    if(idx == M) {  //M개의 숫자로 수열을 만들었으면 출력하고 종료
        for(i=0; i<idx; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        for(i=1; i<=N; i++) {
            if(visited[i] == 0) {   //아직 수열에 해당 숫자가 포함되지 않았으면
                visited[i] = 1; //사용함 표시
                arr[idx] = i;   //숫자 저장
                make_sequence(N, M, idx+1); //다음 인덱스에 대해 재귀호출
                visited[i] = 0; //미사용으로 표시 -> 다음 수열에서 사용할 수 있도록
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
