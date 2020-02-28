//
//  모의ST_점심식사시간.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/27.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <cstdio>
#include <vector>
using namespace std;

int pStair[11] = {0, }; //pStart[i] = j -> (i+1)번째 사람은 j계단으로 이동할 예정
int stair[3][2] = {0, };    //stair[1][0] : 1번계단 행정보, [1][1] : 1번계단 열정보
vector<int> locate; //사람들의 위치 정보 저장
vector<int> stair1; //첫번째 계단으로 도착해서 이동하는(+이동완료한) 사람 정보 저장
vector<int> stair2; //두번째 계단으로 도착해서 이동하는(+이동완료한) 사람 정보 저장
int person; //사람 수
int stair1K;    //첫번째 계단의 길이
int stair2K;    //두번째 계단의 길이
int minCnt = 987987987;

/// 사람들을 건물 밖으로 이동시킨다
/// @param timeCnt 사람들을 모두 밖으로 이동시키는 시간
void simul(int timeCnt) {
    int flag = 0;   //모든 사람들이 이동을 완료하지 않았을 경우 1로 저장
    int stair1Num, stair2Num;
    int i, j;
    
    
    if(stair1.size() + stair2.size() == person) {
        for(i=0; i<stair1.size(); i++) {
            if(stair1[i] > -1) {
                flag = 1;   break;
            }
        }
        for(i=0; i<stair2.size(); i++) {
            if(stair2[i] > -1) {
                flag = 1;   break;
            }
        }
        if(flag == 0) { //모든 사람들이 이동했으면 최소 이동시간을 업데이트하고 종료
            if(minCnt > timeCnt-1) {
                minCnt = timeCnt-1;
            }
            return;
        }   //종료조건
    }
        
    //계단에서 이동할수 잇는사람은 이동시킨다 (3명!!)
    stair1Num = stair2Num = 0;
    for(i=0; i<stair1.size(); i++) {
        if(stair1[i] == -1) {   //이동 완료한사람
            continue;
        }
        if(stair1[i] > -1) {    //이동완료 못한사람
            if(stair1Num < 3) { //앞에 세명만 이동시킨다
                if(stair1[i] != 0) {    //stair1[i] == 0은 계단 맨 아래에 있는경우로 계단 위에 있는 사람 카운트에서 제외!!! 개중요 이걸로 시간좀 잡아먹음.
                    stair1Num++;
                }
                stair1[i] -= 1;
            } else {    //세명 이후부터는 이동시키지 않는다
                break;
            }
        }
    }
    for(i=0; i<stair2.size(); i++) {
        if(stair2[i] == -1) {
            continue;
        }
        if(stair2[i] > -1) {
            if(stair2Num < 3) {
                if(stair2[i] != 0) {
                    stair2Num++;
                }
                stair2[i] -= 1;
            } else {
                break;
            }
        }
    }
    // end 계단에서 이동할수 잇는사람은 이동시킨다 (3명!!)

    //모든 사람에 대하여 (timeCnt == 계단입구까지의 거리) 일 겨우 해당 계단 벡터로 삽입한다
    int personR, personC;
    int stairNum, stairR, stairC;
    int dist = 0;
    int p = 0;
    for(j=0; j<locate.size();) {
        personR = locate[j];
        j += 1;
        personC = locate[j];
        j += 1;
        stairNum = pStair[p];
        p += 1;
        stairR = stair[stairNum][0];
        stairC = stair[stairNum][1];
            
        if(personR > stairR) {
            dist = personR - stairR;
        } else {
            dist = stairR - personR;
        }
        if(personC > stairC) {
            dist += (personC - stairC);
        } else {
            dist += (stairC - personC);
        }
        
        if(dist == timeCnt) {
            if(stairNum == 1) { //1번계단으로 이동하려고 햇을경우
                stair1.push_back(stair1K);  //계단 길이만큼
            } else {    //2번계단으로 이동하려고 햇을 경우
                stair2.push_back(stair2K);
            }
        }
    }
    // end 모든 사람에 대하여 (timeCnt == 계단입구까지의 거리) 일 겨우 해당 계단 벡터로 삽입한다
    
    simul(timeCnt+1);
}


/// 모든 사람들이 어떤 계단으로 이동할지 모든 경우의 수를 구하여 simul돌린다
/// @param idx 계단 정보 변경하려는 사람의 인덱스
void set_stair(int idx) {

    if(idx >= person) {
        stair1.clear();
        stair2.clear();
        simul(1);
    } else {
        pStair[idx] = 1;    //1번계단이동
        set_stair(idx+1);
        pStair[idx] = 2;    //2번계단이동
        set_stair(idx+1);
    }
}


int main(void) {
    int T, t, N, num;
    int stairCnt = 0;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d", &N);
        
        //초기화
        for(i=0; i<11; i++) {
            pStair[i] = 0;
        }
        for(i=0; i<3; i++) {
            for(j=0; j<2; j++) {
                stair[i][j] = 0;
            }
        }
        locate.clear();
        person = 0;
        stair1K = stair2K = stairCnt = 0;
        minCnt = 987987987;
        
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &num);
                if(num == 1) {  //사람이면 위치 정보 저장
                    locate.push_back(i);
                    locate.push_back(j);
                    person++;
                }
                if(num > 1) {   //계단이면 계단 위치 저장
                    if(stairCnt == 0) {
                        stair[1][0] = i;
                        stair[1][1] = j;
                        stair1K = num;
                        stairCnt++;
                    } else {
                        stair[2][0] = i;
                        stair[2][1] = j;
                        stair2K = num;
                        stairCnt++;
                    }
                }
            }
        }
                
        //사람들이 어느 계단으로 이동할건지 모든 경우의 수를 구한다
        set_stair(0);
        
        printf("#%d %d\n", t, minCnt);
    }
    return 0;
}
