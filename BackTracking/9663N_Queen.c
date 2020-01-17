//
//  9663N_Queen.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/02.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <stdio.h>

typedef struct StackType {
    int top;
    int stack[1000][2];
} StackType;

int N;
StackType s;    // 판에 놓여진 퀸들의 정보를 저장한다
int cnt;    //퀸을 놓을 수 있는 경우의 수

/*
 퀸을 놓고, 다음 퀸을 놓을 수 있는 자리인지 확인한 이후에 놓을 수 있으면 재귀호출한다
 row : 퀸을 놓을 행
 col : 퀸을 놓을 열
 num : 함수를 호출했을 경우 퀸이 놓일 개수
 */
void queens(int row, int col, int num) {
    int r, c;
    int i, j;
    int flag = 0;
    
    if(num == N) {  //N개의 퀸을 모두 놓은 경우
        cnt += 1;   //카운트
    } else {
        //퀸을 놓는다 -> 놓은 자리 정보를 스택에 삽입
        s.top += 1;
        s.stack[s.top][0] = row;
        s.stack[s.top][1] = col;
        for(j=0; j<N; j++) {    //다음 행에서 T[row+1][j]에 퀸을 놓을 수 있는지 확인하고 재귀호출한다
            flag = 0;   //퀸을 놓을 수 있는지 없는지에 대한 정보를 저장
            
            for(i=s.top; i>=0; i--) {   //이미 놓은 퀸들의 위치 정보를 기반으로 확인
                r = s.stack[i][0];
                c = s.stack[i][1];
                
                if(j == c) {    //같은 열에 존재하면
                    flag = 1;
                    break;
                } else if(j > c) {  //왼쪽(위) 대각선상에 퀸이 이미 존재하면
                    if((row+1 - r) == (j - c)) {
                        flag = 1;
                        break;
                    }
                } else {    //오른쪽(위) 대각선상에 퀸이 이미 존재하면
                    if((row+1 - r) == (c - j)) {
                        flag = 1;
                        break;
                    }
                }
            }   //end for(이미 놓은 퀸들의 위치 정보를 기반으로 확인)
            
            if(flag == 0) { //놓을 수 있는 자리이면 해당 자리에 대해 재귀호출한다
                queens(row+1, j, num+1);
            }
        }
        
        //놓았던 퀸을 빼서 다른 경우의 수를 파악한다
        s.top -= 1;
    }
}

int main(void) {
    int j;
        
    scanf("%d", &N);
    
    //스택 초기화
    s.top = -1;
    
    cnt = 0;
    
    for(j=0; j<N; j++) {
        queens(0, j, 1);
    }
    
    printf("%d", cnt);
    
    return 0;
}
