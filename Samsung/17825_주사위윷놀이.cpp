//
//  17825_주사위윷놀이.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/07.
//  Copyright © 2020 송혜경. All rights reserved.
//  1h 25min. *****

#include <cstdio>
#include <vector>
using namespace std;

typedef struct NodeType { //그래프(윷판)의 노드 타입
    int num;    //점수
    int nextBlue;   //파란선이 있을 경우 파란선에 해당하는 다음 인덱스. 없으면 -1
    int nextRed;    //빨간선에 해당하는 다음 인덱스
} NodeType;

NodeType g_nodes[40] = {0,};    //윷판정보 초기화
int g_dice[11] = {0, }; //주사위 10개 숫자
int g_horse[4] = {0, };   //말들의 현재 위치(인덱스)
int g_maxValue = 0; //최대 썸

/// dfs방식으로 모든 경우의 수를 확인한다
/// @param turnCnt 현재까지의 턴, 주사위 숫자 인덱스를 가리킨다
/// @param sum 현재까지 누적된 점수
void simul_dfs(int turnCnt, int sum) {
    int tempValue = 0;
    int currentNode, nextNode;
    int sameFlag = 0;
    int i, j;
    
    if(sum > g_maxValue) {
        g_maxValue = sum;
    }
    //10턴을 완료하면
    if(turnCnt == 10) {
        return;
    }
    
    //모든 말들에 대해
    for(i=0; i<4; i++) {
        tempValue = g_horse[i]; //원래 위치 임시저장 (재귀호출 후 원래 위치로 원복시킬때사용)
        
        if(g_horse[i] != 32) {  //이동을 종료한 말이 아니면
            //이동을 마치는 칸에 다른 말이 있는지 확인한다
            currentNode = g_horse[i];
            if(g_nodes[currentNode].nextBlue != -1) {// 현재 위치가 파란색으로이동가능한 칸이면
                nextNode = g_nodes[currentNode].nextBlue;   //일단 파란색으로 한번 이동
            } else {    //빨간색으로 이동해야하는 칸이면
                nextNode = g_nodes[currentNode].nextRed;
            }
            
            for(j=1; j<g_dice[turnCnt]; j++) {  //한번 이동한거 제외하고 이동시킨다
                nextNode = g_nodes[nextNode].nextRed;
            }
            
            //종료하게 될 경우
            if(nextNode == 32) {
                g_horse[i] = nextNode;
                //재귀호출
                simul_dfs(turnCnt+1, sum);
            } else {    //종료하지 않을 경우
                //이동을 마친 칸에 다른 말이 없는지 확인
                sameFlag = 0;   //해당 위치에 말이 있으면 1로 변경
                for(j=0; j<4; j++) {
                    if(j == i) {    //현재 말 제외
                        continue;
                    }
                    if(g_horse[j] == nextNode) { sameFlag = 1; break; }
                }
                if(sameFlag == 0) { //이동마친 칸에 다른 말이 없는 경우
                    g_horse[i] = nextNode; //말이동
                    simul_dfs(turnCnt+1, sum+g_nodes[nextNode].num);    //재귀호출시 도착 지점점수 합산
                } else {    //있는 경우 (이거 애매함)
                    // !! 처음엔 simul_dfs 로 재귀호출을 햇으나 틀렸습니다가 나와서 문제에 따라 고르지 않았더니(재귀호출안하는) 성공함
                   //   simul_dfs(turnCnt+1, sum);  //이동시키지않고 재귀호출
                }
            }
        }
        //end if(g_horse[i] != 32) 
        
        g_horse[i] = tempValue; //원래 위치로 원복
    }

}


/// 윷판 그래프 초기화
void init_graph(void) {
    int idx = 0;
    int i = 0;
    
    //시작지점
    g_nodes[idx].num = 0;
    g_nodes[idx].nextBlue = -1;
    g_nodes[idx].nextRed = 1;
    
    idx += 1;
    i = 2;
    for(; idx<=19; idx++) {
        g_nodes[idx].num = i;
        i += 2;
        g_nodes[idx].nextBlue = -1;
        g_nodes[idx].nextRed = idx+1;
    }
    g_nodes[20].num = 40;
    g_nodes[20].nextBlue = -1;
    g_nodes[20].nextRed = 32;
    
    g_nodes[5].nextBlue = 21;
    g_nodes[10].nextBlue = 24;
    g_nodes[15].nextBlue = 26;
    
    i = 13;
    for(idx=21; idx<=23; idx++) {
        g_nodes[idx].num = i;
        i += 3;
        g_nodes[idx].nextBlue = -1;
        g_nodes[idx].nextRed = idx+1;
    }
    i = 22;
    for(idx=24; idx<=25; idx++) {
        g_nodes[idx].num = i;
        i += 2;
        g_nodes[idx].nextBlue = -1;
        g_nodes[idx].nextRed = idx+1;
    }
    i = 28;
    for(idx=26; idx<=28; idx++) {
        g_nodes[idx].num = i;
        i -= 1;
        g_nodes[idx].nextBlue = -1;
        g_nodes[idx].nextRed = idx+1;
    }
    g_nodes[23].nextRed = g_nodes[25].nextRed = g_nodes[28].nextRed = 29;
    i = 25;
    for(idx=29; idx<=31; idx++) {
        g_nodes[idx].num = i;
        i += 5;
        g_nodes[idx].nextBlue = -1;
        g_nodes[idx].nextRed = idx+1;
    }
    g_nodes[31].nextRed = 20;
    g_nodes[32].num = 0;
    g_nodes[32].nextBlue = g_nodes[32].nextRed = 32;
}

int main(void) {
    int i;
    
    for(i=0; i<10; i++) {
        scanf("%d", &g_dice[i]);
    }
    
    init_graph();
    
    simul_dfs(0, 0);
    
    printf("%d", g_maxValue);
    
    return 0;
}
