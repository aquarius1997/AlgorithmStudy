//
//  모의ST_원자소멸시뮬레이션.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/03.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef struct NodeType{
    int row;
    int col;
    int dir;
    int flag;   //죽으면 1
    int K;  //에너지
}NodeType;

NodeType atom[1001];
int table[2002][2002] = {0, };
int N;  //원자개수
int answer = 0;


/// 원자 구조체에 대해 이동 이후 위치 정보로 업데이트 + X.5 초에 터지는 경우 해당 함수에서 처리
/// @param atomNum 움직이려는 원자 번호
void move_func(int atomNum) {
    int row, col;
    int num;
    
    //원래 위치에 대해 테이블 초기화
    row = atom[atomNum].row;
    col = atom[atomNum].col;
    table[row][col] = 0;
    
    if(atom[atomNum].dir == 0) {
        atom[atomNum].row -= 1;
    } else if(atom[atomNum].dir == 1) {
        atom[atomNum].row += 1;
    } else if(atom[atomNum].dir == 2) {
        atom[atomNum].col -= 1;
    } else {
        atom[atomNum].col += 1;
    }
    
    //이동한 이후 행열 알아내고
    row = atom[atomNum].row;
    col = atom[atomNum].col;
    //만일 이동한 이후가 테이블 범위를 벗어나면 영원히 다른 원자랑 부딪힐 일이 없으므로 그냥 flag = 1 처리한다
    if(row < 0 || row > 2000 || col < 0 || col > 2000) {
        atom[atomNum].flag = 1;
    } else {
        //이동하려는 위치에 다른 원자가 있으면 둘은 X.5초에 터짐
        if(table[row][col] != 0) {
            num = table[row][col];  //부딪힐수도있는 원자
            int dirSum = atom[atomNum].dir + atom[num].dir;
            if(dirSum == 1 || dirSum == 5) {    //부딪힘 확정
                answer += (atom[atomNum].K + atom[num].K);  //둘의 에너지 방출
                table[row][col] = 0;    //상대 원자 정보도 테이블에서 지운다
                atom[atomNum].flag = 1;
                atom[num].flag = 1;
            }
        }
    }
}

/// (timeCnt - 0.5) ~ timeCnt 시간의 시뮬레이션을 실행한다
/// @param timeCnt 초
void simul(int timeCnt) {
    queue<int> Queue;   //이번에 부딪혀서 사라질 원자의 원자번호 저장
    int atomNum;
    int row, col;
    int i;
    
    
    if(timeCnt > 2002) {
        return;
    }
    //timeCnt - 0.5초에 터지는 원자들을 알아낸다 + 원자 구조체에 대해 이동한 이후 행열정보를 업데이트한다
    for(i=1; i<=N; i++) {
        if(atom[i].flag == 0) {
            move_func(i);
        }
    }
    //end timeCnt - 0.5초에 터지는 원자들을 알아낸다
    //timeCnt에 터지는 원자들을 알아낸다
    for(i=1; i<=N; i++) {
        if(atom[i].flag == 0) {
            row = atom[i].row;
            col = atom[i].col;
            if(table[row][col] == 0) {  //같은 위치로 와서 부딪힐 원자 없으면 해당 원자번호로 저장
                table[row][col] = i;
            } else {    //부딪히는게 생기면
                Queue.push(table[row][col]);    //원래 있던 원자는 큐에 넣고 나중에 처리
                //이번에 부딪힐 원자는 에너지방출 + 없어짐 처리
                answer += atom[i].K;
                atom[i].flag = 1;
            }
        }
    }
    //end timeCnt에 터지는 원자들을 알아낸다
    //큐에 대해 처리
    while(!Queue.empty()) {
        atomNum = Queue.front();
        Queue.pop();
        row = atom[atomNum].row;
        col = atom[atomNum].col;
        //중복해서 더하지 않기 위해
        if(atom[atomNum].flag == 0) {
            atom[atomNum].flag = 1;
            answer += atom[atomNum].K;
            table[row][col] = 0;    // !!!!!!!!!!!!!!처음에 이 코드 빼먹어서 테케 몇개 틀림
        }
    }
    //end 큐 처리
    //재귀호출
    simul(timeCnt+1);
    
}

int main(void) {
    int T, t, x, y, dir, K;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d", &N);
        
        for(i=1; i<=N; i++) {
            scanf("%d %d %d %d", &x, &y, &dir, &K);

            table[(1000 - y)][(1000 + x)] = i;  //테이블에 원자 번호로 저장
            atom[i].row = 1000 - y;
            atom[i].col = 1000 + x;
            atom[i].dir = dir;
            atom[i].flag = 0;
            atom[i].K = K;
        }
        
        //함수호출
        simul(1);
        
        //정답출력
        printf("#%d %d\n", t, answer);
        
        //초기화
        answer = 0;
        for(i=0; i<2001; i++) {
            for(j=0; j<2001; j++) {
                table[i][j] = 0;
            }
        }
    }
    
    return 0;
}

