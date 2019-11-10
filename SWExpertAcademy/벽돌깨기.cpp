//
//  벽돌깨기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 19/10/2019.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

const int MAXN = 18;

int N, W, H;
int table[MAXN][MAXN] = {0, };
int minC;
int visited[MAXN][MAXN] = {0, };

void breaking(int row, int col, int temp[MAXN][MAXN]) {
    int r;
    int val = temp[row][col];
    
    //구슬에 맞은 벽돌을 0으로 만든다
    table[row][col] = 0;
    visited[row][col] = 1;
    
    //상하좌우의 벽돌을 연쇄적으로 깬다
    for(r=1; r<val; r++) {
        if(row-r >= 0) {
            if(temp[row-r][col] > 0 && visited[row-r][col] == 0) {
                breaking(row-r, col, temp);
            }
        }
        if(row+r < H) {
            if(temp[row+r][col] > 0 && visited[row+r][col] == 0) {
                breaking(row+r, col, temp);
            }
        }
        if(col-r >= 0) {
            if(temp[row][col-r] > 0 && visited[row][col-r] == 0) {
                breaking(row, col-r, temp);
            }
        }
        if(col+r < W) {
            if(temp[row][col+r] > 0 && visited[row][col+r] == 0) {
                breaking(row, col+r, temp);
            }
        }
    }   //end 상하좌우 벽돌 연쇄적으로 깨기
    
}

void makeGood() {
    int nextB = 0;
    int d;
    int i, j, k;
    
    //각 열에 대하여 반복
    for(j=0; j<W; j++) {
        
        //각 행에 대하여 반복
        for(i=H-1; i>=0; i--) {
            
            //빈 공간이면 바로 위쪽 벽돌의 위치를 찾는다
            if(table[i][j] == 0) {
                for(k=i; k>=0; k--) {
                    //위에 벽돌 없음
                    if(k == 0 && table[k][j] == 0) {
                        nextB = -1;
                    }
                    //채워 넣을 위쪽 벽돌 위치를 저장
                    if(table[k][j] > 0) {
                        nextB = k;  break;
                    }
                    
                }
                
                //위에 벽돌 없으면 다음 열에 대하여 반복
                if(nextB == -1) {
                    break;
                }
                
                //위의 벽돌과의 거리를 구한다
                d = (i - nextB);
                
                //벽돌을 아래로 내린다
                for(k=0; k<=nextB; k++) {
                    table[i-k][j] = table[i-k-d][j];
                    table[i-k-d][j] = 0;
                }
                
                
            }   //end 바로 위쪽 벽돌 찾기
            
        }   //end 각 행에 대하여 반복
        
    }   //end 각 열에 대하여 반복
}


void dfs(int col, int cc) {
    int temp[MAXN][MAXN] = {0, };
    int counting = 0;
    int flag = 0;
    int i, j;
    
    //구슬을 모두 쐈으면
    if(cc > N) {
        //남은 벽돌의 수를 구해서 최소 남은 벽돌수를 업데이트한다
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                if(table[i][j] > 0) {
                    counting++;
                }
            }
        }
        
        if(minC > counting) {
            minC = counting;
        }

        return ;
    }   //end 구슬을 모두 쏜 경우
    else {
        
        //temp배열의 현재 벽돌의 정보를 저장한다
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                temp[i][j] = table[i][j];
            }
        }
        
        //입력으로 들어온 열에 대하여 벽돌을 깬다
        for(i=0; i<H; i++) {
            if(table[i][col] > 0) {
                breaking(i, col, temp);
                flag = 1;
                break;
            }
        }
        
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                visited[i][j] = 0;
            }
        }
        
            
        //빈 공간이 없도록 벽돌을 재정렬한다
        makeGood();
            
        //다음 벽돌을 깬다
        for(j=0; j<W; j++) {
            dfs(j, cc+1);
        }
            
        
        //원래 벽돌모양으로 원상복구한다
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                table[i][j] = temp[i][j];
            }
        }
        
    }   //end 구슬을 모두 쏘지 못한 경우
}

int main(void) {
    int T, t;
    int col;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=0; t<T; t++) {
        scanf("%d %d %d", &N, &W, &H);
        
        //벽돌의 초기 정보를 입력받는다
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                scanf("%d", &table[i][j]);
            }
        }
        
        //남은 벽돌의 최소값을 초기화한다
        minC = 987987987;
        

        //dfs호출
        for(col=0; col<W; col++) {
            dfs(col, 1);
        }
        
        printf("#t %d\n", minC);

        
    }   //end testcase
    
}
