//
//  모의ST_핀볼게임.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/22.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
using namespace std;

typedef struct Pin {
    int row;
    int col;
    int dir;    //1:위로이동, 2:오른쪽으로이동, 3:아래로이동, 4:왼쪽이동
    int cnt;    //핀볼점수
}Pin;

typedef struct Hole {
    int row1, row2;
    int col1, col2;
}Hole;

int table[102][102] = {0, };
int N;
Hole hole[5];   //웜홀 [i] -> i+6번웜홀
int maxCnt;
Pin pin;

/// 벽에 부딪힌 핀볼의 이동 방향을 바꾼다
void changeDir(int brickNum) {
    if(brickNum == 1) {
        if(pin.dir == 1) {
            pin.dir = 3;
        } else if(pin.dir == 2) {
            pin.dir = 4;
        } else if(pin.dir == 3) {
            pin.dir = 2;
        } else {
            pin.dir = 1;
        }
    } else if(brickNum == 2) {
        if(pin.dir == 1) {
            pin.dir = 2;
        } else if(pin.dir == 2) {
            pin.dir = 4;
        } else if(pin.dir == 3) {
            pin.dir = 1;
        } else {
            pin.dir = 3;
        }
    } else if(brickNum == 3) {
        if(pin.dir == 1) {
            pin.dir = 4;
        } else if(pin.dir == 2) {
            pin.dir = 3;
        } else if(pin.dir == 3) {
            pin.dir = 1;
        } else {
            pin.dir = 2;
        }
    } else if(brickNum == 4) {
        if(pin.dir == 1) {
            pin.dir = 3;
        } else if(pin.dir == 2) {
            pin.dir = 1;
        } else if(pin.dir == 3) {
            pin.dir = 4;
        } else {
            pin.dir = 2;
        }
    } else {
        if(pin.dir == 1) {
            pin.dir = 3;
        } else if(pin.dir == 2) {
            pin.dir = 4;
        } else if(pin.dir == 3) {
            pin.dir = 1;
        } else {
            pin.dir = 2;
        }
    }
}


/// 핀볼을 이동방향으로 굴린다
void simul() {
    int i, j;
    int holeInfo;
    
    if(pin.dir == 1) {  //위로 이동하는 핀볼
        if(pin.row == N) {
            i = N-1;
            pin.row = N-1;
        } else {
            i = pin.row - 1;
        }
        for(; i>=0; i--) {    //벽에 부딪히기 직전까지
            if(table[i][pin.col] == 0) {    //아무것도 없으면
                continue;
            }
            else if(table[i][pin.col] == -2 || table[i][pin.col] == -1) {    //원래 위치로 오거나 블랙홀만나면
                if(maxCnt < pin.cnt) {
                    maxCnt = pin.cnt;
                }
                pin.cnt = 0;
                return;
            }
            else if(table[i][pin.col] >= 1 && table[i][pin.col] <= 5) {  //벽돌 부딪
                changeDir(table[i][pin.col]);   //핀볼이동방향 바꾸고
                pin.cnt++;
                //핀볼 위치조정
                pin.row = i;
                pin.col = pin.col;
                simul();
                return;
            }   //end if(벽돌에 부딪)
            else if(table[i][pin.col] >= 6 && table[i][pin.col] <= 10) {    //웜홀
                holeInfo = table[i][pin.col];
                //다른 웜홀로 이동시킨다
                if(hole[holeInfo-6].row1 == i && hole[holeInfo-6].col1 == pin.col) {
                    pin.row = hole[holeInfo-6].row2;
                    pin.col = hole[holeInfo-6].col2;
                } else {
                    pin.row = hole[holeInfo-6].row1;
                    pin.col = hole[holeInfo-6].col1;
                }
                simul();
                return;
            }   //end if(웜홀)
        }   //end 벽에 부딪히기 직전까지
        //벽에 부딪혔으니 방향 바꾸고 카운팅
        pin.dir = 3;
        pin.row = -1;
        pin.cnt++;
        simul();
        return;
    }   //end if(pin.dir == 1)
    if(pin.dir == 2) {  //오른쪽으로 이동하는 핀볼
        if(pin.col == -1) {
            j = 0;
            pin.col = 0;
        } else {
            j = pin.col + 1;
        }
        for(; j<N; j++) {    //벽에 부딪히기 직전까지
            if(table[pin.row][j] == 0) {    //아무것도 없으면
                continue;
            }
            else if(table[pin.row][j] == -2 || table[pin.row][j] == -1) {    //원래 위치로 오거나 블랙홀만나면
                if(maxCnt < pin.cnt) {
                    maxCnt = pin.cnt;
                }
                return;
            }
            else if(table[pin.row][j] >= 1 && table[pin.row][j] <= 5) {  //벽돌 부딪
                changeDir(table[pin.row][j]);   //핀볼이동방향 바꾸고
                pin.cnt++;
                //핀볼 위치조정
                pin.row = pin.row;
                pin.col = j;
                simul();
                return;
            }   //end if(벽돌에 부딪)
            else if(table[pin.row][j] >= 6 && table[pin.row][j] <= 10) {    //웜홀
                holeInfo = table[pin.row][j];
                //다른 웜홀로 이동시킨다
                if(hole[holeInfo-6].row1 == pin.row && hole[holeInfo-6].col1 == j) {
                    pin.row = hole[holeInfo-6].row2;
                    pin.col = hole[holeInfo-6].col2;
                } else {
                    pin.row = hole[holeInfo-6].row1;
                    pin.col = hole[holeInfo-6].col1;
                }
                simul();
                return;
            }   //end if(웜홀)
        }   //end 벽에 부딪히기 직전까지
        //벽에 부딪혔으니 방향 바꾸고 카운팅
        pin.dir = 4;
        pin.col = N;
        pin.cnt++;
        simul();
        return;
    }   //end if(pin.dir == 2)
    if(pin.dir == 3) {  //아래로 이동하는 핀볼
        if(pin.row == -1) {
            i = 0;
            pin.row = 0;
        } else {
            i = pin.row + 1;
        }
        for(; i<N; i++) {    //벽에 부딪히기 직전까지
            if(table[i][pin.col] == 0) {    //아무것도 없으면
                continue;
            }
            else if(table[i][pin.col] == -2 || table[i][pin.col] == -1) {    //원래 위치로 오거나 블랙홀만나면
                if(maxCnt < pin.cnt) {
                    maxCnt = pin.cnt;
                }
                return;
            }
            else if(table[i][pin.col] >= 1 && table[i][pin.col] <= 5) {  //벽돌 부딪
                changeDir(table[i][pin.col]);   //핀볼이동방향 바꾸고
                pin.cnt++;
                //핀볼 위치조정
                pin.row = i;
                pin.col = pin.col;
                simul();
                return;
            }   //end if(벽돌에 부딪)
            else if(table[i][pin.col] >= 6 && table[i][pin.col] <= 10) {    //웜홀
                holeInfo = table[i][pin.col];
                //다른 웜홀로 이동시킨다
                if(hole[holeInfo-6].row1 == i && hole[holeInfo-6].col1 == pin.col) {
                    pin.row = hole[holeInfo-6].row2;
                    pin.col = hole[holeInfo-6].col2;
                } else {
                    pin.row = hole[holeInfo-6].row1;
                    pin.col = hole[holeInfo-6].col1;
                }
                simul();
                return;
            }   //end if(웜홀)
        }   //end 벽에 부딪히기 직전까지
        //벽에 부딪혔으니 방향 바꾸고 카운팅
        pin.dir = 1;
        pin.row = N;
        pin.cnt++;
        simul();
        return;
    }   //end if(pin.dir == 3)
    if(pin.dir == 4) {  //왼쪽으로 이동하는 핀볼
        if(pin.col == N) {
            j = N-1;
            pin.col = N-1;
        } else {
            j = pin.col - 1;
        }
        for(; j>=0; j--) {    //벽에 부딪히기 직전까지
            if(table[pin.row][j] == 0) {    //아무것도 없으면
                continue;
            }
            else if(table[pin.row][j] == -2 || table[pin.row][j] == -1) {    //원래 위치로 오거나 블랙홀만나면
                if(maxCnt < pin.cnt) {
                    maxCnt = pin.cnt;
                }
                return;
            }
            else if(table[pin.row][j] >= 1 && table[pin.row][j] <= 5) {  //벽돌 부딪
                changeDir(table[pin.row][j]);   //핀볼이동방향 바꾸고
                pin.cnt++;
                //핀볼 위치조정
                pin.row = pin.row;
                pin.col = j;
                simul();
                return;
            }   //end if(벽돌에 부딪)
            else if(table[pin.row][j] >= 6 &&table[pin.row][j] <= 10) {    //웜홀
                holeInfo = table[pin.row][j];
                //다른 웜홀로 이동시킨다
                if(hole[holeInfo-6].row1 == pin.row && hole[holeInfo-6].col1 == j) {
                    pin.row = hole[holeInfo-6].row2;
                    pin.col = hole[holeInfo-6].col2;
                } else {
                    pin.row = hole[holeInfo-6].row1;
                    pin.col = hole[holeInfo-6].col1;
                }
                simul();
                return;
            }   //end if(웜홀)
        }   //end 벽에 부딪히기 직전까지
        //벽에 부딪혔으니 방향 바꾸고 카운팅
        pin.dir = 2;
        pin.col = -1;
        pin.cnt++;
        simul();
        return;
    }   //end if(pin.dir == 4)
}

int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        //초기화
        maxCnt = 0;
        for(i=0; i<5; i++) {
            hole[i].row1 = hole[i].row2 = hole[i].col1 = hole[i].col2 = -100;
        }
        
        scanf("%d", &N);
        
        //테이블 정보 입력받기
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &table[i][j]);
                //웜홀 구조체 초기화필요1!!!
                if(table[i][j] >=6 && table[i][j] <=10) {
                    if(hole[(table[i][j]-6)].row1 == -100) {    //쌍중의 첫번째 웜홀이면
                        hole[(table[i][j]-6)].row1 = i;
                        hole[(table[i][j]-6)].col1 = j;
                    } else {
                        hole[(table[i][j]-6)].row2 = i;
                        hole[(table[i][j]-6)].col2 = j;
                    }
                }
            }
        }
        
        //핀볼을 놓을 수 있는 곳에 핀볼을 놓고 상하좌우로 굴려본다
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(table[i][j] == 0) {
                    table[i][j] = -2;
                    
                    //핀 구조체 초기화필요
                    pin.cnt = 0;
                    pin.row = i;
                    pin.col = j;
                    pin.dir = 1;
                    simul();
                    
                    //핀 구조체 초기화필요
                    pin.cnt = 0;
                    pin.row = i;
                    pin.col = j;
                    pin.dir = 2;
                    simul();
                    
                    //핀 구조체 초기화필요
                    pin.cnt = 0;
                    pin.row = i;
                    pin.col = j;
                    pin.dir = 3;
                    simul();

                    
                    //핀 구조체 초기화필요
                    pin.cnt = 0;
                    pin.row = i;
                    pin.col = j;
                    pin.dir = 4;
                    simul();
                    
                    table[i][j] = 0;    //핀볼 위치 초기화
                }
            }
        }   //end 핀볼 상하좌우 굴리기
        
        printf("#%d %d\n", t, maxCnt);

    }   //end for(t)
    return 0;
}
