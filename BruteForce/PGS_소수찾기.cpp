//
//  PGS_소수찾기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/19.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>
#include <math.h>

using namespace std;

int visited[10] = {0, };    //visited[i] = 0 : i번째 인덱스에 있는 값을 방문 안함
int arr[10] = {0, };
int pCnt = 0;
int isMaked[100] = {0, };   int idx = 0;

//dfs로 완전 탐색
void dfs(string numbers, int cnt) {
    int i, j;
    int num;    int flag, flag2;
    int r;
    
    
    for(i=0; i<numbers.length(); i++) {
        if(visited[i] == 0) {
            visited[i] = 1;
            arr[cnt] = numbers[i] - '0';
            
            for(j=0; j<=cnt; j++) {
                printf("%d", arr[j]);
            }
            printf("\n");
            
            //숫자변환중
            num = arr[0];
            
            for(j=1; j<=cnt; j++) {
                num *= 10;
                num += arr[j];
            }
            
            flag2 = 0;
            
            for(j=0; j<idx; j++) {
                if(num == isMaked[j]) { //이전에 만든 숫자와 동일할 경우
                    flag2 = 1;
                }
            }
            
            if(flag2 == 0) {    //이미 확인했던 수가 아닐경우
                //소수인지 확인
                flag = 0;
                for(r=2; r<=sqrt(num); r++) {
                    if(num % r == 0) {
                        flag = 1;   break;
                    }
                }
                
                if(num == 1) {
                    flag = 1;
                }
                
                //소수
                if(flag == 0) {
                    pCnt += 1;
                    
                    printf("prind l; %d\n", num);
                    isMaked[idx++] = num;
                }
            }
            
            
            if(cnt+1 < numbers.length()) {  //반복
                dfs(numbers, cnt+1);
            }
            
            visited[i] = 0;
        }
    }
}

int solution(string numbers) {
    int answer = 0;
    int i;
    
    pCnt = 0;
    for(i=0; i<10; i++) {
        visited[i] = arr[i] = 0;
    }
    
    dfs(numbers, 0);
    
    answer = pCnt;
    
    return answer;
}

int main(void) {
    dfs("011", 0);
    
    return 0;
}
