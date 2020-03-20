//
//  15683_감시.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/20.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <cstdio>
using namespace std;

int table[10][10] = {0, };
int N, M;
int minCnt = 987987987;

void find_other_cctv(int row, int col);

/// 왼쪽으로 감시하는 함수
/// @param row 기준 행
/// @param col 기준 열
void left_cctv(int row, int col) {
    for(int j=col-1; j>=0; j--) {
        if(table[row][j] == 6) {break;}
        if(table[row][j] == 0) {
            table[row][j] = -1;
        }
    }
}

/// 오른쪽으로 감시하는 함수
/// @param row 기준 행
/// @param col 기준 열
void right_cctv(int row, int col) {
    for(int j=col+1; j<M; j++) {
        if(table[row][j] == 6) {break;}
        if(table[row][j] == 0) {
            table[row][j] = -1;
        }
    }
}

/// 위쪽으로 감시하는 함수
/// @param row 기준 행
/// @param col 기준 열
void up_cctv(int row, int col) {
    for(int i=row-1; i>=0; i--) {
        if(table[i][col] == 6) {break;}
        if(table[i][col] == 0) {    //다른 CCTV는 통과하도록
            table[i][col] = -1;
        }
    }
}

/// 아래로 감시하는 함수
/// @param row 기준 행
/// @param col 기준 열
void down_cctv(int row, int col) {
    for(int i=row+1; i<N; i++) {
        if(table[i][col] == 6) {break;}
        if(table[i][col] == 0) {
            table[i][col] = -1;
        }
    }
}

/// from_table을 to_table로 복사
void copy_table(int from_table[10][10], int to_table[10][10]) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            to_table[i][j] = from_table[i][j];
        }
    }
}

/// 1번 CCTV를 가동시킨다
/// @param row 행
/// @param col 열
void cctv1(int row, int col) {
    int temp_table[10][10] = {0, };
    copy_table(table, temp_table);
    
    //위로 감시
    up_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //오른쪽감시
    right_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //아래 감시
    down_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);

    //왼쪽 감시
    left_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
}

/// 2번 CCTV 가동
/// @param row 행 위치
/// @param col 열 위치
void cctv2(int row, int col) {
    int temp_table[10][10] = {0, };
    copy_table(table, temp_table);

    //양옆으로 감시
    right_cctv(row, col);
    left_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //위아래로 감시
    up_cctv(row, col);
    down_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
}

/// 3번 CCTV 가동
/// @param row 행 위치
/// @param col 열 위치
void cctv3(int row, int col) {
    int temp_table[10][10] = {0, };
    copy_table(table, temp_table);
    
    //위+오른
    up_cctv(row, col);
    right_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //오른+아래
    right_cctv(row, col);
    down_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //아래+왼
    down_cctv(row, col);
    left_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //왼+위
    left_cctv(row, col);
    up_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
}

/// 4번 CCTV 가동
/// @param row 행 위치
/// @param col 열 위치
void cctv4(int row, int col) {
    int temp_table[10][10] = {0, };
    copy_table(table, temp_table);
    
    //왼+위+오른
    left_cctv(row, col);
    up_cctv(row, col);
    right_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //위+오른+아래
    up_cctv(row, col);
    right_cctv(row, col);
    down_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //오른+아래+왼
    right_cctv(row, col);
    down_cctv(row, col);
    left_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
    
    //아래+왼+위
    down_cctv(row, col);
    left_cctv(row, col);
    up_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
}

/// 5번 CCTV 가동
/// @param row 행 위치
/// @param col 열 위치
void cctv5(int row, int col) {
    int temp_table[10][10] = {0, };
    copy_table(table, temp_table);

    up_cctv(row, col);
    right_cctv(row, col);
    down_cctv(row, col);
    left_cctv(row, col);
    find_other_cctv(row, col);
    copy_table(temp_table, table);
}

/// CCTV 번호에 따른 함수를 호출한다
/// @param cctvNum CCTV 종류(번호)
/// @param row CCTV 위치 행 정보
/// @param col CCTV 위치 열 정보
void call_cctv_function(int cctvNum, int row, int col) {
    if(cctvNum == 1) {
        cctv1(row, col);
    } else if(cctvNum == 2) {
        cctv2(row, col);
    } else if(cctvNum == 3) {
        cctv3(row, col);
    } else if(cctvNum == 4) {
        cctv4(row, col);
    } else {
        cctv5(row, col);
    }
}

/// 이전에 가동시킨 CCTV 이외의 다른 CCTV들이 있는지 확인한다
/// @param row 직전에 구동시킨 CCTV 행 정보
/// @param col 직전에 구동시킨 CCTV 열 정보
void find_other_cctv(int row, int col) {
    int flag = 0;   //남은 CCTV 한개도 없으면
    int cnt = 0;
    
    for(int j=col+1; j<M; j++) {
        if(table[row][j] >=1 && table[row][j] <= 5) {
            int cctvNum = table[row][j];
            flag = 1;
            call_cctv_function(cctvNum, row, j);
        }
    }
    for(int i=row+1; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(table[i][j] >=1 && table[i][j] <= 5) {
                int cctvNum = table[i][j];
                flag = 1;
                call_cctv_function(cctvNum, i, j);
            }
        }
    }
    
    //CCTV를 모두 가동시켰으면 사각지대의 숫자를 세서 최소 사각지대 개수로 업데이트 가능한지 확인한다
    if(flag == 0) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(table[i][j] == 0) {  //사각지대 세고
                    cnt++;
                }
            }
        }
        if(minCnt > cnt) {
            minCnt = cnt;
        }
    }
}


int main(void) {
    int flag = 0;
    scanf("%d %d", &N, &M);
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &table[i][j]);
        }
    }
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(table[i][j] >= 1 && table[i][j] <= 5) {
                int cctvNum = table[i][j];
                call_cctv_function(cctvNum, i, j);
                flag = 1;
                break;
            }
        }
        if(flag == 1) { break;}
    }
    
    if(flag == 0) { //CCTV가 없는 경우!! 중요
        minCnt = 0;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(table[i][j] == 0) {
                    minCnt++;
                }
            }
        }
    }
    
    printf("%d", minCnt);
    
    return 0;
}
