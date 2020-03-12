//
//  14500_테트로미노.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/12.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <cstdio>
using namespace std;

int table[501][501] = {0, };
int maxCnt = 0;
int N, M;

void tetro1(int row, int col) {
    int i;
    int flag1 = 0;  int flag2 = 0;
    int temp1, temp2;
    temp1 = temp2 = table[row][col];
    
    for(i=1; i<=3; i++) {
        if(col + i >= M) {
            flag1 = 1;
        }
        if(row + i >= N) {
            flag2 = 1;
        }
        temp1 += table[row][col+i];
        temp2 += table[row+i][col];
    }
    if(flag1 == 0) {
        if(temp1 > maxCnt) {
            maxCnt = temp1;
        }
    }
    if(flag2 == 0) {
        if(temp2 > maxCnt) {
            maxCnt = temp2;
        }
    }
}

void tetro2(int row, int col) {
    int i, j;
    int temp = 0;
    
    for(i=0; i<2; i++) {
        for(j=0; j<2; j++) {
            if(row+i < N && col+j < M) {
                temp += table[row+i][col+j];
            } else {
                return;
            }
        }
    }
    if(temp > maxCnt) {
        maxCnt = temp;
    }
}

void tetro3(int row, int col) {
    int i, j;
    int flag = 0;
    int temp = 0;
    
    for(i=0; i<3; i++) {
        if(row+i < N) {
            temp += table[row+i][col];
        } else {
            flag = 1;
        }
    }
    if(flag == 0) {
        if(col+1 < M) {
            if(temp + table[row+2][col+1] > maxCnt) {
                maxCnt = temp + table[row+2][col+1];
            }
            if(temp + table[row][col+1] > maxCnt) {
                maxCnt = temp + table[row][col+1];
            }
        }
        if(col - 1 >= 0) {
            if(temp + table[row+2][col-1] > maxCnt) {
                maxCnt = temp + table[row+2][col-1];
            }
            if(temp + table[row][col-1] > maxCnt) {
                maxCnt = temp + table[row][col-1];
            }
        }
    }
    
    temp = flag = 0;
    
    for(j=0; j<3; j++) {
        if(col + j < M) {
            temp += table[row][col+j];
        } else {
            flag = 1;
        }
    }
    if(flag == 0) {
        if(row+1 < N) {
            if(temp + table[row+1][col] > maxCnt) {
                maxCnt = temp + table[row+1][col];
            }
            if(temp + table[row+1][col+2] > maxCnt) {
                maxCnt = temp + table[row+1][col+2];
            }
        }
        if(row-1 >= 0) {
            if(temp + table[row-1][col+2] > maxCnt) {
                maxCnt = temp + table[row-1][col+2];
            }
            if(temp + table[row-1][col] > maxCnt) {
                maxCnt = temp + table[row-1][col];
            }
        }
    }
}

void tetro4(int row, int col) {
    int temp = table[row][col];
    int flag = 0;
    
    if(row+1 < N) {
        temp += table[row+1][col];
    } else {
        flag = 1;
    }
    
    if(flag == 0) {
        if(col+1 < M && row+2 < N) {
            if(temp + table[row+1][col+1] + table[row+2][col+1] > maxCnt) {
                maxCnt = temp + table[row+1][col+1] + table[row+2][col+1];
            }
        }
        if(row+2 < N && col-1 >= 0) {
            if(temp + table[row+1][col-1] + table[row+2][col-1] > maxCnt) {
                maxCnt = temp + table[row+1][col-1] + table[row+2][col-1];
            }
        }
        if(col-1 >= 0 && col+1 < M) {
            if(temp + table[row+1][col-1] + table[row][col+1] > maxCnt) {
                maxCnt = temp + table[row+1][col-1] + table[row][col+1];
            }
            if(temp + table[row][col-1] + table[row+1][col+1] > maxCnt) {
                maxCnt = temp + table[row][col-1] + table[row+1][col+1];
            }
        }
    }
}

void tetro5(int row, int col) {
    int flag = 0;
    int temp = 0;
    for(int i=0; i<3; i++) {
        if(col+i > M) {
            flag = 1;   break;
        } else {
            temp += table[row][col+i];
        }
    }
    if(flag == 0) {
        if(row+1 < N) {
            if(temp + table[row+1][col+1] > maxCnt) {
                maxCnt = temp + table[row+1][col+1];
            }
        }
        if(row - 1 >= 0) {
            if(temp + table[row-1][col+1] > maxCnt) {
                maxCnt = temp + table[row-1][col+1];
            }
        }
    }
    flag = temp = 0;
    for(int i=0; i<3; i++) {
        if(row+i > N) {
            flag = 1;   break;
        } else {
            temp += table[row+i][col];
        }
    }
    if(flag == 0) {
        if(col-1 >= 0) {
            if(temp + table[row+1][col-1] > maxCnt) {
                maxCnt = temp + table[row+1][col-1];
            }
        }
        if(col+1 < M) {
            if(temp + table[row+1][col+1] > maxCnt) {
                maxCnt = temp + table[row+1][col+1];
            }
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &M);
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            tetro1(i, j);
            tetro2(i, j);
            tetro3(i, j);
            tetro4(i, j);
            tetro5(i, j);
        }
    }
    
    printf("%d", maxCnt);
    
    return 0;
}
