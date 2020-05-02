//
//  모의ST_보호필름.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/28.
//  Copyright © 2020 송혜경. All rights reserved.
//  43min. Fail : 0 ****

#include <cstdio>
using namespace std;

int g_D = 0;
int g_W = 0;
int g_K = 0;
int g_film[15][22] = {0,};
int g_tempFilm[15][22] = {0,};
int g_inject[15] = {0,};    //약품 투입 정보, 해당 행에 약품주입 안하면 -1, A : 0, B : 1
int g_flag = 0; //테스트 통과시 1로 저장

void testing(int injectCnt, int idx, int cnt) {
    int i, j;
    int testCnt = 0;
    int colFlag = 0;    //해당 열 테스트 통과 할경우 1
    int aOrB;
    
    if(injectCnt == cnt) {  //주입시킬양을 모두 채우면 테스트를 통과하는지 확인한다
        //약품을 주입한다
        for(i=0; i<g_D; i++) {
            if(g_inject[i] == -1) { //약품없음
                for(j=0; j<g_W; j++) {
                    g_tempFilm[i][j] = g_film[i][j];
                }
            } else if(g_inject[i] == 0) {   //A
                for(j=0; j<g_W; j++) {
                    g_tempFilm[i][j] = 0;
                }
            } else {    //B
                for(j=0; j<g_W; j++) {
                    g_tempFilm[i][j] = 1;
                }
            }
        } //end 약품 주입
       
        //테스트실행
        for(j=0; j<g_W; j++) {
            //해당 열이 K개만큼 연속되는지 확인
            testCnt = 1;
            aOrB = g_tempFilm[0][j];
            for(i=1; i<g_D; i++) {
                if(aOrB == g_tempFilm[i][j]) {  //같은 약물 인접
                    testCnt++;
                } else {    //다른 약물일 경우
                    aOrB = g_tempFilm[i][j];    //약물변경
                    testCnt = 1;
                }
                if(testCnt == g_K) {    //테스트 통과
                    colFlag = 1;    break;
                }
            } //end for(i)
            if(colFlag != 1) {  //j번째 열에대해 통과 못하면 다음 살펴볼 필요 없음
                break;
            } else {
                colFlag = 0;
                if(j == g_W - 1) {  //모든 열에 대해 테스트 통과했을 경우
                    g_flag = 1;
                }
            }
        }//테스트실행
        
        return;
    } //주입시킬양을 모두 채우면 테스트를 통과하는지 확인한다
    
    if(idx < g_D) {
        //주입 안함
        g_inject[idx] = -1;
        testing(injectCnt, idx+1, cnt);
        if(g_flag == 1) { return;}
        
        //A주입
        g_inject[idx] = 0;
        testing(injectCnt, idx+1, cnt+1);
        if(g_flag == 1) { return;}

        //B주입
        g_inject[idx] = 1;
        testing(injectCnt, idx+1, cnt+1);
        if(g_flag == 1) { return;}

        
        //주입안함으로 초기화
        g_inject[idx] = -1;
    }
}

int simul(void) {
    int injectCnt = 0;
    
    //주입 수를 증가시키며 테스트를 통과하는지 확인한다. 통과하면 종료
    while(1) {
        testing(injectCnt, 0, 0);
        
        if(g_flag == 1) {   //테스트 통과
            break;
        }
        
        injectCnt++;
    } //주입 수를 증가시키며 테스트를 통과하는지 확인한다. 통과하면 종료
    
    //최소 주입 수를 리턴
    return injectCnt;
}

int main(void) {
    int t, T;
    int i, j;
    int minInject = 0;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //초기화
        for(i=0; i<15; i++) {
            g_inject[i] = -1;
        }
        g_flag = 0;
        
        //입력
        scanf("%d %d %d", &g_D, &g_W, &g_K);
        for(i=0; i<g_D; i++) {
            for(j=0; j<g_W; j++) {
                scanf("%d", &g_film[i][j]);
                g_tempFilm[i][j] = g_film[i][j];
            }
        }
        
        //시뮬레이션 호출
        minInject = simul();
        
        //정답 출력
        printf("#%d %d\n", t, minInject);
        
    }
    
    return 0;
}


