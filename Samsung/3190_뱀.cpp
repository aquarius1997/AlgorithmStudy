//
//  3190_뱀.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/05.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
#include <queue>
using namespace std;

typedef struct SnakeHead {
    int row;
    int col;
    int dir;    //현재 뱀의 이동 방향 (1 : 상, 2: 하, 3:좌, 4:우)
}SnakeHead;   //뱀의 머리가 위치한 정보를 저장

queue<int> times;   //뱀 이동에 따라 시간, 방향변경 정보를 저장한다
int apple[102][102] = {0, };    //사과가 있으면 1
SnakeHead head;
int endTime;
int N;

/// timeCnt + 1 시간의 실행을 돌린다
/// @param timeCnt 뱀이 현재까지 이동해온 시간
void simul(queue<int> snake, int timeCnt) {
    queue<int> tempSnake;
    int lr, r, c;
    
    //방향 변경이 있을 경우 머리의 방향을 바꾼다
    if(!times.empty()) {
        if(times.front() == (timeCnt)) {
            times.pop();    //시간은 빼기
            lr = times.front();  //머리 바꾸는 방향알아내기
            times.pop();
            if(head.dir == 1) { //위로 움직이고 있었을 경우
                if(lr == 1) {   //왼틂
                    head.dir = 3;
                } else {
                    head.dir = 4;
                }
            } else if(head.dir == 2) {  //아래로 움직이고 있었을 경우
                if(lr == 1) {
                    head.dir = 4;
                } else {
                    head.dir = 3;
                }
            } else if(head.dir == 3) {  //왼쪽으로 움직이고 있었을 경우
                if(lr == 1) {
                    head.dir = 2;
                } else {
                    head.dir = 1;
                }
            } else {    //오른쪽으로 움직이고 잇엇을 경우
                if(lr == 1) {
                    head.dir = 1;
                } else {
                    head.dir = 2;
                }
            }
        }
    }

    if(head.dir == 1) {    //위로 이동
        head.row = head.row - 1;
    } else if(head.dir == 2) {  //아래 이동
        head.row = head.row + 1;
    } else if(head.dir == 3) {  //왼족 이동
        head.col = head.col - 1;
    } else {    //오른쪽
        head.col = head.col + 1;
    }
    
    if(head.row <= 0 || head.row > N || head.col <= 0 || head.col > N) {    //벽에 부딪히면 죽음
        endTime = timeCnt + 1;
        return;
    }
    
    //뱀의 머리가 몸과 만나는지 확인한다
    while(!snake.empty()) {
        r = snake.front();  snake.pop();
        c = snake.front();  snake.pop();
        if(r == head.row && c == head.col) {    //몸과 머리가 만나면 죽음
            endTime = timeCnt + 1;
            return;
        }
        tempSnake.push(r);  tempSnake.push(c);
    }
    
    
    //이동한 좌표가 사과가 없는 자리면 큐를 팝해서 이전 위치를 없앤다
    if(apple[head.row][head.col] == 0) {    //사과가 없으면
        tempSnake.pop();
        tempSnake.pop();
    } else {    //사과없어져 ㅠㅠ 이거 고려안했어
        apple[head.row][head.col] = 0;
    }
    
    //이동한 후 뱀의 머리의 위치를 푸시한다
    tempSnake.push(head.row);
    tempSnake.push(head.col);
    

    simul(tempSnake, timeCnt+1);
}


int main(void) {
    queue<int> snake;   //뱀이 위치한 좌표
    int K, row, col, L, time;
    char dir;
    int i;
    
    scanf("%d", &N);
    
    scanf("%d", &K);
    for(i=0; i<K; i++) {    //사과 위치 저장
        scanf("%d %d", &row, &col);
        apple[row][col] = 1;
    }
    
    scanf("%d", &L);
    for(i=0; i<L; i++) {
        scanf("%d %c", &time, &dir);
        times.push(time);
        if(dir == 'L') {    //왼쪽은 1
            times.push(1);
        } else {    //오른쪽은 2
            times.push(2);
        }
    }
    
    head.row = 1;
    head.col = 1;
    head.dir = 4;
    snake.push(1);  snake.push(1);
    
    simul(snake, 0);
    
    printf("%d", endTime);
    
    return 0;
}

