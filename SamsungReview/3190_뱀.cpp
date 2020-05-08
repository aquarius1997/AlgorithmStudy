//
//  3190_뱀.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/05/06.
//  Copyright © 2020 송혜경. All rights reserved.
// 1h1min 1Fail ( 변수 하나 잘못 저장함 개실수)

#include <cstdio>
#include <queue>
using namespace std;

//뱀이 방향을 변환하는 정보를 저장
typedef struct SnakeDir {
    int secs;
    int dir;    //1 : 왼쪽, 2: 오른쪽
}SnakeDir;
//뱀 몸의 위치를 저장
typedef struct Snake {
    int row;
    int col;
}Snake;

int g_table[102][102] ={0,};    //사과가 놓여있으면 1
int g_N = 0;
queue<SnakeDir> dirQueue;   //뱀이 방향을 전환하는 정보를 큐로 저장

int simul(void) {
    int timeCnt = 1;
    int snakeR, snakeC, dir; //뱀위치, 방향(1:상, 2:하, 3:좌, 4:우)
    int breakFlag = 0;
    Snake temp;
    SnakeDir snakeDir;
    queue<Snake> snake; //뱀의 몸 위치들을 큐로 저장 (큐 head : 뱀의 꼬리, rear : 뱀의 머리)
    queue<Snake> tempSnake; //뱀 몸에 부딪히는지 확인할 때 사용
    
    //현재 뱀 위치, 방향
    snakeR = snakeC = 1;
    dir = 4;    //올ㄴ쪽으로 이동중
    //뱀 몸 큐에 푸시
    Snake newSnake;
    newSnake.row = 1;
    newSnake.col = 1;
    snake.push(newSnake);
    
    //뱀을 움직인다
    while(true) {
        
        //이전시간이 끝나고 방향을 전환해야 하는지 확인한다
        snakeDir = dirQueue.front();
        if(snakeDir.secs == timeCnt-1) {  //방향전환해야함
            dirQueue.pop();
            if(dir == 1) {
                if(snakeDir.dir == 1) { dir = 3; }
                else { dir = 4; }
            } else if(dir == 2) {
                if(snakeDir.dir == 1) { dir = 4; }
                else { dir = 3; }
            } else if(dir == 3) {
                if(snakeDir.dir == 1) { dir = 2; }
                else { dir = 1; }
            } else {
                if(snakeDir.dir == 1) { dir = 1; }
                else { dir = 2;}
            }
        }
        
        if(dir == 1) {  //위로 움직이고 있을 때
            if(snakeR - 1 < 1) {   //다음 위치가 범위를 벗어나게 되면
                break;
            } else { //범위 안벗어나면
                snakeR -= 1;
            }
        } else if(dir == 2) {   //아래로 움직이고 있으 ㄹ때
            if(snakeR + 1 > g_N) { break; }
            else { snakeR += 1; }
        } else if(dir == 3) {   //왼쪽으로 움직이고 있을 때
            if(snakeC - 1 < 1) { break; }
            else { snakeC -= 1; }
        } else {    //오른쪽으로 움지깅고 잇을때
            if(snakeC + 1 > g_N) { break; }
            else { snakeC += 1; }
        } //오른쪽으로 움지깅고 잇을때
        
        //이동할 위치가 몸이랑 부딪히는지 확인하자
        while(!snake.empty()) {
            temp = snake.front();
            tempSnake.push(temp);   //임시 저장
            snake.pop();
            if(temp.row == snakeR && temp.col == snakeC) {  //몸이랑 부딪히게 됨
                breakFlag = 1;
                break;
            }
        }
        if(breakFlag == 1) { break; }   //몸이랑 부딪힘
        
        //몸이랑 부딪히지 않았으면 현재 위치를 몸 큐에 삽입하고
        while(!tempSnake.empty()) {
            temp = tempSnake.front();
            snake.push(temp);
            tempSnake.pop();
        }
        Snake newSnake2; //새로 이동할 위치를 저장할 변수 선언
        newSnake2.row = snakeR;
        newSnake2.col = snakeC;
        snake.push(newSnake2);
        //해당 위치에 사과가 잇으면 먹고
        if(g_table[snakeR][snakeC] == 1) {
            g_table[snakeR][snakeC] = 0;
        } else {    //사과가 없으면 선단을 잘라 원래 크기로 유지한다
            snake.pop();
        }
        
        //시간을 증가시킨다
        timeCnt++;
    }
        
    return timeCnt;
}

int main(void) {
    int K, L;
    char dir;
    int i, r, c, secs;
    int answer = 0;
    
    scanf("%d", &g_N);
    scanf("%d", &K);
    for(i=0; i<K; i++) {    //사과정보저장
        scanf("%d %d", &r, &c);
        g_table[r][c] = 1;
    }
    scanf("%d", &L);
    for(i=0; i<L; i++) {    //방향 변환 정보 저장
        scanf("%d %c", &secs, &dir);
        SnakeDir newSnakeDir;
        newSnakeDir.secs = secs;
        if(dir == 'L') {    //왼쪽
            newSnakeDir.dir = 1;
        } else {
            newSnakeDir.dir = 2;
        }
        dirQueue.push(newSnakeDir);
    }
    
    answer = simul();
    printf("%d", answer);
    
    return 0;
}
