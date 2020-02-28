//
//  벽돌깨기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/02/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
#define MAXN    987987987

using namespace std;

int bricks[20][20] = {0,};
int N, W, H;
int minBrickNum;


/// 벽돌을 연쇄적으로 부신다
/// @param row 부셔야 하는 벽돌의 행 정보
/// @param col 부셔야 하는 벽돌의 열 정보
void breakContinuous(int row, int col) {
    int i, j;
    int distance;
    
    //상하좌우 부셔야 하는 벽돌의 수
    distance = bricks[row][col] - 1;
    
    bricks[row][col] = 0;
    //상
    for(i=row-1; (i>=row-distance && i>=0); i--) {
        if(bricks[i][col] != 0) {
            breakContinuous(i, col);
            bricks[i][col] = 0;
        }
    }
    //하
    for(i=row+1; (i<=row+distance && i<H); i++) {
        if(bricks[i][col] != 0) {
            breakContinuous(i, col);
            bricks[i][col] = 0;
        }
    }
    //좌
    for(j=col-1; (j>=0 && j>=col-distance); j--) {
        if(bricks[row][j] != 0) {
            breakContinuous(row, j);
            bricks[row][j] = 0;
        }
    }
    //우
    for(j=col+1; (j<W && j<=col+distance); j++) {
        if(bricks[row][j] != 0) {
            breakContinuous(row, j);
            bricks[row][j] = 0;
        }
    }

}

/// 벽돌 사이의 빈칸을 없앤다
void makeClean(void) {
    int i, j, k;
    int cnt = 0;
    int idx;
    
    for(j=0; j<W; j++) {
        idx = H-1;
        cnt = 0;
        
        for(i=H-1; i>=0;) {
            if(bricks[i][j] == 0) {
                cnt++;
                i--;
            } else {
                if(cnt > 0) {
                    for(k=i; k>=0; k--) {
                        bricks[k+cnt][j] = bricks[k][j];
                    }
                    for(k=0; k<cnt; k++) {
                        bricks[k][j] = 0;
                    }
                }
                i = i+cnt-1;
                cnt = 0;
            }
        }
    }
}


/// 벽돌을 부시는 함수 (구슬을 맞은 벽돌에 대해 연쇄적으로 벽돌을 부시는 함수를 호출한다)
/// @param cnt 여태까지 구슬을 던진 횟수
void breakingBrick(int cnt) {
    int tempBricks[20][20] = {0, };
    int bricksNum = 0;
    int i, j;
    
    if(cnt == N) {  //N개의 구슬을 모두 던졌으면 남은 벽돌 수가 최소인지 알아내고 종료
        for(i=0; i<H; i++) {
            for(j=0; j<W; j++) {
                if(bricks[i][j] != 0) {
                    bricksNum++;
                }
            }
        }
        if(bricksNum < minBrickNum) {
            minBrickNum = bricksNum;
        }
    } else {
        
        for(i=0; i<H; i++) {    //이전까지의 벽돌 정보 임시 저장
            for(j=0; j<W; j++) {
                tempBricks[i][j] = bricks[i][j];
            }
        }
        
        //만일 빈 열이 아니면 해당 벽돌을 부신다
        for(j=0; j<W; j++) {
            for(i=0; i<H; i++) {
                if(bricks[i][j] != 0) {
                    breakContinuous(i, j);
                    makeClean();
                    breakingBrick(cnt+1);
                    
                    
                    for(int l=0; l<H; l++) {    //원래 벽돌 정보로 저장
                        for(int ll=0; ll<W; ll++) {
                            bricks[l][ll] = tempBricks[l][ll];
                        }
                    }
                    break;  //다음 열에 대해 탐색
                }   //end if(bricks[i][j] != 0)
            }
        }
    }
    

}
int main(void) {
    int T, t;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        scanf("%d %d %d", &N, &W, &H);
        
        for(i=0; i<H; i++) {    //입력
            for(j=0; j<W; j++) {
                scanf("%d", &bricks[i][j]);
            }
        }
        
        
        
        minBrickNum = MAXN;
        
        breakingBrick(0);

        if(minBrickNum == MAXN) {
            minBrickNum = 0;
        }
        printf("#%d %d\n", t, minBrickNum);
    }
    
    return 0;
}

