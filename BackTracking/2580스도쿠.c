//
//  2580스도쿠.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/05.
//  Copyright © 2020 송혜경. All rights reserved.
//  *****

#include <stdio.h>

int T[9][9] = {0, };
int arr[83][2] = {0, }; //빈 칸의 좌표를 저장
int arrIdx = 0;
int endFlag = 0;

/*
 arr[fIdx]에 놓을 수 있는 숫자들을 알아내서, 숫자를 쓸 수 있으면 숫자를 저장한 다음에 재귀호출한다
 fIdx : 확인할 arr배열의 인덱스
 */
void sudoku(int fIdx) {
    int row, col;
    int flag = 0;
    int i, j, r, c, r2, c2;
    
    if(fIdx == arrIdx && endFlag == 0) {    //빈 칸을 모두 채웠으면
        for(i=0; i<9; i++) {
            for(j=0; j<9; j++) {
                printf("%d ", T[i][j]);
            }
            printf("\n");
        }
        endFlag = 1;
    } else {    //해당 빈 칸에 1~9까지 넣어본다
        //인자로 넘어온 빈칸의 행, 열 정보를 알아내고
        row = arr[fIdx][0];
        col = arr[fIdx][1];
        for(i=1; i<=9; i++) {
            flag = 0;
            for(j=0; j<9; j++) {    //행과 열에 숫자 i가 있는지 확인
                if(T[row][j] == i) {
                    flag = 1;   break;
                }
                if(T[j][col] == i) {
                    flag = 1;   break;
                }
            }   //end for(j)
            if(flag == 0) { //행 열에는 숫자 i가 없으면 3*3에도 없는지확인
                //확인을 시작할 행과 열의 위치를 알아낸다
                r = row/3;
                c = col/3;
                r = r*3;
                c = c*3;
                //3*3에 숫자 i를 가지고 있는지 확인
                for(r2=r; r2<r+3; r2++) {
                    for(c2=c; c2<c+3; c2++) {
                        if(T[r2][c2] == i) {
                            flag = 1;   break;
                        }
                    }
                    if(flag == 1) {
                        break;
                    }
                }   //end 3*3에 숫자 k를 가지고 있는지 확인
            }   //end if(flag==0)
            
            if(flag == 0) { //해당 빈칸에 숫자 i를 넣을 수 있으면
                T[row][col] = i;
                sudoku(fIdx+1);
                T[row][col] = 0;
            }
        }   //end for(i)
    }
}

int main(void) {
    int i, j;
    
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            scanf("%d", &T[i][j]);
            if(T[i][j] == 0) {  //빈 칸에 대하여 행과 열 정보를 저장한다 -> 이렇게 안하면 시간초과남!!!
                arr[arrIdx][0] = i;
                arr[arrIdx][1] = j;
                arrIdx++;
            }
        }
    }
    
    sudoku(0);
    
    return 0;
}
