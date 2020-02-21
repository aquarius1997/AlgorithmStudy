//
//  모의ST_줄기세포배양.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <cstdio>
#include <queue>
#define STARTIDX   300
using namespace std;

typedef struct CellType{
    int inactiveCnt;    //남은 비활성 카운트를 저장 -> 0이되면 활성 세포
    int activeCnt;  //남은 활성 카운트를 저장 -> 0이되면 죽은 세포
    int row;    //세포의 행 정보
    int col;    //세포의 열정보
}CellType;

int cell[700][700] = {0, }; //-1 : 죽은 세포, 양수 : 살아있는 세포와 그 세포의 생명력값, 0 : 비어있는 셀
int K;
int answer;

/// timeCnt후의 줄기세포 배양 정보를 입력으로 받는다 + 줄기세포를 배양하는 함수
/// @param ct 살아있는 줄기세포의 정보를 담은 큐
/// @param timeCnt 몇시간 이후인지를 담고있는 카운팅 변수
void cultivation(queue<CellType> ct, int timeCnt) {
    queue<int> cellInf, tempCellInf; //새로 배양된 세포들의 정보[행+열+세포값]를 저장하는 큐
    queue<CellType> newCt;  //timeCnt+1 시간 후의 살아있는 세포를 저장하는 큐
    CellType currentCell;
    int row, col, cn;
    int cellNum;
    
    if(timeCnt == K) {  //종료조건
        answer = ct.size(); //살아있는 세포[활성+비활성] 의 개수
        return;
    } else {
        while(!ct.empty()) {    //살아있는 모든 줄기세포들에 대하여 반복
            currentCell = ct.front();   ct.pop();
            
            if(currentCell.inactiveCnt > 0) {  //현재 비활성 상태이면
                currentCell.inactiveCnt = currentCell.inactiveCnt - 1;
                
                newCt.push(currentCell);
            } else {    //현재 활성상태이면
                currentCell.activeCnt = currentCell.activeCnt - 1;
                
                cellNum = cell[currentCell.row][currentCell.col];

                if(currentCell.activeCnt > 0) {    //세포가 죽지 않았으면
                    newCt.push(currentCell);
                } else {    //세포가 죽었으면
                    cell[currentCell.row][currentCell.col] = -1;
                }   //end 세포 죽음
                
                //세포의 상하좌우 셀이 빈 셀일 경우 newCell에 정보를 삽입한다
                if(cell[(currentCell.row)-1][(currentCell.col)] == 0) {
                    cellInf.push((currentCell.row)-1);
                    cellInf.push((currentCell.col));
                    cellInf.push(cellNum);
                }
                if(cell[(currentCell.row)+1][(currentCell.col)] == 0) {
                    cellInf.push((currentCell.row)+1);
                    cellInf.push((currentCell.col));
                    cellInf.push(cellNum);
                }
                if(cell[(currentCell.row)][(currentCell.col)-1] == 0) {
                    cellInf.push((currentCell.row));
                    cellInf.push((currentCell.col)-1);
                    cellInf.push(cellNum);
                }
                if(cell[(currentCell.row)][(currentCell.col)+1] == 0) {
                    cellInf.push((currentCell.row));
                    cellInf.push((currentCell.col)+1);
                    cellInf.push(cellNum);
                }
                    //end 세포의 상하좌우 셀이 빈 셀일 경우 newCell에 정보를 삽입한다

            }   //end 현재 활성상태이면
        }   //end 살아있는 모든 줄기세포들에 대하여 반복
        
        
        // !!!! 처음에 이다음 while코드 2개를 [end 살아있는 모든 줄기세포들에 대하여 반복] 이전에 삽입해서 제대로 동작하지 않음.
        
        //cellInf의 값을 바탕으로 timeCnt+1시간 후의 세포 정보를 업데이트한다
        while(!cellInf.empty()) {
            row = cellInf.front();  cellInf.pop();
            col = cellInf.front();  cellInf.pop();
            cn = cellInf.front();   cellInf.pop();
                            
            if(cell[row][col] == 0) {
                cell[row][col] = cn;
                tempCellInf.push(row);  tempCellInf.push(col);   //새로 생긴 세포 정보 저장
            } else {
                if(cell[row][col] < cn) { //더 큰값으로 업데이트 가능하면 업데이트
                    cell[row][col] = cn;
                }
            }
        }   //end while(!cellInf.empty())
        
        while(!tempCellInf.empty()) {
            row = tempCellInf.front();  tempCellInf.pop();
            col = tempCellInf.front();  tempCellInf.pop();
            
            CellType newCell;
            newCell.activeCnt = newCell.inactiveCnt = cell[row][col];
            newCell.row = row;
            newCell.col = col;
            
            newCt.push(newCell);
        }   //end while(!tempCellInf.empty())
        
        //재귀함수호출
        cultivation(newCt, timeCnt+1);
    }
}


int main(void) {
    int T, t, N, M, c;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d %d", &N, &M, &K);
        
        queue<CellType> liveCellQ;   //살아 있는 줄기세포의 노드 정보를 담는 큐
        
        for(i=0; i<N; i++) {    //줄기세포값 초기화
            for(j=0; j<M; j++) {
                scanf("%d", &c);
                cell[i+STARTIDX][j+STARTIDX] = c;
                if(c != 0) {    //살아있는 줄기 세포는 큐에 삽입
                    CellType ct;
                    ct.inactiveCnt = ct.activeCnt = c;
                    ct.row = i+STARTIDX;
                    ct.col = j+STARTIDX;
                    liveCellQ.push(ct);
                }
            }
        }   //end 줄기세포 초기화
        
        //줄기세포를 배양하는 함수를 호출한다
        cultivation(liveCellQ, 0);
        
        printf("#%d %d\n", t, answer);
        
        
        for(i=0; i<700; i++) {
            for(j=0; j<700; j++) {
                cell[i][j] = 0;
            }
        }
    }   //end for(t)
    
    return 0;
}
