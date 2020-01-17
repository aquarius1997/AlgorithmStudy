//
//  3009_네번째점.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/11.
//  Copyright © 2020 송혜경. All rights reserved.
// **

#include <stdio.h>

int main(void) {
    int x1, x2;
    int y1, y2;
    int i, j;
    int x, y;
    int resultX, resultY;
    int xCnt, yCnt;

    xCnt = yCnt = x1 = x2 = y1 = y2 = 0;
    
    
    for(i=0; i<3; i++) {
        scanf("%d %d", &x, &y);

        if(xCnt == 0) {
            x1 = x; xCnt++;
        } else if(xCnt == 1) {
            if(x1 != x) {
                x2 = x;
            }
            xCnt++;
            
        } else if(xCnt == 2) {
            if(x2 == 0) {
                resultX = x;
            } else {
                if(x == x1) {
                    resultX = x2;
                } else {
                    resultX = x1;
                }
            }
        }
        
        if(yCnt == 0) {
            y1 = y; yCnt++;
        } else if(yCnt == 1) {
            if(y1 != y) {
                y2 = y;
            }
            yCnt++;
        } else if(yCnt == 2) {
            if(y2 == 0) {
                resultY = y;
            } else {
                if(y == y1) {
                    resultY = y2;
                } else {
                    resultY = y1;
                }
            }
        }
                
    }
    
    printf("%d %d", resultX, resultY);
    
    return 0;
}
