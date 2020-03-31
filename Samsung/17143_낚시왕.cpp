//
//  17143_낚시왕.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/31.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***** (1h 50min)

#include <cstdio>
#include <vector>
using namespace std;

typedef struct Shark {
    int row;
    int col;
    int s;  //속력
    int d;  //방향(1:위, 2:아래, 3:오, 4:왼)
    int z;  //상어 크기
    int liveFlag;   //살아있으면0, 죽으면 1
}Shark;

Shark shark[10003]; //인덱스 1부터 사용. 상어의 인덱스가 상어의 번호가 된다
int sharkTable[102][102] = {0,};    //상어의 위치 저장
int tempSharkTable[102][102] = {0, };
int M;   //상어의 수 저장
int R, C;
int person = 0; //사람 위치 저장
int sharkSum = 0;   //잡은 상어 크기 누적

/// 가로로 움직이는 상어에 대해 마지막 위치를 구한다
/// @param sharkNum 움직일 상어 번호
/// @param num 상어가 움직일 칸의 개수
void move_right_left(int sharkNum, int num) {
    int dir = shark[sharkNum].d;    //처음 방향
    int div = 0;
    int col = 0;
    int r = 0;
    
    if(num == 1) {
        div = 0;
    } else {
        div = (num - 1) / (C-1);
    }
    
    if(div % 2 != 0) {  //홀수
        //방향 바꿔준다
        if(dir == 3) {
            shark[sharkNum].d = 4;
        } else {
            shark[sharkNum].d = 3;
        }
    }
    
    r = num % (C-1);
    if(shark[sharkNum].d == 3) {    //마지막 방향이 오른쪽이면
        if(r == 0) {
            col = C;
        } else {
            col = 1 + r;
        }
    } else {    //마지막 방향이 왼쪽이면
        if(r == 0) {
            col = 1;
        } else {
            col = C - r;
        }
    }
    
    //상어 구조체 열 위치 업데이트
    shark[sharkNum].col = col;
}

/// 위아래로 움직이는 상어의 최종 위치를 구한다
/// @param sharkNum 움직일 상어 번호
/// @param num 상어가 움직일 칸의 개수
void move_up_down(int sharkNum, int num) {
    int dir = shark[sharkNum].d;    //처음 방향
    int div = 0;
    int row = 0;
    int r = 0;
    
    if(num == 1) {
        div = 0;
    } else {
        div = (num - 1) / (R-1);
    }
    
    if(div % 2 != 0) {  //홀수
        //방향 바꿔준다
        if(dir == 1) {
            shark[sharkNum].d = 2;
        } else {
            shark[sharkNum].d = 1;
        }
    }
    
    r = num % (R-1);
    if(shark[sharkNum].d == 1) {    //마지막 방향이 위쪽이면
        if(r == 0) {
            row = 1;
        } else {
            row = R - r;
        }
    } else {    //마지막 방향이 아래쪽이면
        if(r == 0) {
            row = R;
        } else {
            row = 1 + r;
        }
    }
    
    //상어 구조체 열 위치 업데이트
    shark[sharkNum].row = row;
}

void simul(void) {
    int row = 0;    int col = 0;    int num = 0;    int dir = 0;
    int sameSharkNum = 0;
    int i, j;
    
    //오른쪽으로 사람 이동
    person += 1;
    
    //종료
    if(person > C) {
        return;
    }
    
    //가장 위에 있는 상어를 잡는다
    for(i=1; i<=R; i++) {
        if(sharkTable[i][person] > 0) { //상어가 있으면
            sharkSum += shark[(sharkTable[i][person])].z;   //잡은 상어의 크기 누적
            shark[(sharkTable[i][person])].liveFlag = 1;    //잡힌 상어(죽은상어) 표시
            sharkTable[i][person] = 0;  //잡은 상어이므로 테이블에서 지우기
            break;
        }
    }
    
    //상어들을 이동시킨다
    for(i=1; i<=M; i++) {
        if(shark[i].liveFlag == 0) {    //살아있는 상어면
            row = shark[i].row;
            col = shark[i].col;
            num = shark[i].s;   //총 움직일 칸의개수
            dir = shark[i].d;   //처음 방향
            
            //상어 이동시키기
            if(dir == 1) {  //위로 움직이는 상어
                if(row - num < 1) { //벽에 부딪히면
                    //아래로 방향 전환 시켜서 1행부터 이동하도록 한다
                    shark[i].d = 2;
                    num -= (row -1);
                    move_up_down(i, num);
                } else {
                    shark[i].row = row - num;
                }
            } else if(dir == 2) {   //아래로 움직이는 상어
                if(row + num > R) {
                    //위로 방향 전환 시켜서 R행부터 이동하도록 한다
                    shark[i].d = 1;
                    num -= (R - row);
                    move_up_down(i, num);
                } else {
                    shark[i].row = row + num;
                }
            } else if(dir == 3) {   //오른쪽으로 움직이는 상어
                //벽에 부딪히는지 확인
                if(col + num > C) {
                    //왼쪽으로 방향 전환시켜서 C열부터 이동하도록 한다
                    shark[i].d = 4;
                    num -= (C - col);
                    move_right_left(i, num);
                } else {
                    shark[i].col = col + num;
                }
            } else if(dir == 4) {   //왼쪽으로 이동하는 상어
                //벽에 부딪히는지 확인
                if(col - num < 1) {
                    //오른쪽으로 방향 전환 시켜서 1열부터 이동하도록 한다
                    shark[i].d = 3;
                    num -= (col - 1);
                    move_right_left(i, num);
                } else {
                    shark[i].col = col - num;
                }
            }
            //현재 상어 움직이기 끝
            
            //이동한 위치로 상어 번호 저장
            row = shark[i].row;
            col = shark[i].col;
            if(tempSharkTable[row][col] == 0) { //이동한 위치에 아무것도 없으면 상어의 번호로 최초 저장
                tempSharkTable[row][col] = i;
            } else {    //여러 상어가 위치하게 되면 큰 애로 남겨둔다
                sameSharkNum = tempSharkTable[row][col];
                if(shark[i].z > shark[sameSharkNum].z) {    //현재 상어가 더 크면 업데이트
                    tempSharkTable[row][col] = i;
                    shark[sameSharkNum].liveFlag = 1;   //이전 상어 죽음
                } else {    //원래 있던 상어가 더 크면
                    shark[i].liveFlag = 1;  //현재 상어 죽음
                }
            }
        }
        //end 살아있는 상어면
    }
    //end 상어 이동
    
    //sharkTable에 tempSharkTable 정보 저장 + tempSharkTable 초기화
    for(i=1; i<=R; i++) {
        for(j=1; j<=C; j++) {
            sharkTable[i][j] = tempSharkTable[i][j];
            tempSharkTable[i][j] = 0;
        }
    }
    
    //재귀호출
    simul();
}

int main(void) {
    int r, c, s, d, z;
    int i;
    
    scanf("%d %d %d", &R, &C, &M);
    
    for(i=1; i<=M; i++) {
        scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
        //상어 초기화
        shark[i].row = r;
        shark[i].col = c;
        shark[i].s = s;
        shark[i].d = d;
        shark[i].z = z;
        shark[i].liveFlag = 0;
        sharkTable[r][c] = i;
    }
    
    simul();
    
    printf("%d", sharkSum);
    
    return 0;
}
