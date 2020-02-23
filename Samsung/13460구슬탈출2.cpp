//
//  13460구슬탈출2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/22.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** -> 아이디어는 쉽게 생각나나 늘 시뮬레이션을 풀때 구현에서 많은 실수가 생김. 빡침.

#include <cstdio>
#define INFI    987987987
using namespace std;

int table[12][12] = {0,};
int N, M;
int redRow, redCol;
int blueRow, blueCol;
int redDist, blueDist;
int minCnt;

/// 빨간구슬 오른쪽으로 굴리기
void redRight(void) {
    int j;
    
    for(j=redCol+1; j<M; j++) {
        if(table[redRow][j] == -1 || table[redRow][j] == 2) { //벽이거나 파란 구슬이 있으면
            table[redRow][redCol] = 0;  //원래자리 빈곳으로 만들고
            redCol = j-1;
            table[redRow][redCol] = 1; //빨간 구슬 놓기
            break;
        } else if(table[redRow][j] == 3) {  //구멍이면 얼마나 이동했는지 거리 구하기
            redDist = j - redCol;
            table[redRow][redCol] = 0;
            break;
        }
    }
}

/// 파란구슬 오른쪽으로 굴리기
void blueRight(void) {
    int j;
    
    for(j=blueCol+1; j<M; j++) {
        if(table[blueRow][j] == -1 || table[blueRow][j] == 1) {
            table[blueRow][blueCol] = 0;
            blueCol = j-1;
            table[blueRow][blueCol] = 2;
            break;
        } else if(table[blueRow][j] == 3) {
            blueDist = j - blueCol;
            table[blueRow][blueCol] = 0;
            break;
        }
    }
}

/// 빨간구슬 위로 굴리기
void redUp(void) {
    int i;
    
    for(i=redRow-1; i>=0; i--) {
        if(table[i][redCol] == -1 || table[i][redCol] == 2) {
            table[redRow][redCol] = 0;
            redRow = i+1;
            table[redRow][redCol] = 1;
            break;
        } else if(table[i][redCol] == 3) {
            redDist = redRow - i;
            table[redRow][redCol] = 0;
            break;
        }
    }
}

/// 파란구슬 위로 굴리기
void blueUp(void) {
    int i;
    
    for(i=blueRow-1; i>=0; i--) {
        if(table[i][blueCol] == -1 || table[i][blueCol] == 1) {
            table[blueRow][blueCol] = 0;
            blueRow = i+1;
            table[blueRow][blueCol] = 2;
            break;
        } else if(table[i][blueCol] == 3) {
            blueDist = blueRow - i;
            table[blueRow][blueCol] = 0;
            break;
        }
    }
}

/// 빨간구슬 아래로 굴리기
void redDown(void) {
    int i;
    
    for(i=redRow+1; i<N; i++) {
        if(table[i][redCol] == -1 || table[i][redCol] == 2) {
            table[redRow][redCol] = 0;
            redRow = i-1;
            table[redRow][redCol] = 1;
            break;
        } else if(table[i][redCol] == 3) {
            redDist = i - redRow;
            table[redRow][redCol] = 0;
            break;
        }
    }
}

/// 파란구슬 아래로 굴리기
void blueDown(void) {
    int i;
    
    for(i=blueRow+1; i<N; i++) {
        if(table[i][blueCol] == -1 || table[i][blueCol] == 1) {
            table[blueRow][blueCol] = 0;
            blueRow = i-1;
            table[blueRow][blueCol] = 2;
            break;
        } else if(table[i][blueCol] == 3) {
            blueDist = i - blueRow;
            table[blueRow][blueCol] = 0;
            break;
        }
    }
}

/// 빨간 구슬 왼쪽으로 굴리기
void redLeft(void) {
    int j;
    
    for(j=redCol-1; j>=0; j--) {
        if(table[redRow][j] == -1 || table[redRow][j] == 2) {
            table[redRow][redCol] = 0;
            redCol = j+1;
            table[redRow][redCol] = 1;
            break;
        } else if(table[redRow][j] == 3) {
            redDist = redCol - j;
            table[redRow][redCol] = 0;
            break;
        }
    }
}

/// 파란구슬 왼쪽으로 굴리기
void blueLeft(void) {
    int j;
    
    for(j=blueCol-1; j>=0; j--) {
        if(table[blueRow][j] == -1 || table[blueRow][j] == 1) {
            table[blueRow][blueCol] = 0;
            blueCol = j+1;
            table[blueRow][blueCol] = 2;
            break;
        } else if(table[blueRow][j] == 3) {
            blueDist = blueCol - j;
            table[blueRow][blueCol] = 0;
            break;
        }
    }
}

void simul(int cnt, int direc) {
    int rr, rc, br, bc; //굴린 이후 위치 저장
    
    if(cnt > 10) {
        return;
    } else {
        
        if(direc == 1) {    //위로 굴리는거면
            redDist = blueDist = 0;
            
            //행값이 더 작은구슬을 먼저 굴린다
            if(redRow < blueRow) {
                redUp();
                blueUp();
            } else {
                blueUp();
                redUp();
            }
            
            //만약 구멍에 들어간 구슬이있는지 확인한다
            if(blueDist > 0) {  //파란구슬이 빠졌으면
                return;
            } else if(redDist > 0) {   //빨간구슬만 빠지면
                if(minCnt > cnt) {
                    minCnt = cnt;
                }
                return;
            }
            
            //위로 굴린 이후 위치를 저장
            rr = redRow;    rc = redCol;    br = blueRow;   bc = blueCol;
            
            simul(cnt+1, 2);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 3);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 4);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
        }   //end 위로 굴리기
        
        if(direc == 2) {    //아래로 굴리는거면
            redDist = blueDist = 0;
            
            //행값이 더 큰구슬을 먼저 굴린다
            if(redRow > blueRow) {
                redDown();
                blueDown();
            } else {
                blueDown();
                redDown();
            }
            
            //만약 구멍에 들어간 구슬이있는지 확인한다
            if(blueDist > 0) {  //파란구슬이 빠졌으면
                return;
            } else if(redDist > 0) {   //빨간구슬만 빠지면
                if(minCnt > cnt) {
                    minCnt = cnt;
                }
                return;
            }
            
            //아래로 굴린 이후 위치를 저장
            rr = redRow;    rc = redCol;    br = blueRow;   bc = blueCol;
            
            simul(cnt+1, 1);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 3);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 4);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
        }   //end 아래로 굴리기
        
        if(direc == 3) {    //오른쪽으로 굴리는거면
            redDist = blueDist = 0;
            
            //열값이 더 큰걸 먼저 굴린다
            if(redCol > blueCol) {
                redRight();
                blueRight();
            } else {
                blueRight();
                redRight();
            }
            
            //만약 구멍에 들어간 구슬이있는지 확인한다
            if(blueDist > 0) {  //파란구슬이 빠졌으면
                return;
            } else if(redDist > 0) {   //빨간구슬만 빠지면
                if(minCnt > cnt) {
                    minCnt = cnt;
                }
                return;
            }
            
            //오른쪽으로 굴린 이후 위치를 저장
            rr = redRow;    rc = redCol;    br = blueRow;   bc = blueCol;
            
            simul(cnt+1, 1);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 2);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 4);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
        }   //end 오른쪽으로 굴리기
        
        if(direc == 4) {    //왼쪽으로  굴리는거면
            redDist = blueDist = 0;
            
            //열값이 더 작은 구슬을 먼저 굴린다
            if(redCol < blueCol) {
                redLeft();
                blueLeft();
            } else {
                blueLeft();
                redLeft();
            }
            
            //만약 구멍에 들어간 구슬이있는지 확인한다
            if(blueDist > 0) {  //파란구슬이 빠졌으면
                return;
            } else if(redDist > 0) {   //빨간구슬만 빠지면
                if(minCnt > cnt) {
                    minCnt = cnt;
                }
                return;
            }
            
            //왼쪽으로 굴린 이후 위치를 저장
            rr = redRow;    rc = redCol;    br = blueRow;   bc = blueCol;
            
            simul(cnt+1, 1);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 2);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
            
            simul(cnt+1, 3);
            table[redRow][redCol] = table[blueRow][blueCol] = 0;
            redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
            table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
        }   //end 왼쪽으로 굴리기
    }
}
int main(void) {
    char str[12];
    int rr, rc, br, bc;
    int i, j;
    
    scanf("%d %d", &N, &M);
    
    for(i=0; i<N; i++) {
        scanf("%s", str);
        for(j=0; j<M; j++) {
            if(str[j] == '#') {
                table[i][j] = -1;
            } else if(str[j] == '.') {
                table[i][j] = 0;
            } else if(str[j] == 'O') {
                table[i][j] = 3;
            } else if(str[j] == 'R') {
                table[i][j] = 1;
                rr = redRow = i;
                rc = redCol = j;
            } else {
                table[i][j] = 2;
                br = blueRow = i;
                bc = blueCol = j;
            }
        }
    }
    
    minCnt = INFI;
    
    simul(1, 1);
    table[redRow][redCol] = table[blueRow][blueCol] = 0;
    redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
    table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;

    simul(1, 2);
    table[redRow][redCol] = table[blueRow][blueCol] = 0;
    redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
    table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;

    simul(1, 3);
    table[redRow][redCol] = table[blueRow][blueCol] = 0;
    redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
    table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
    
    simul(1, 4);
    table[redRow][redCol] = table[blueRow][blueCol] = 0;
    redRow = rr;    redCol = rc;    blueRow = br;   blueCol = bc;
    table[redRow][redCol] = 1;  table[blueRow][blueCol] = 2;
    
    if(minCnt == INFI) {
        minCnt = -1;
    }
    
    printf("%d", minCnt);
    
    return 0;
}
