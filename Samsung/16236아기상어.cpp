//
//  16236아기상어.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 24/09/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//  !! 아기상어가 몸무게를 update할때, 바로 그동안 먹은 물고기의 개수를 0으로 초기화해야함을 유의한다

#include <cstdio>
#include <queue>
#define     INFI 987987987
using namespace std;

int N;
int f_r, f_c;   //최단거리인 물고기의 행,열 위치
int T[22][22] = {0, };

//BFS탐색을 통해 상어로부터 잡아먹을 수 있는 가장 가까운 물고기의 위치를 알아낸다.
//dist_T에 각 위치까지에 대한 최단거리를 저장한다
//최단거리를 알아내면서, 잡아먹을수 있는 물고기들의 위치를 큐에 넣는다
int bfs_function(int s_r, int s_c) {
    int i, j;
    int dist_T[22][22] = {0, };
    int visited[22][22] = {0, };
    int min_d = INFI;
    int d;
    
    //최단거리를 알아낼 때 사용하는 큐
    queue <int> Queue;
    //잡아 먹을 수 있는 물고기들의 위치를 저장할 때 사용하는 큐
    queue <int> F_Queue;
    
    //현재 상어의 위치에서 부터 시작한다
    Queue.push(s_r);    Queue.push(s_c);
    visited[s_r][s_c] = 1;
    
    //큐가 빌때까지 반복
    while( !(Queue.empty()) ) {
        i = Queue.front();  Queue.pop();
        j = Queue.front();  Queue.pop();
        d = dist_T[i][j] + 1;
        
        //위쪽 그래프 탐색
        if(i-1 >= 0) {
            //아직 최단거리 확인을 하지 않았거나, 최단거리를 업데이트 할 수 있으면 최단거리 값을 저장한 다음에 큐에 push
            if(dist_T[i-1][j] == 0 || dist_T[i-1][j] > d) {
                dist_T[i-1][j] = d;
                Queue.push(i-1);    Queue.push(j);
            }
            //만약 먹을 수 있는 물고기라면 + 방문하지 않았더라면
            if(T[i-1][j] !=0 && T[i-1][j] < T[s_r][s_c] && visited[i-1][j] == 0) {
                F_Queue.push(i-1);  F_Queue.push(j);
            }
            visited[i-1][j] = 1;
        }//end if(위쪽 그래프 탐색)
        //아래쪽 그래프 탐색
        if(i+1 < N) {
            if(dist_T[i+1][j] == 0 || dist_T[i+1][j] > d) {
                dist_T[i+1][j] = d;
                Queue.push(i+1);    Queue.push(j);
            }
            if(T[i+1][j] !=0 && T[i+1][j] < T[s_r][s_c] && visited[i+1][j] == 0) {
                F_Queue.push(i+1);  F_Queue.push(j);
            }
            visited[i+1][j] = 1;
        }//end if(아래쪽 그래프 탐색)
        //왼쪽 그래프 탐색
        if(j-1 >= 0) {
            if(dist_T[i][j-1] == 0 || dist_T[i][j-1] > d) {
                dist_T[i][j-1] = d;
                Queue.push(i);    Queue.push(j-1);
            }
            if(T[i][j-1] !=0 && T[i][j-1] < T[s_r][s_c] && visited[i][j-1] == 0) {
                F_Queue.push(i);  F_Queue.push(j-1);
            }
            visited[i][j-1] = 1;
        }//end if(왼쪽 그래프 탐색)
        //오른쪽 그래프 탐색
        if(j+1 < N) {
            if(dist_T[i][j+1] == 0 || dist_T[i][j+1] > d) {
                dist_T[i][j+1] = d;
                Queue.push(i);    Queue.push(j+1);
            }
            if(T[i][j+1] !=0 && T[i][j+1] < T[s_r][s_c] && visited[i][j+1] == 0) {
                F_Queue.push(i);  F_Queue.push(j+1);
            }
            visited[i][j+1] = 1;
        }//end if(오른쪽 그래프 탐색)
        
    }//end while(큐가 빌때까지 반복)
    
    //가장 가까운 위치에 존재하는 물고기를 구한다
    while( !(F_Queue.empty()) ) {
        i = F_Queue.front();    F_Queue.pop();
        j = F_Queue.front();    F_Queue.pop();
        
        //최단 거리인 물고기이면
        if(min_d >= dist_T[i][j]) {
            //최단거리인 물고기가 여러마리이면 행이 가장 작은 물고기를 택한다
            if(min_d == dist_T[i][j]) {
                //행이 가장 작은 물고기가 여러마리이면 열이 가장 작은 물고기를 택한다
                if(f_r > i) {
                    f_r = i;    f_c = j;
                }else if(f_r == i) {
                    if(f_c > j) {
                        f_r = i;    f_c= j;
                    }
                }
            }else{
                min_d = dist_T[i][j];
                f_r = i;    f_c = j;
            }
        }
    }//end while(물고기 큐가 빌때까지 반복)
    
    //잡아먹을 수 있는 물고기가 없으면
    if(min_d == INFI) {
        return -1;
    }
    //잡아 먹을 수 있는 물고기가 있으면 그 물고기와의 거리를 리턴
    return min_d;

}

int main(void) {
    int i, j;
    int s_r, s_c;       //상어의 행, 열 위치
    int min_d;
    int dist_sum;
    int count;
    
    //변수 초기화
    dist_sum = count = 0;
    
    scanf("%d", &N);

    //테이블을 초기화하면서 상어의 위치를 알아낸다
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &T[i][j]);
            if(T[i][j] == 9) {
                s_r = i;
                s_c = j;
            }//end 상어위치
        }//end for(j)
    }//end for(i);
    
    //현재상태에서 잡아먹을 수 있는 가장 가까운 물고기의 위치를 알아낸다
    //최단거리인 물고기의 행, 열 위치를 무한대값으로 초기화
    f_r = f_c = INFI;
    min_d = bfs_function(s_r, s_c);
    
    while(min_d > 0) {
        printf("%d %d %d\n", min_d, f_r, f_c);
        //이동한 거리를 누적
        dist_sum += min_d;
        //현재 아기상어를 먹은 수를 카운팅
        count++;
        //아기상어 몸무게를 업데이트 할 수 있으면
        if(count == T[s_r][s_c]) {
            count = 0;
            T[s_r][s_c]++;
        }
        //상어의 위치를 잡아먹은 물고기의 위치로 업데이트
        T[f_r][f_c] = T[s_r][s_c];
        T[s_r][s_c] = 0;
        s_r = f_r;  s_c = f_c;
        
        //BFS함수 호출 (더 잡아먹을 수 있는지 확인)
        min_d = bfs_function(s_r, s_c);
    }
    
    printf("%d", dist_sum);
    return 0;
}
