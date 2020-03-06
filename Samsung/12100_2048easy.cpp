//
//  12100_2048easy.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/05.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****

#include <cstdio>
using namespace std;

int table[21][21] = {0, };
int maxNum = 0;
int N;

/// 위로 올릴때
/// @param flag table[row][col]의 값이 이미 합쳐져서 변경되었으면 1, 변경된 적 없으면 0
/// @param row 기준 원소의 행
/// @param col 기준 원소의 열
void simul_up(int flag, int row, int col) {
    int i;
    int num;
    
    num = table[row][col];
    
    for(i=row+1; i<N; i++) {    //기준원소 아래로 확인
        if(table[i][col] != 0) {    //빈곳이 아니면
            if(num != table[i][col]) {  //값이 다르면 위치만 변경하고 다음 시뮬
                table[row+1][col] = table[i][col];
                if(i != row+1) {
                    table[i][col] = 0;
                }
                simul_up(0, row+1, col);
            } else {    //값이 같으면 이미 값이 변경된것인지 아닌지에 따라 결정
                if(flag == 0) { //table[row][col]의 값이 변경된 적 없으면
                    table[row][col] = num*2;
                    if(i != row) {
                        table[i][col] = 0;
                    }
                    simul_up(1, row, col);
                } else {    //table[row][col]의 값이 변경된 적 있으면
                    table[row+1][col] = table[i][col];  //위치만 변경
                    if(i != row+1) {
                        table[i][col] = 0;
                    }
                    simul_up(0, row+1, col);
                }
            }
            break;  //필수
        }
    }
}

/// 아래로 내릴 때
/// @param flag table[row][col]의 값이 이미 합쳐져서 변경되었으면 1, 변경된 적 없으면 0
/// @param row 기준 원소의 행
/// @param col 기준 원소의 열
void simul_down(int flag, int row, int col) {
    int i;
    int num = table[row][col];
    
    for(i=row-1; i>=0; i--) {   //기준원소 위로 확인
        if(table[i][col] != 0) {    //빈곳이 아니면
            if(num != table[i][col]) {  //같은 값이 아니면 자리만 변경하고 재귀
                table[row-1][col] = table[i][col];
                if(i != row-1) {
                    table[i][col] = 0;
                }
                simul_down(0, row-1, col);
            } else {    //값이 같으면
                if(flag == 0) { //변경된 적 없으면
                    table[row][col] = num*2;
                    if(i != row) {
                        table[i][col] = 0;
                    }
                    simul_down(1, row, col);
                } else {    //변경된 적 있으면
                    table[row-1][col] = table[i][col];
                    if(i != row-1) {
                        table[i][col] = 0;
                    }
                    simul_down(0, row-1, col);
                }
            }
            
            break;  //필수
        }
    }
}

/// 왼쪽으로 스윕
/// @param flag table[row][col]의 값이 이미 합쳐져서 변경되었으면 1, 변경된 적 없으면 0
/// @param row 기준 원소의 행
/// @param col 기준 원소의 열
void simul_left(int flag, int row, int col) {
    int j;
    int num = table[row][col];
    
    for(j=col+1; j<N; j++) {
        if(table[row][j] != 0) {    //빈곳이 아니면
            if(num != table[row][j]) {  //값이 다르면 자리만 변경
                table[row][col+1] = table[row][j];
                if(j != col+1) {
                    table[row][j] = 0;
                }
                simul_left(0, row, col+1);
            } else {    //값이 같으면
                if(flag == 0) { //변경되지 않은 값이면
                    table[row][col] = num*2;
                    if(col != j) {
                        table[row][j] = 0;
                    }
                    simul_left(1, row, col);
                } else {    //변경된 값이면 자리만
                    table[row][col+1] = table[row][j];
                    if(j != col+1) {
                        table[row][j] = 0;
                    }
                    simul_left(0, row, col+1);
                }
            }
            break;  //필수
        }
    }
}

/// 오른쪽으로 스윕
/// @param flag table[row][col]의 값이 이미 합쳐져서 변경되었으면 1, 변경된 적 없으면 0
/// @param row 기준 원소의 행
/// @param col 기준 원소의 열
void simul_right(int flag, int row, int col) {
    int j;
    int num = table[row][col];
    
    for(j=col-1; j>=0; j--) {
        if(table[row][j] != 0) {    //빈곳이 아니면
            if(num != table[row][j]) {  //값이 다르면 자리만 변경
                table[row][col-1] = table[row][j];
                if(j != col-1) {
                    table[row][j] = 0;
                }
                simul_right(0, row, col-1);
            } else {    //값이 같으면
                if(flag == 0) { //변경되지 않은 값이면
                    table[row][col] = num*2;
                    if(col != j) {
                        table[row][j] = 0;
                    }
                    simul_right(1, row, col);
                } else {    //변경된 값이면 자리만
                    table[row][col-1] = table[row][j];
                    if(j != col-1) {
                        table[row][j] = 0;
                    }
                    simul_right(0, row, col-1);
                }
            }
            break;  //필수
        }
    }
}

/// 5번 움직여서 최대 값을 알아낸다
/// @param cnt 현재까지 몇번 움직였는지 카운팅
void simul(int cnt) {
    int temp_table[21][21] = {0, };
    int i, j;
    
    if(cnt == 5) {
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(table[i][j] > maxNum) {
                    maxNum = table[i][j];
                }
            }
        }
        return;
    } else {    //재귀
        //원래 모양을 저장
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                temp_table[i][j] = table[i][j];
            }
        }
        //end 원래 모양 저장
        
        //위로 움직이는 시뮬레이션 함수 호출하고 +  재귀 + 원상복구
        for(j=0; j<N; j++) {    //각 열마다 첫번째로 빈칸이 아닌 숫자를 찾아서 재귀호출한다
            if(table[0][j] != 0) {
                simul_up(0, 0, j);
            } else {
                for(i=1; i<N; i++) {
                    if(table[i][j] != 0) {
                        table[0][j] = table[i][j];
                        table[i][j] = 0;
                        simul_up(0, 0, j);
                        break;
                    }
                }
            }
        }
        simul(cnt+1);
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                table[i][j] = temp_table[i][j];
            }
        }
        //end 위로 움직이는 시뮬레이션 함수 호출하고 +  재귀 + 원상복구
        
        //아래로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구
        for(j=0; j<N; j++) {    //각 열마다 첫번째 숫자를 찾아서 재귀호출한다
            if(table[N-1][j] != 0) {
                simul_down(0, N-1, j);
            } else {
                for(i=N-2; i>=0; i--) {
                    if(table[i][j] != 0) {
                        table[N-1][j] = table[i][j];
                        table[i][j] = 0;
                        simul_down(0, N-1, j);
                        break;
                    }
                }
            }
        }
        simul(cnt+1);
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                table[i][j] = temp_table[i][j];
            }
        }
        //end 아래로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구
        
        //왼쪽으로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구
        for(i=0; i<N; i++) {    //각 행마다 첫번째 숫자를 찾아서 재귀호출
            if(table[i][0] != 0) {
                simul_left(0, i, 0);
            } else {
                for(j=1; j<N; j++) {
                    if(table[i][j] != 0) {
                        table[i][0] = table[i][j];
                        table[i][j] = 0;
                        simul_left(0, i, 0);
                        break;
                    }
                }
            }
        }
        simul(cnt+1);
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                table[i][j] = temp_table[i][j];
            }
        }
        //end 왼쪽으로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구
        
        //오른쪽으로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구
        for(i=0; i<N; i++) {    //각 행마다 첫번째 숫자를 찾아서 재귀호출
            if(table[i][N-1] != 0) {
                simul_right(0, i, N-1);
            } else {
                for(j=N-2; j>=0; j--) {
                    if(table[i][j] != 0) {
                        table[i][N-1] = table[i][j];
                        table[i][j] = 0;
                        simul_right(0, i, N-1);
                        break;
                    }
                }
            }
        }
        simul(cnt+1);
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                table[i][j] = temp_table[i][j];
            }
        }
        //end 오른쪽으로 움직이는 시뮬레이션 함수 호출 + 재귀 + 원상복구

    }//재귀
}

int main(void) {
    int i, j;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    simul(0);

    
    printf("%d", maxNum);
    
    return 0;
}
