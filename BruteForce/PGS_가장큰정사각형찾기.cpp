//
//  PGS_가장큰정사각형찾기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/19.
//  Copyright © 2019 송혜경. All rights reserved.
//  문제 *****

/* 처음 계속 정확성이 틀린 이유는
 1 1 1 1
 1 1 1 0
 1 1 1 0
 0 0 0 0
 
 과 같은 경우를 고려하지 않았기 때문
 
 
 */

#include <iostream>
#include<vector>
using namespace std;

int solution(vector<vector<int>> board) {
    int T[1002][1002] = {0, };
    int answer = 0;
    int cnt = 0;
    int tempLen = 0;
    int maxLen = 0; int flag = 0;
    int row, col, r, c;
    int i, j, k;
    
    row = board.size();
    col = board[0].size();
    
    for(i=0; i<row; i++) {
        cnt = 0;
        for(j=col-1; j>=0; j--) {
            if(board[i][j] == 0) {
                cnt = 0;
                continue;
            } else {
                cnt += 1;
                T[i][j] = cnt;
            }
        }
    }
    
    for(i=0; i<row; i++) {
        for(j=0; j<col; j++) {
            if(board[i][j] == 0) {
                continue;
            } else {
                if(T[i][j] > maxLen) {  //maxLen보다 더 길면 확인해봄

                    tempLen = T[i][j];
                    //범위보다 더 크면 tempLen 줄이기
                    while(i + tempLen - 1 >= row) {
                        tempLen -= 1;
                    }
                    
                    if(tempLen > maxLen) {
                        
                        for(r=i+tempLen-1; r>=i; r--) { //효율성을 위해 T값을 기준으로 각 행의 가장 첫번째 요소 값만 확인한다
                            if(T[r][j] < tempLen) {
                                tempLen = r-i;
                            }
                            if(tempLen <= maxLen) {
                                break;
                            }
                        }

                        if(tempLen > maxLen) {
                            maxLen = tempLen;
                            answer = maxLen * maxLen;
                        }
                    }

                }   //end if(T[i][j] > maxLen)
                
            }
        }
    }
    
    
    return answer;
}
