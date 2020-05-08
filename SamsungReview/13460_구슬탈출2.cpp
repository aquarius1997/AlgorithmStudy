//
//  13460_구슬탈출2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/04.
//  Copyright © 2020 송혜경. All rights reserved.
//
#include <cstdio>
using namespace std;

int g_table[13][13] = {0,};
int g_N = 0;
int g_M = 0;
int g_redCnt = 987987987;

void dfs_moving(int rr, int rc, int br, int bc, int cnt) {
    int nextrr, nextrc, nextbr, nextbc;
    int redFlag, blueFlag;
    int i, j;
    
    if(cnt > 10) {
        return;
    }
    
    redFlag = blueFlag = 0;
    //위로기울이기
    if(rr < br) {
        //빨간 구슬 굴리고
        for(i=rr-1; i>=0; i--) {
            if(g_table[i][rc] == -1) {   //벽
                break;
            } else if(g_table[i][rc] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = i+1;
            nextrc = rc;
        }
        //파란 구슬 굴리기
        for(i=br-1; i>=0; i--) {
            if(g_table[i][bc] == -1) {
                break;
            } else if(i == nextrr && bc == nextrc) { //빨간구슬위치
                break;
            } else if(g_table[i][bc] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = i+1;
            nextbc = bc;
        }
    } else {    //파란 구슬부터
        //파란 구슬 굴리기
        for(i=br-1; i>=0; i--) {
            if(g_table[i][bc] == -1) {
                break;
            } else if(g_table[i][bc] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = i+1;
            nextbc = bc;
        }
        //빨간 구슬 굴리기
        for(i=rr-1; i>=0; i--) {
            if(g_table[i][rc] == -1) {   //벽
                break;
            } else if(i == nextbr && rc == nextbc) { //파란 구슬 위치
                break;
            } else if(g_table[i][rc] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = i+1;
            nextrc = rc;
        }
    }

    if(blueFlag == 0 && redFlag == 1) {   //빨간거만 빠졋으면
        if(g_redCnt > cnt) { g_redCnt = cnt;}
    } else if(redFlag + blueFlag == 0 ){   //둘다 안빠졌으면
        dfs_moving(nextrr, nextrc, nextbr, nextbc, cnt+1);
    }
    //end 위로 기울이기
    //아래로 굴리기
    redFlag = blueFlag = 0;
    if(rr > br) {
        //빨간 구슬 굴리고
        for(i=rr+1; i<g_N; i++) {
            if(g_table[i][rc] == -1) {   //벽
                break;
            } else if(g_table[i][rc] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = i-1;
            nextrc = rc;
        }
        //파란 구슬 굴리기
        for(i=br+1; i<g_N; i++) {
            if(g_table[i][bc] == -1) {  //벽
                break;
            } else if(i == nextrr && bc == nextrc) { //빨간구슬위치
                break;
            } else if(g_table[i][bc] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = i-1;
            nextbc = bc;
        }
    } else {    //파란 구슬부터
        //파란 구슬 굴리기
        for(i=br+1; i<g_N; i++) {
            if(g_table[i][bc] == -1) {  //벽
                break;
            } else if(g_table[i][bc] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = i-1;
            nextbc = bc;
        }
        //빨간 구슬 굴리기
        for(i=rr+1; i<g_N; i++) {
            if(g_table[i][rc] == -1) {   //벽
                break;
            } else if(i == nextbr && rc == nextbc) { //파란 구슬 위치
                break;
            } else if(g_table[i][rc] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = i-1;
            nextrc = rc;
        }
    }
    
    if(blueFlag == 0 && redFlag == 1) {   //빨간거만 빠졋으면
        if(g_redCnt > cnt) { g_redCnt = cnt;}
    } else if(redFlag + blueFlag == 0 ){   //둘다 안빠졌으면
        dfs_moving(nextrr, nextrc, nextbr, nextbc, cnt+1);
    }
    //end 아래로 굴리기
    //왼쪽으로 굴리기
    redFlag = blueFlag = 0;
    if(rc < bc) {
        //빨간 구슬 굴리고
        for(j=rc-1; j>=0; j--) {
            if(g_table[rr][j] == -1) {   //벽
                break;
            } else if(g_table[rr][j] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = rr;
            nextrc = j+1;
        }
        //파란 구슬 굴리기
        for(j=bc-1; j>=0; j--)  {
            if(g_table[br][j] == -1) {
                break;
            } else if(br == nextrr && j == nextrc) { //빨간구슬위치
                break;
            } else if(g_table[br][j] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = br;
            nextbc = j+1;
        }
    } else {    //파란 구슬부터
        //파란 구슬 굴리기
        for(j=bc-1; j>=0; j--)  {
            if(g_table[br][j] == -1) {
                break;
            } else if(g_table[br][j] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = br;
            nextbc = j+1;
        }
        //빨간 구슬 굴리고
        for(j=rc-1; j>=0; j--) {
            if(g_table[rr][j] == -1) {   //벽
                break;
            } else if(nextbr == rr && nextbc == j) {
                break;
            } else if(g_table[rr][j] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = rr;
            nextrc = j+1;
        }
    }
    if(blueFlag == 0 && redFlag == 1) {   //빨간거만 빠졋으면
        if(g_redCnt > cnt) { g_redCnt = cnt;}
    } else if(redFlag + blueFlag == 0 ){   //둘다 안빠졌으면
        dfs_moving(nextrr, nextrc, nextbr, nextbc, cnt+1);
    }
    //end 왼쪽으로 굴리기
    //오른쪽 굴리기
    redFlag = blueFlag = 0;
    if(rc > bc) {
        //빨간 구슬 굴리고
        for(j=rc+1; j<g_M; j++) {
            if(g_table[rr][j] == -1) {   //벽
                break;
            } else if(g_table[rr][j] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = rr;
            nextrc = j-1;
        }
        //파란 구슬 굴리기
        for(j=bc+1; j<g_M; j++)  {
            if(g_table[br][j] == -1) {
                break;
            } else if(br == nextrr && j == nextrc) { //빨간구슬위치
                break;
            } else if(g_table[br][j] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = br;
            nextbc = j-1;
        }
    } else {    //파란 구슬부터
        //파란 구슬 굴리기
        for(j=bc+1; j<g_M; j++) {
            if(g_table[br][j] == -1) {
                break;
            } else if(g_table[br][j] == 1) {    //구멍
                blueFlag = 1;   break;
            }
        }
        if(blueFlag == 1) {
            nextbr = nextbc = 0;
        } else {
            nextbr = br;
            nextbc = j-1;
        }
        //빨간 구슬 굴리고
        for(j=rc+1; j<g_M; j++) {
            if(g_table[rr][j] == -1) {   //벽
                break;
            } else if(nextbr == rr && nextbc == j) {
                break;
            } else if(g_table[rr][j] == 1) { //구멍
                redFlag = 1;
                break;
            }
        }
        if(redFlag == 1) {
            nextrr = nextrc = 0;
        } else {
            nextrr = rr;
            nextrc = j-1;
        }
    }
    if(blueFlag == 0 && redFlag == 1) {   //빨간거만 빠졋으면
        if(g_redCnt > cnt) { g_redCnt = cnt;}
    } else if(redFlag + blueFlag == 0 ){   //둘다 안빠졌으면
        dfs_moving(nextrr, nextrc, nextbr, nextbc, cnt+1);
    }
    //end 오른쪽 굴리기
}

int main(void) {
    char tempStr[13];
    int rr, rc, br, bc;
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
                rr = i;
                rc = j;
            } else if(tempStr[j] == 'B'){
                br = i;
                bc = j;
            } else {
                g_table[i][j] = 1;
            }
        }
    }
    
    dfs_moving(rr, rc, br, bc, 1);

    if(g_redCnt == 987987987) {
        printf("-1");
    } else {
        printf("%d", g_redCnt);
    }
    
    return 0;
}
