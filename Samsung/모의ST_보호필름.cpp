//
//  모의ST_보호필름.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/03.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
using namespace std;

int D, W, K;
int film[15][22] = {0, };
int answer = -1;
int inject[15]; //A : 0, B : 1, X : -1

/// injectCnt만큼 약품을 주입시킨다. DFS 방식으로 모든 경우의 수를 알아낸다
/// @param injectCnt 총 주입시킨 약품 수
/// @param cnt 현재까지 주입시킨 약품수
/// @param idx DFS 를 위한 인덱스 변수
void injection(int injectCnt, int cnt, int idx) {
    int aOrb = 0;   //a : 0, b : 1
    int abCnt = 0;
    int noFlag = 0; //합격기준 만족 못할 경우
    int i, j;
    
    if(cnt == injectCnt) {  //약품 개수를 injectCnt만큼 주입했으면 테스트를 통과할수 있는지 알아낸다
        for(j=0; j<W; j++) {
            noFlag = 0;
            if(inject[0] == -1) {
                aOrb = film[0][j];  //첫번재 필름으로 초기화
            } else {
                aOrb = inject[0];
            }
            abCnt = 1;
            for(i=1; i<D; i++) {
                if(inject[i] == -1) {
                    if(aOrb == film[i][j]) {
                        abCnt++;
                    } else {
                        abCnt = 1;
                        aOrb = film[i][j];
                    }
                } else {
                    if(aOrb == inject[i]) {
                        abCnt++;
                    } else {
                        abCnt = 1;
                        aOrb = inject[i];
                    }
                }
                if(abCnt >= K) {    //합격기준 만족하는 열이면
                    noFlag = 1;
                    break;
                }
            }
            if(noFlag == 0) {   //모든 합격기준 만족 못하면
                break;
            }
        }
        if(noFlag == 1) {   //합격기준을 모두 만족하면 답을 업데이트한다
            answer = injectCnt;
        }
        
    } else {    //재귀호출을 통해 DFS방식으로 약품 주입
        for(i=idx; i<D; i++) {
            if(answer == -1) {
                inject[i] = 0;
                injection(injectCnt, cnt+1, i+1);
                
                inject[i] = 1;
                injection(injectCnt, cnt+1, i+1);
                
                inject[i] = -1;
            } else {
                break;
            }
        }
    }
}

/// 약품을 injectCnt 만큼 주입해, 테스트를 통과시킬 수 있을지 확인하고, 통과 못할경우 재귀호출한다
/// @param injectCnt 주입시킬 약품 수
void simul(int injectCnt) {
    int i;
    
    for(i=0; i<D; i++) {    //일단 주입 아무것도 안된걸로 초기화
        inject[i] = -1;
    }
    //함수호출을 통해 injectCnt만큼 약품을 주입시키고, 테스트를 통과하는지 알아낸다
    injection(injectCnt, 0, 0);
    
    //테스트를 통과하지 못했을 경우 재귀호출
    if(answer == -1) {
        simul(injectCnt+1);
    }
    
}

int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);

    for(t=1; t<=T; t++) {
        scanf("%d %d %d", &D, &W, &K);

        for(i=0; i<D; i++) {
            for(j=0; j<W; j++) {
                scanf("%d", &film[i][j]);   //A : 0, B : 1
            }
        }
        
        //함수호출
        simul(0);
                
        //답
        printf("#%d %d\n", t, answer);

        //초기화
        answer = -1;
    }
    

    
    return 0;
}

