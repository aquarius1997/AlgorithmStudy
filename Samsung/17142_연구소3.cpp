//
//  17142_연구소3.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/02.
//  Copyright © 2020 송혜경. All rights reserved.
// 1h5min ***

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int virusTable[52][52] = {0, };
int timeTable[52][52] = {0, };
const int INFI = 987987987;
int minTime = INFI;
vector<int> choosedVirus;


/// 바이러스 전파
void spread_virus(void) {
    queue<int> Queue;
    int row = 0;    int col = 0;
    int r = 0;  int c = 0;  int t = 0;
    int blankCnt = 0;
    int maxTime = -1;
    int flag = 0;
    int i, j, k;
    
    for(k=0; k<choosedVirus.size();) {  //M개의 활성 바이러스들의 위치를 알아내서
        row = choosedVirus[k];
        k++;
        col = choosedVirus[k];
        k++;
        
        //BFS방식으로 확산시킨다
        Queue.push(row);
        Queue.push(col);
        timeTable[row][col] = 1;    //1부터 시작하게 햇으므로 나중에 최소 시간 -1 해줘야함
        
        while(!Queue.empty()) {
            r = Queue.front();
            Queue.pop();
            c = Queue.front();
            Queue.pop();
            t = timeTable[r][c] + 1;
            
            //상하좌우 전파
            if(r-1 >= 0) {
                if(virusTable[r-1][c] != 1) {   //벽이 아니면서
                    if(timeTable[r-1][c] == 0 || timeTable[r-1][c] > t) {   //아직 이동안한 곳이거나 더 짧은 시간으로 이동가능하면
                        timeTable[r-1][c] = t;
                        Queue.push(r-1);    Queue.push(c);
                    }
                }
            }
            if(r+1 < N) {
                if(virusTable[r+1][c] != 1) {
                    if(timeTable[r+1][c] == 0 || timeTable[r+1][c] > t) {
                        timeTable[r+1][c] = t;
                        Queue.push(r+1);    Queue.push(c);
                    }
                }
            }
            if(c-1 >= 0) {
                if(virusTable[r][c-1] != 1) {
                    if(timeTable[r][c-1] == 0 || timeTable[r][c-1] > t) {
                        timeTable[r][c-1] = t;
                        Queue.push(r);  Queue.push(c-1);
                    }
                }
            }
            if(c+1 < N) {
                if(virusTable[r][c+1] != 1) {
                    if(timeTable[r][c+1] == 0 || timeTable[r][c+1] > t) {
                        timeTable[r][c+1] = t;
                        Queue.push(r);  Queue.push(c+1);
                    }
                }
            }
        }
        //end while
        
        //빈 칸중 최대 값을 알아낸다
        blankCnt = 0;   //빈칸수
        maxTime = -1;
        flag = 0;
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(virusTable[i][j] == 0) {
                    blankCnt++;
                    if(timeTable[i][j] == 0) {  //전파되지 않은 빈칸이 있으면
                        flag = 1;   break;
                    } else {
                        if(timeTable[i][j] > maxTime) {
                            maxTime = timeTable[i][j];
                        }
                    }
                }
            }
            if(flag == 1) { break; }
        }
        maxTime -= 1;
        //모두 전파되었으면 최소 시간 업데이트한다
        if(flag == 0) {
            if(blankCnt == 0) { //애초에 빈칸이 없었을 경우
                maxTime = 0;
            }
            if(minTime > maxTime) {
                minTime = maxTime;
            }
        }
    }
    
    //timeTable초기화
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            timeTable[i][j] = 0;
        }
    }
}

/// M개의 바이러스를 선택한다
/// @param cnt 현재까지 선택한 개수 (main 호출시 : 1)
/// @param row 선택할 바이러스의 행
/// @param col 선택할 바이러스의 열
void choose_M_virus(int cnt, int row, int col) {
    int i, j;
    
    //선택한 바이러스의 위치 정보를 벡터에 저장
    choosedVirus.push_back(row);
    choosedVirus.push_back(col);
    
    if(cnt == M) {  //M개를 선택했으면 BFS방식으로 최단 시간을 알아낸다
        spread_virus();
    } else {
        for(j=col+1; j<N; j++) {
            if(virusTable[row][j] == 2) {
                choose_M_virus(cnt+1, row, j);
            }
        }
        for(i=row+1; i<N; i++) {
            for(j=0; j<N; j++) {
                if(virusTable[i][j] == 2) {
                    choose_M_virus(cnt+1, i, j);
                }
            }
        }
    }
    
    //선택해재하면서 빼기 (스택성질)
    choosedVirus.pop_back();
    choosedVirus.pop_back();
}

int main(void) {
    int i, j;
    
    scanf("%d %d", &N, &M);
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &virusTable[i][j]);
        }
    }
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(virusTable[i][j] == 2) {
                choose_M_virus(1, i, j);
            }
        }
    }
    
    if(minTime == INFI) {   //어떤 경우에도 모든 빈칸에 바이러스를 퍼트릴 수 없으면
        minTime = -1;
    }
    
    printf("%d", minTime);
    
    return 0;
}
