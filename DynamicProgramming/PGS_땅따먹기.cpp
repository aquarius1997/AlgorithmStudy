//
//  PGS_땅따먹기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/01.
//  Copyright © 2020 송혜경. All rights reserved.
//  **

#include <iostream>
#include <vector>
#define MAXN(a, b)  (((a) >= (b)) ? (a) : (b))

using namespace std;

int solution(vector<vector<int> > land)
{
    int T[100002][4] = {0, };
    int n = land.size();
    int answer = 0;
    int i;

    //base-case
    T[0][0] = land[0][0];
    T[0][1] = land[0][1];
    T[0][2] = land[0][2];
    T[0][3] = land[0][3];
    
    //induction step
    for(i=1; i<n; i++) {
        T[i][0] = land[i][0] + MAXN(T[i-1][1], (MAXN(T[i-1][2], T[i-1][3])));
        T[i][1] = land[i][1] + MAXN(T[i-1][0], (MAXN(T[i-1][2], T[i-1][3])));
        T[i][2] = land[i][2] + MAXN(T[i-1][0], (MAXN(T[i-1][1], T[i-1][3])));
        T[i][3] = land[i][3] + MAXN(T[i-1][0], (MAXN(T[i-1][1], T[i-1][2])));
    }
    
    answer = MAXN(T[n-1][0], (MAXN(T[n-1][1], (MAXN(T[n-1][2], T[n-1][3])))));

    return answer;
}
