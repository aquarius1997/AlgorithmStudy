//
//  모의ST_홈방범서비스.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/28.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
#include <vector>
using namespace std;

int answer = 0;
vector<int> house;  //집의 위치[행+열]정보를 저장한다
int M;  //하나의 집이 지불할 수 있는 비용
int N;  //테이블 크기

void simul(int K) {
    int maxHouse = 0;   //K운영 크기로 커버할 수 있는 최대 집의 개수
    int cnt = 0;    //방범서비스 위치에 존재하는 집 수
    int dist;
    int row, col, houseR, houseC;
    
    for(row=0; row<N; row++) {
        for(col=0; col<N; col++) {
            cnt = 0;
            
            //모든 집에 대해 방법서비스 위치 안에 있는지 확인한다
            for(int i=0; i<house.size(); ){
                houseR = house[i];
                i += 1;
                houseC = house[i];
                i += 1;
                
                if(row > houseR) {
                    dist = row - houseR;
                } else {
                    dist = houseR - row;
                }
                if(col > houseC) {
                    dist += (col - houseC);
                } else {
                    dist += (houseC - col);
                }
                
                if(dist <= K-1) {   //제공 범위 안에 있는 집
                    cnt++;
                }
            }
            //end 모든 집에 대해 방법서비스 위치 안에 있는지 확인한다
            
            if(cnt > maxHouse) {
                maxHouse = cnt;
            }
        }
    }
    
    //이익을 구해서 0 이상으면 answer를 업데이트한다 + (K+1)크기에 대하여 재귀호출한다
    int rest = (maxHouse * M) - ((K * K) + ((K-1) * (K-1)));
    if(rest >= 0) {
        if(maxHouse > answer) {
            answer = maxHouse;
        }
        simul(K+1);
    } else {    //손해일 경우에도 방범서비스 구역이 테이블 크기보다 작을경우 (K+1)에 대하여 재귀호출한다
        if(K < N) {
            simul(K+1);
        }
    }

    
}



int main(void) {
    int T, t, num;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d", &N, &M);
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &num);
                if(num == 1) {
                    house.push_back(i);
                    house.push_back(j);
                }
            }
        }

        //함수 호출
        simul(1);
        //정답 출력
        printf("#%d %d\n", t, answer);
        
        
        //초기화
        answer = 0;
        house.clear();
    }
    
    return 0;
}
