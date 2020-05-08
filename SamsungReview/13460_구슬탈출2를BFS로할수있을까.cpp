//
//  13460_구슬탈출2를BFS로할수있을까.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/04.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
using namespace std;

typedef struct MarbleType {
    int rr, rc;
    int br, bc;
    int cnt;
}MarbleType;

int g_table[13][13] ={0,};
int g_N = 0;
int g_M = 0;
int g_min = 987987987;

void bfs_simul(MarbleType marble) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int cnt, rr, rc, br, bc;
    int rFlag, bFlag;
    int k;
    int row, col;
    int rRow, rCol, bRow, bCol, dist, rDist, bDist;
    queue<MarbleType> Q;
    
    Q.push(marble);
    
    while(true) {
        rr = Q.front().rr;
        rc = Q.front().rc;
        br = Q.front().br;
        bc = Q.front().bc;
        cnt = Q.front().cnt + 1;
        Q.pop();
        
        if(cnt > 10) {
            break;
        }
        
        for(k=0; k<4; k++) {
            rFlag = bFlag = 0;
            //빨간색움직이기
            row = rr + dx[k];
            col = rc + dy[k];
            while(true) {
                if(row < 0 || col < 0 || row >= g_N || col >= g_M) {
                    break;
                }
                if(g_table[row][col] == 1) {    //구멍
                    rFlag = 1;  break;
                } else if(g_table[row][col] == -1) {    //벽
                    break;
                }
                row += dx[k];
                col += dy[k];
            }
            //최종적인 빨간 구슬 위치
            rRow = row - dx[k];
            rCol = col - dy[k];
            dist = rr - rRow;
            if(dist < 0) { dist *= -1; }
            rDist = dist;
            dist = rc - rCol;
            if(dist < 0) { dist *= -1; }
            rDist += dist;

            //파란색움직이기
            row = br + dx[k];
            col = bc + dy[k];
            while(true) {
                if(row < 0 || col < 0 || row >= g_N || col >= g_M) {
                    break;
                }
                if(g_table[row][col] == 1) {    //구멍
                    bFlag = 1;  break;
                } else if(g_table[row][col] == -1) {    //벽
                    break;
                }
                row += dx[k];
                col += dy[k];
            }
            //최종적인 파란 구슬 위치
            bRow = row - dx[k];
            bCol = col - dy[k];
            dist = br - bRow;
            if(dist < 0) { dist *= -1; }
            bDist = dist;
            dist = bc - bCol;
            if(dist < 0) { dist *= -1; }
            bDist += dist;
            
            if(rFlag == 1 && bFlag == 0) {  //빨간색만 빠지면
                if(g_min > cnt) { g_min = cnt; }
                break;
            } else if(rFlag + bFlag == 0) { //둘다 안빠지면
                MarbleType newMarble;
                if(rRow == bRow && rCol == bCol) {    //도착위치가 동일하면
                    if(rDist < bDist) { //빨간색이 더 가까웠으면
                        newMarble.rr = rRow;
                        newMarble.rc = rCol;
                        newMarble.br = rRow - dx[k];
                        newMarble.bc = rCol - dy[k];
                    } else {    //파란색이 더 가까웠으면
                        newMarble.rr = bRow - dx[k];
                        newMarble.rc = bCol - dy[k];
                        newMarble.br = bRow;
                        newMarble.bc = bCol;
                    }
                } else {   //도착위치 다르면
                    newMarble.rr = rRow;
                    newMarble.rc = rCol;
                    newMarble.br = bRow;
                    newMarble.bc = bCol;
                }
                newMarble.cnt = cnt;
                Q.push(newMarble);
            }
        }
        
        if(g_min != 987987987) {
            break;
        }
        
    }
    
}


int main(void) {
    MarbleType marble;
    char tempStr[13];
    int i, j;
    
    scanf("%d %d", &g_N, &g_M);
    for(i=0; i<g_N; i++) {
        scanf("%s", tempStr);
        for(j=0; j<g_M; j++) {
            if(tempStr[j] == '#') {
                g_table[i][j] = -1;
            } else if(tempStr[j] == '.') {
                g_table[i][j] = 0;
            } else if(tempStr[j] == 'R') {
                marble.rr = i;
                marble.rc = j;
            } else if(tempStr[j] == 'B'){
                marble.br = i;
                marble.bc = j;
            } else {
                g_table[i][j] = 1;
            }
        }
    }
        
    marble.cnt = 0;
    
    bfs_simul(marble);
    
    if(g_min != 987987987) {
        printf("%d", g_min);
    } else {
        printf("-1");
    }
    
    return 0;
}
