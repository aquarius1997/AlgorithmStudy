//
//  16236_아기상어.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/28.
//  Copyright © 2020 송혜경. All rights reserved.
//  1h 20min
// 처음에 시간초과가 나서 당황해서 헤멨는데 알고보니 뜬금없는 곳에 초기화 코드를 넣어서 그랬음
/*
 첫번째 결과 : 틀렸습니다 -> 확인해 보니
 3
 1 3 0
 3 0 0
 0 0 9
 와 같이 도달할 수 없는 곳에 나보다 작은 크기의 물고기가 있는 경우를 고려 안했음
 두 번째 결과 : 메모리초과 -> moves 함수 안에 dist배열, Queue큐를 선언했는데 이것때문에
 세 번째 결과 : 시간초과 -> dist배열을 전역으로 빼고 초기화하는 부분을 이상한 곳에 넣어서 시간초과 남
 */
#include <cstdio>
#include <queue>
using namespace std;

typedef struct Shark {  //아기상어의 위치와 크기를 저장
    int row;
    int col;
    int weight;
    int eatedCnt;   //먹은 물고기 수
}Shark;

int N;  //공간크기
int fish[22][22] = {0, };   //물고기의 위치 저장
int dist[22][22] = {0, };
int seconds = 0;    //몇 초가 흘렀는지 카운팅
queue<int> Queue;
Shark shark;

///  아기 상어를 움직인다
void moves(void) {
    int fishCnt = 0;
    int eatFlag = 0;    //물고기 먹은거 표시하는 플래그
    int minDist = 987987987;    // 가장 가까운 먹을 수 있는 물고기와의 거리를 구할때 사용
    int row, col, d;
    int i, j;
    
    //먹을 수 있는 물고기의 수를 센다
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            dist[i][j] = 0; //dist배열 초기화
            if(fish[i][j] > 0 && fish[i][j] < shark.weight) {
                fishCnt++;
            }
        }
    }
    
    //먹을 수 있는 물고기가 없으면 종료
    if(fishCnt == 0) { return; }
    
    //먹을 수 있는 물고기가 있다면 BFS방식으로 각 칸의 최단 거리를 구한다
    Queue.push(shark.row);  Queue.push(shark.col);  Queue.push(0);
    dist[shark.row][shark.col] = 0;
    while(!Queue.empty()) {
        row = Queue.front();
        Queue.pop();
        col = Queue.front();
        Queue.pop();
        d = Queue.front();
        Queue.pop();
        d += 1;
        
        //상하좌우 최단 거리 업데이트 가능한지 확인
        if(row-1 >= 0) {
            if(fish[row-1][col] <= shark.weight) {
                if(dist[row-1][col] == 0 || d < dist[row-1][col]) { //한번도 이동한적 없는 곳이거나 더 빠르게 이동가능하면
                    dist[row-1][col] = d;
                    Queue.push(row-1);  Queue.push(col);    Queue.push(d);
                }
            }
        }
        if(row+1 < N) {
            if(fish[row+1][col] <= shark.weight) {
                if(dist[row+1][col] == 0 || d < dist[row+1][col]) {
                    dist[row+1][col] = d;
                    Queue.push(row+1);  Queue.push(col);    Queue.push(d);
                }
            }
        }
        if(col-1 >= 0) {
            if(fish[row][col-1] <= shark.weight) {
                if(dist[row][col-1] == 0 || d < dist[row][col-1]) {
                    dist[row][col-1] = d;
                    Queue.push(row);    Queue.push(col-1);  Queue.push(d);
                }
            }
        }
        if(col+1 < N) {
            if(fish[row][col+1] <= shark.weight) {
                if(dist[row][col+1] == 0 || d < dist[row][col+1]) {
                    dist[row][col+1] = d;
                    Queue.push(row);    Queue.push(col+1);  Queue.push(d);
                }
            }
        }
    }
    //end 최단거리 구하기

    //가장 가까운 먹을 수 있는 물고기를 찾는다
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(fish[i][j] > 0 && fish[i][j] < shark.weight) {   //먹을 수 있는 물고기의 위치
                if(minDist > dist[i][j] && dist[i][j] != 0) {  //중에서 최단 거리를 찾는다
                    minDist = dist[i][j];
                }
            }
        }
    }
    
    //가장 가까운 먹을 수 있는 물고기 중 가장 상단+왼쪽인걸 찾아 먹는다
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(dist[i][j] == minDist && fish[i][j] > 0 && fish[i][j] < shark.weight) { //먹어먹어
                fish[i][j] = 0;
                seconds += (minDist);   //시간 갱신
                //상어 위치 갱신
                shark.row = i;
                shark.col = j;
                //먹고 상어 크기 커질 수 있는지 확인
                shark.eatedCnt += 1;
                if(shark.eatedCnt == shark.weight) {
                    shark.eatedCnt = 0;
                    shark.weight += 1;
                }
                eatFlag = 1;
                moves();
                break;
            }
        }
        if(eatFlag == 1) {
            break;
        }
    }
    
    //재귀호출
    
}

int main(void) {
    int i, j;
    
    scanf("%d", &N);
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &fish[i][j]);
            if(fish[i][j] == 9) {   //아기상어 위치면 0 으로 저장하고 상어 구조체 초기화
                fish[i][j] = 0;
                shark.row = i;  shark.col = j;  shark.weight = 2;
                shark.eatedCnt = 0;
            }
        }
    }
    
    //함수 호출
    moves();
    
    //답 출력
    printf("%d", seconds);
    
    return 0;
}

