//
//  14889_스타트와링크.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/19.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int N;
int team[22] = {0, };   //1과 0팀으로 나눈다
int visited[22] = {0, };    //방문시 1
int S[22][22] = {0, };  //능력치 저장
int minN = 987987987;

/// 팀0과 팀1의 능력치를 구해, 최소값을 없데이트 할 수 있는지 확인한다
void calculate_diff(void) {
    int team0Sum, team1Sum;
    
    team0Sum = team1Sum = 0;
    
    //0번팀의 능력치 구하기
    int temp = 0;   //쌍을 찾기 위해
    for(int i=1; i<=N; i++) {
        if(visited[i] == 0) {
            for(int j=i+1; j<=N; j++) {
                if(visited[j] == 0) {
                    team0Sum += (S[i][j] + S[j][i]);
                }
            }
        }
    }
    //1번팀의 능력치구하기
    temp = 0;
    for(int i=1; i<=N; i++) {
        if(visited[i] == 1) {
            for(int j=i+1; j<=N; j++) {
                if(visited[j] == 1) {
                    team1Sum += (S[i][j] + S[j][i]);
                }
            }
        }
    }
    
    //둘 차이의 최소를 구한다
    if(team1Sum > team0Sum) {
        if(minN > (team1Sum - team0Sum)) {
            minN = team1Sum - team0Sum;
        }
    } else {
        if(minN > (team0Sum - team1Sum)) {
            minN = team0Sum - team1Sum;
        }
    }
}

/// 팀을 0팀과 1팀으로 나눈다. DFS탐색을 통해 수행되고 방문 여부가 1인 것이 팀 1이 된다
/// @param cnt 팀 1에 포함된 사람의 수
/// @param idx 팀 1에 포함시킬 수 있는지 확인할 사람의 인덱스
void make_team(int cnt, int idx) {
    if(cnt == (N/2)) {
        
        calculate_diff();    //둘의 능력치합을 구해 최소값 업데이트

    } else {
        if(visited[idx] == 0 && idx <= N) {
            visited[idx] = 1;
            team[idx] = 1;
            make_team(cnt+1, idx+1);
            visited[idx] = 0;
            team[idx] = 0;
        }
        for(int i=idx+1; i<=N; i++) {
            if(visited[i] == 0) {
                visited[i] = 1;
                team[i] = 1;
                make_team(cnt+1, i+1);
                visited[i] = 0;
                team[i] = 0;
            }
        }
    }
}


int main(void) {
    scanf("%d", &N);
    
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            scanf("%d", &S[i][j]);
        }
    }
        
    make_team(0, 1);
    
    printf("%d", minN);
    
    return 0;
}
