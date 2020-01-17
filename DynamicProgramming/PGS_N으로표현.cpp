//
//  P_N으로표현.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/10/31.
//  Copyright © 2019 송혜경. All rights reserved.
//

// !! 프로그래머스에는 DP문제로 나와있으나, DP로 어떻게 풀 지 생각이 안나므로... DFS를 활용해 완전탐색함

#include <cstdio>
#define MAXN    32000

using namespace std;
int minN = 987987987;
int flag = 0;

//num : dfs함수에서 만들어서 넘기는 숫자
void dfs(int N, int number, int cnt, int num) {
    int temp;
    
    if(num == number) { //8회 안에 원하는 숫자를 만든 경우
        if(minN > cnt) {
            minN = cnt;
            flag = 1;
        }
    }
    if(cnt > 8) {  //8번으로 원하는 숫자를 만들지 못한 경우
        return;
    }
    
    //dfs 함수 호출을 통한 숫자 만들기 반복
    temp = N;
    
    //N, NN, NNN, ...에 대하여 DFS를 통한 사칙연산 수행
    for(int i=0; i<8-cnt; i++) {
    
        dfs(N, number, cnt+(i+1), num+temp);
        dfs(N, number, cnt+(i+1), num-temp);
        dfs(N, number, cnt+(i+1), num*temp);
        dfs(N, number, cnt+(i+1), num/temp);
        
        temp = (temp*10) + N;
    }
}

int solution(int N, int number) {
    int answer = 0;
    int temp = N;
    
    dfs(N, number, 0, 0);
    
    if(flag == 0) {
        answer = -1;
    }else {
        answer = minN;
    }
    
    return answer;
}

int main(void) {
    printf("%d\n", solution(5, 12));
    
    return 0;
}
