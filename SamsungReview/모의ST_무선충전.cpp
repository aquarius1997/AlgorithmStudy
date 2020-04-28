//
//  모의ST_무선충전.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/17.
//  Copyright © 2020 송혜경. All rights reserved.
// 2H ***** 두번째로 큰 값을 저장할때 문제있었음. 이거 꼭 다시 복습하기

#include <cstdio>
#include <vector>
using namespace std;

typedef struct BC {
    int row;
    int col;
    int C;  //충전범위
    int P;  //처리량
}BC;

vector<BC> g_bcs;   //bc들을 저장
int g_person1Move[102] = {0, }; //첫번째 사람의 이동 방향
int g_person2Move[102] = {0, }; //두번재 사람의 이동 방향
int g_totalCnt = 0; //정답 저장

/// 사람들을 이동시키며 최대로 충전할 수 있는 양을 구한다
/// @param M 총 이동시간
void get_max_charge(int M) {
    int per1bc[2] = {0, };  //사람1이 BC 구역에 속한다면 처리량의 내림차순으로 BC 번호를 저장한다
    int per2bc[2] = {0, };  //사람2가 BC구역에 속한다면 처리량의 내림차순으로 BC 번호를 저장한다
    int bcNum = 0;  int bcNum2 = 0;
    int per1row = 1;
    int per1col = 1;
    int per2row = 10;
    int per2col = 10;
    int rowDist, colDist, dist;
    int totalCnt = 0;   //정답을 누적한다(최대 충전량)
    int temp = 0;
    int timeCnt = 0;    //소요시간
    int i;
    
    while(1) {
        //per1bc, per2bc를 일단 없는 거로 저장
        for(i=0; i<2; i++) {
            per1bc[i] = per2bc[i] = -1;
        }
        
        for(i=0; i<g_bcs.size(); i++) { //사람1의 BC구역들을 구한다
            rowDist = g_bcs[i].row - per1row;
            colDist = g_bcs[i].col - per1col;
            if(rowDist < 0) { rowDist *= -1; }
            if(colDist < 0) { colDist *= -1; }
            dist = rowDist + colDist;   //BC구역에 속하는지 확인하기 위해 거리 구한다
            if(dist <= g_bcs[i].C) { //충전범위에 속하면
                bcNum = per1bc[0];
                if(bcNum == -1) {   //첫번째 최대 BC인 경우
                    per1bc[0] = i;
                } else {
                    if(g_bcs[bcNum].P < g_bcs[i].P) {    //최대 BC처리량이면
                        per1bc[0] = i;
                        //기존 가장 큰 값을 두번째로 옮긴다
                        if(per1bc[1] == -1) {
                            per1bc[1] = bcNum;
                        } else {
                            if(g_bcs[(per1bc[1])].P < g_bcs[bcNum].P) {
                                per1bc[1] = bcNum;
                            }
                        }
                    } else {    //second best BC 처리량이면
                        bcNum2 = per1bc[1];
                        if(bcNum2 == -1) {
                            per1bc[1] = i;
                        } else {
                            if(g_bcs[bcNum2].P < g_bcs[i].P) {
                                per1bc[1] = i;
                            }
                        }
                    }
                }
            }   //충전범위에 속하면
        }   //end 사람1의 BC 구역들을 구한다
        for(i=0; i<g_bcs.size(); i++) { //사람2의 BC구역들을 구한다
            rowDist = g_bcs[i].row - per2row;
            colDist = g_bcs[i].col - per2col;
            if(rowDist < 0) { rowDist *= -1; }
            if(colDist < 0) { colDist *= -1; }
            dist = rowDist + colDist;   //BC구역에 속하는지 확인하기 위해 거리 구한다
            if(dist <= g_bcs[i].C) { //충전범위에 속하면
                bcNum = per2bc[0];
                if(bcNum == -1) {   //첫번째 최대 BC인 경우
                    per2bc[0] = i;
                } else {
                    if(g_bcs[bcNum].P < g_bcs[i].P) {    //최대 BC처리량이면
                        per2bc[0] = i;
                        //기존 가장 큰 값을 두번째로 옮긴다
                        if(per2bc[1] == -1) {
                            per2bc[1] = bcNum;
                        } else {
                            if(g_bcs[(per2bc[1])].P < g_bcs[bcNum].P) {
                                per2bc[1] = bcNum;
                            }
                        }
                    } else {    //second best BC 처리량이면
                        bcNum2 = per2bc[1];
                        if(bcNum2 == -1) {
                            per2bc[1] = i;
                        } else {
                            if(g_bcs[bcNum2].P < g_bcs[i].P) {
                                per2bc[1] = i;
                            }
                        }
                    }
                }
            }   //충전범위에 속하면
        }//end 사람2의 BC구역들을 구한다

        
        //둘의 최대 충전량을 구해서 누적
        if(per1bc[0] == -1) {   //사람1은 속한 BC구역이 없을 경우
            if(per2bc[0] != -1) {   //사람2는 속한 BC구역이 있을 경우
                bcNum = per2bc[0];
                totalCnt += g_bcs[bcNum].P;
            }
        } else {    //사람1이 속한 BC구역이 있을 경우
            if(per2bc[0] == -1) {   //사람2는 속한 BC구역이 없을 경우
                bcNum = per1bc[0];
                totalCnt += g_bcs[bcNum].P;
            } else { //사람2도 속한 BC 구역이 잇을 경유
                //둘의 BC가 동일한지 확인
                if(per1bc[0] == per2bc[0]) {    //동일한 BC가 둘의 최대일 경우
                    bcNum = per1bc[0];
                    temp =  g_bcs[bcNum].P; //일단 동일한 BC를 나눠가질경우로 초기화
                    if(per1bc[1] != -1) {   //사람1이 다른 BC구역에도 속할 경우
                        if(g_bcs[(per1bc[1])].P + g_bcs[(per2bc[0])].P > temp) {    //사람1의 두번째로 큰 BC와 사람2의 가장 큰 BC를 더해서 최댓값인지 확인
                            temp = g_bcs[(per1bc[1])].P + g_bcs[(per2bc[0])].P;
                        }
                    }
                    if(per2bc[1] != -1) {
                        if(g_bcs[(per1bc[0])].P + g_bcs[(per2bc[1])].P > temp) { //사람1의 가장 큰 BC와 사람2의 두번째로 큰 BC를 더해서 최댓값인지 확인
                            temp = g_bcs[(per1bc[0])].P + g_bcs[(per2bc[1])].P;
                        }
                    }
                    totalCnt += temp;   //최대값으로 누적
                } else {    //둘이 서로 다른 BC가 최대일 경우
                    totalCnt += (g_bcs[(per1bc[0])].P + g_bcs[(per2bc[0])].P);
                }
            }
        }
        //end 둘의 최대 충전량을 구해서 누적
        
        //사람들을 이동시킨다
        if(g_person1Move[timeCnt] == 1) { per1row -= 1; }
        else if(g_person1Move[timeCnt] == 2) { per1col += 1; }
        else if(g_person1Move[timeCnt] == 3) { per1row += 1; }
        else if(g_person1Move[timeCnt] == 4) { per1col -= 1; }
        else {}
        
        if(g_person2Move[timeCnt] == 1) { per2row -= 1; }
        else if(g_person2Move[timeCnt] == 2) { per2col += 1; }
        else if(g_person2Move[timeCnt] == 3) { per2row += 1; }
        else if(g_person2Move[timeCnt] == 4) { per2col -= 1; }
        else {}
        //end 사람들을 이동시킨다

        if(timeCnt == M) {  //종료
            g_totalCnt = totalCnt;
            break;
        } else {
            timeCnt += 1;
        }
    }
    //end while(1)
}

int main(void) {
    int T, t;
    int x, y, c, p;
    int M = 0;  //이동시간
    int A = 0;  //BC개수
    int i;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d %d", &M, &A);
        for(i=0; i<M; i++) {    //첫번째 사람의 이동방향을 입력받는다
            scanf("%d", &g_person1Move[i]);
        }
        for(i=0; i<M; i++) {    //두번째 사람의 이동방향을 입력받는다
            scanf("%d", &g_person2Move[i]);
        }
        //BC 정보를 입력받는다
        for(i=1; i<=A; i++) {
            scanf("%d %d %d %d", &x, &y, &c, &p);
            BC newBc;
            newBc.row = y;
            newBc.col = x;
            newBc.C = c;
            newBc.P = p;
            g_bcs.push_back(newBc);
        }
        
        //시뮬레이션 실행
        get_max_charge(M);
        
        //정답출력
        printf("#%d %d\n", t, g_totalCnt);
        
        //초기화
        g_totalCnt = 0;
        g_bcs.clear();
        for(i=0; i<102; i++) {
            g_person1Move[i] = g_person2Move[i] = 0;
        }
        
    }
    
    
    return 0;
}
