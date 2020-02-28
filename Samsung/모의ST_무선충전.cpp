//
//  모의ST_무선충전.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/25.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** (처음에 문제 완전 잘못이해함)

#include <cstdio>
#include <queue>
#include <vector>
#define MAXN(a, b)  (((a) > (b)) ? (a) : (b))
using namespace std;

int aRow, aCol, bRow, bCol; //A, B의 위치 저장
int bcValue[10] = {0, };    //bcValue[i] : i번째 BC의 성능을 저장
int aDir[102] = {0, };  int bDir[102] = {0, };  //A와 B의 이동방향
int M;  //총 이동시간
int A;  //BC개수
int total;  //총 충전한 값

void simul(int timeCnt, queue<int> bc) {
    int aBC1, aBC2, bBC1, bBC2; //A와 B의 위치에 따른 BC번호를 저장
    int bcNum, row, col, c, aDist, bDist;
    queue<int> tempBc;  //원래 bc정보 저장
    vector<int> aBCs, bBCs;  //a와 B가 속하는BC 구역들
    int maxA, maxB;
    
    if(timeCnt > M) {   //종료
        return;
    } else {    //재귀함수 호출
        aBC1 = aBC2 = bBC1 = bBC2 = 0;  //초기화
        maxA = maxB = 0;
        bcNum = 1;
        while(!bc.empty()) {    //A와 B가 속한 BC 구역 확인
            row = bc.front();   bc.pop();   tempBc.push(row);
            col = bc.front();   bc.pop();   tempBc.push(col);
            c = bc.front(); bc.pop();   tempBc.push(c);
            //A와 해당 BC간 거리 구하기
            if(row - aRow > 0) {
                aDist = row - aRow;
            } else {
                aDist = aRow - row;
            }
            if(col - aCol > 0) {
                aDist += (col - aCol);
            } else {
                aDist += (aCol - col);
            }
            //B와 해당 BC간 거리 구하기
            if(row - bRow > 0) {
                bDist = row - bRow;
            } else {
                bDist = bRow - row;
            }
            if(col - bCol > 0) {
                bDist += (col - bCol);
            } else {
                bDist += (bCol - col);
            }
            
            if(c >= aDist) {
                aBCs.push_back(bcNum);
                if(bcValue[bcNum] > bcValue[maxA]) { //가장 큰 BC
                    maxA = bcNum;
                }
            }
            if(c >= bDist) {
                bBCs.push_back(bcNum);
                if(bcValue[bcNum] > bcValue[maxB]) {
                    maxB = bcNum;
                }
            }
            
            bcNum += 1;
        }   //end A,B가 속한 BC 구역 확인
        
        if(aBCs.size() == 0 && bBCs.size() == 0) {  //둘다 BC구역 안에 없으면
            total += 0;
        } else if(aBCs.size() == 0) {   //B만 BC구역 안에 있으면
            total += bcValue[maxB];
        } else if(bBCs.size() == 0) {   //A만 BC구역 안에 있으면
            total += bcValue[maxA];
        } else {    //둘다 BC구역 안에 있으면
            if(maxA == maxB) {  //둘의 최대가 동일한 BC면
                if(aBCs.size() == 1 && bBCs.size() == 1) {
                    total += bcValue[maxA];
                } else {    //둘중 한명이라도 여러 BC구역에 있으면
                    int aNextMax, bNextMax;
                    aNextMax = bNextMax = 0;
                    for(int j=0; j<aBCs.size(); j++) {  //두번째로 큰 B의 BC찾기
                        if(bcValue[aBCs[j]] > bcValue[aNextMax]) {
                            if(aBCs[j] != maxA) {
                                aNextMax = aBCs[j];
                            }
                        }
                    }
                    for(int j=0; j<bBCs.size(); j++) {  //두번째로 큰 B의 BC찾기
                        if(bcValue[bBCs[j]] > bcValue[bNextMax]) {
                            if(bBCs[j] != maxB) {
                                bNextMax = bBCs[j];
                            }
                        }
                    }
                    
                    if(bcValue[aNextMax] > bcValue[bNextMax]) {
                        total += (bcValue[maxB] + bcValue[aNextMax]);
                    } else {
                        total += (bcValue[maxA] + bcValue[bNextMax]);
                    }
                }
            } else {
                total += (bcValue[maxA] + bcValue[maxB]);
            }
        }
        
        //A와 B의 위치 재조정하기
        if(aDir[timeCnt] == 0) {
        } else if(aDir[timeCnt] == 1) {
            aRow -= 1;
        } else if(aDir[timeCnt] == 2) {
            aCol += 1;
        } else if(aDir[timeCnt] == 3) {
            aRow += 1;
        } else {
            aCol -= 1;
        }
        if(bDir[timeCnt] == 0) {
        } else if(bDir[timeCnt] == 1) {
            bRow -= 1;
        } else if(bDir[timeCnt] == 2) {
            bCol += 1;
        } else if(bDir[timeCnt] == 3) {
            bRow += 1;
        } else {
            bCol -= 1;
        }
        //end - A와 B의 위치 재조정하기
        simul(timeCnt+1, tempBc);
    }   //end 재귀함수호출
}


int main(void) {
    int T, t, row, col, C, P;
    int i;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d", &M, &A);
        
        //초기화
        aRow = aCol = 1;
        bRow = bCol = 10;
        total = 0;
        for(i=0; i<10; i++) {
            bcValue[i] = 0;
        }
        for(i=0; i<102; i++) {
            aDir[i] = bDir[i] = 0;
        }
        
        queue<int> bc; //BC의 좌표를 저장
        for(i=0; i<M; i++) {
            scanf("%d", &aDir[i]);
        }
        for(i=0; i<M; i++) {
            scanf("%d", &bDir[i]);
        }
        for(i=1; i<=A; i++){    //BC의 정보를 입력받아서 저장
            scanf("%d %d %d %d", &col, &row, &C, &P);
            bc.push(row);  bc.push(col);  bc.push(C);
            bcValue[i] = P;
        }
        
        //함수호출
        simul(0, bc);
        
        printf("#%d %d\n", t, total);
    }
    
    return 0;
}
