//
//  모의ST_줄기세포배양.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***** (시간초과)

#include <cstdio>
#include <queue>
using namespace std;

struct cellNode {
    int row;
    int col;
    int activeCnt;  //남은 활성 상태 카운트 저장
    int inactiveCnt;    //남은 비활성 상태 카운트 저장
};

int g_cell[700][700] = {0, };   //세포 정보 저장. 죽으면 -1
int g_N = 0;
int g_M = 0;
int g_K = 0;
int g_cellCnt = 0;


/// timeCnt시간인지 확인한 후, 아닐 경우 timeCnt+1시간의 세포 정보를 구한다
/// @param timeCnt 현재까지 흐른 시간
/// @param cells timeCnt시간에 살아있는 세포들을 저장
void simul(queue<cellNode> cells, int timeCnt) {
    queue<cellNode> nextCells;  //timeCnt+1시간에 살아있을 세포들을 저장
    queue<int> newCells;
    queue<cellNode> newCells2;
    int row, col, life;
    int i, j;
        
    if(timeCnt == g_K) {    //end simul
        g_cellCnt = cells.size();
        return;
    } else {    //recursive
        //1. 현재까지 살아있는 세포들에 대해
        while(!cells.empty()) {
            cellNode currentCell = cells.front();
            cells.pop();
            //1) 비활성/활성인지 구분
            if(currentCell.inactiveCnt > 0) {   //비활성
                currentCell.inactiveCnt -= 1;
                nextCells.push(currentCell);
            } else {    //활성
                row = currentCell.row;
                col = currentCell.col;
                
                //(1) 활성 카운트가 생명력이랑 같으면 추가 번식
                if(currentCell.activeCnt == g_cell[row][col]) {
                    //상하좌우확인
                    if(row-1 >=0) {
                        if(g_cell[row-1][col] == 0) {
                            newCells.push(row-1); newCells.push(col); newCells.push(g_cell[row][col]);
                        }
                    }
                    if(row+1 < 700) {
                        if(g_cell[row+1][col] == 0) {
                            newCells.push(row+1); newCells.push(col); newCells.push(g_cell[row][col]);
                        }
                    }
                    if(col-1 >= 0) {
                        if(g_cell[row][col-1] == 0) {
                            newCells.push(row); newCells.push(col-1); newCells.push(g_cell[row][col]);
                        }
                    }
                    if(col+1 < 700) {
                        if(g_cell[row][col+1] == 0) {
                            newCells.push(row); newCells.push(col+1); newCells.push(g_cell[row][col]);
                        }
                    }
                }
                //end (1)
                currentCell.activeCnt -= 1;
                if(currentCell.activeCnt > 0) { //timeCnt+1에 살아있을 세포만
                    nextCells.push(currentCell);
                }
            }
            //end 1)
        }
        //end 1
        
        //2. 새로 생긴 세포들에 대해 g_cell테이블에 저장. 이때 같은 자리로 중복될 수 있음
        while(!newCells.empty()) {
            row = newCells.front();  newCells.pop();
            col = newCells.front();  newCells.pop();
            life = newCells.front();    newCells.pop();
            
            if(life > g_cell[row][col]) {
                g_cell[row][col] = life;
                cellNode newCell;
                newCell.row = row;
                newCell.col = col;
                newCell.activeCnt = newCell.inactiveCnt = life;
                newCells2.push(newCell);
            }
        }
        //end 2
        
        //3. 중복된 것들 제거해서 nextCells에 추가
        while(!newCells2.empty()) {
            cellNode currentCell = newCells2.front();
            newCells2.pop();
            row = currentCell.row;
            col = currentCell.col;
            life = currentCell.inactiveCnt;
            
            if(g_cell[row][col] == life) {
                nextCells.push(currentCell);
            }
        }
        
        //3. 재귀호출
        simul(nextCells, timeCnt+1);
    }
}

int main(void) {
    queue<cellNode> cells;  //save alive cellNode
    int t, T;
    int i, j;
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        //initialize
        while(!cells.empty()) {
            cells.pop();
        }
        for(i=0; i<700; i++) {
            for(j=0; j<700; j++) {
                g_cell[i][j] = 0;
            }
        }

        scanf("%d %d %d", &g_N, &g_M, &g_K);
        //input g_cell
        for(i=0; i<g_N; i++) {
            for(j=0; j<g_M; j++) {
                scanf("%d", &g_cell[i+301][j+301]);
                //1. push alive cells to cells queue
                if(g_cell[i+301][j+301] > 0) {
                    cellNode newCell;
                    newCell.row = i+301;
                    newCell.col = j+301;
                    newCell.activeCnt = newCell.inactiveCnt = g_cell[i+301][j+301];
                    cells.push(newCell);
                }
                //end 1
            }
        }
        

        //2. call simul function
        simul(cells, 0);
        
        //3. 정답 출력
        printf("#%d %d\n", t, g_cellCnt);
        
    }
    
    
    return 0;
}
