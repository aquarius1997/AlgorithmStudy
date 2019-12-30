//
//  1436영화감독숌.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/30.
//  Copyright © 2019 송혜경. All rights reserved.
// *

#include <stdio.h>

int main(void) {
    int N;
    int sixCnt = 0;   //연속된 6의 갯수를 셀 때 사용하는 변수
    int cnt = 0;
    int num, tempNum;
    int i;
    
    scanf("%d", &N);
    
    for(i=1; ; i++) {
        sixCnt = 0;
        
        //일의 숫자부터 마지막까지 확인 -> i가 123이라면 3, 2, 1 순으로 숫자가 6인지 확인
        num = i;
        while(1) {
            tempNum = num % 10;
            if(tempNum == 6) {  //num의 일의 자리 수가 6이면
                sixCnt++;
            } else {    //숫자가 6이 아니면 다시 연속된 6의 개수를 0으로 초기화한다
                sixCnt = 0;
            }
            
            if(sixCnt >= 3) {   //6이 세개 이상 연속될 경우 cnt를 +1하고 더이상 확인할 필요없으므로 나간다
                cnt++;
                break;
            }
            
            if(num < 10) {  //더 이상 확인할 숫자가 없으면 나가기
                break;
            }
            num = num / 10;
        }   //end while(1)
        
        
        if(cnt == N) {  //구하고자 하는 6이 세개 이상 연속하는 N번째 숫자를 찾으면 출력하고 for문 나가기
            printf("%d", i);
            break;
        }
    }   //end for(i);
    
    return 0;
}
