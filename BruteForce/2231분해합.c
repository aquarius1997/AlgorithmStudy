//
//  2231분해합.c
//  AlgorithmGit
//
//  Created by 송혜경 on 31/08/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>
int main(void) {
    int N;  int sum;
    int div;
    int min = 987987987;
    int flag = 0;
    int i, j;   int temp;
    
    scanf("%d", &N);
    
    for( i=1; i<=N; i++ ) {
        //변수 초기화
        sum = 0;
        div = 10;
        temp = i;
        
        //i의 자리수를 변수s에 구한다
        while(1) {
            if( i/div >= 1 ) {
                div *= 10;
            }else {
                break;
            }
        }
        div /= 10;
        
        //자기자신 더하고
        sum += temp;
        //각 자리수에 해당하는 숫자를 더한다
        for( j=div; j>=1; j=j/10 ) {
            sum += (temp/j);
            temp = i%j;
        }
        
        if(sum == N){
            if(min > i){
                min = i;
                flag = 1;
            }
        }
    }
    
    
    if(flag == 1)
        printf("%d", min);
    else
        printf("0");
    
    return 0;
}
