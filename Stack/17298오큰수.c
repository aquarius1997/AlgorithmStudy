//
//  17298오큰수.c
//  AlgorithmGit
//
//  Created by 송혜경 on 31/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

int main(void) {
    int N;
    int arr[1000002] = {0, };
    int stack[1000002] = {0, };
    int result[1000002] = {0, };    //각 원소의 오큰수를 저장 (result[i] : arr[i]의 오큰수)
    int top = -1;
    int i, j;
    
    scanf("%d", &N);
    
    //수를 입력받는다
    for( i=0; i<N; i++ )
        scanf("%d", &arr[i]);
    
    //arr 역순으로 오큰수를 구한다
    //마지막 수의 오큰수는 없으므로 따로 구한다
    stack[++top] = arr[N-1];
    result[N-1] = -1;
    for( i=N-2; i>=0; i-- ) {
        //우선 오큰수가 없을 경우를 대비해 값을 -1로 저장한다
        result[i] = -1;
        //스택의 top부터 스택을 훑는다. 첫번째로 발견한 현재 요소(arr[i])보다 큰 수가 오큰수이다
        for( j=top; j>=0; j-- ){
            if(stack[j] > arr[i]) {
                result[i] = stack[j];
                break;
            }else {
                //현재 요소보다 스택에 들어있는 값이 작을 경우 스택에서 pop한다.
                //따라서 스택에는 늘 현재 요소보다 큰 값들만 들어있게된다
                top--;
            }
        }
        //현재 요소를 스택에 push
        stack[++top] = arr[i];
    }
    
    for( i=0; i<N-1; i++ )
        printf("%d ", result[i]);
    printf("%d", result[N-1]);
    
    return 0;
}
