//
//  모의ST_원자소멸시뮬레이션.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/16.
//  Copyright © 2020 송혜경. All rights reserved.
//  **** (종료조건 잘못 잡음)

#include <cstdio>
#include <queue>
using namespace std;

typedef struct Atom {
    int row;
    int col;
    int direc;  //0:상, 1:하, 2:좌, 3:우
    int energy;
    int dieFlag;    //살아있는 원자 : 0, 죽은 원자 : 1
}Atom;

int g_atomTable[2100][2100] = {0, };    //원자들의 위치를 원자 번호로 저장
Atom g_atoms[1010]; //원자들 저장 (인덱스 1부터 시작)
int g_N = 0;    //원자들의 수
int g_totalEnergy = 0;

void simul(void) {
    queue<int> dieAtoms;   //먼저 해당 자리에 위치한 죽을 원자번호
    int preAtomNum = 0; //먼저 해당 자리에 위치한 원자 번호
    int timeCnt = 0;
    int r, c;
    int i;
    
    while(timeCnt < 2020) { //0초 부터 2020초까지 원자들을 이동시킨다
        //1.살아있는 원자들에 대해 이동 이후 위치로 원자 구조체를 수정하면서 timeCnt+0.5초에 부딪힐 원자들을 같이 알아내서 처리한다
        for(i=1; i<=g_N; i++) {
            if(g_atoms[i].dieFlag == 0) {   //살아있는 원자들만
                if(g_atoms[i].direc == 0) { //위
                    r = g_atoms[i].row - 1;
                    c = g_atoms[i].col;
                    //원래 위치는 0으로 저장
                    g_atomTable[g_atoms[i].row][g_atoms[i].col] = 0;
                    if(r < 0) {//범위 밖으로 벗어나면 영원히 부딪힐 일 없으므로 죽은 원자로 처리
                        g_atoms[i].dieFlag = 1;
                    } else {    //범위 이내면
                        if(g_atomTable[r][c] != 0) {    //timeCnt + 0.5초에 부딙힐 원자이닞 확인
                            preAtomNum = g_atomTable[r][c];
                            if(g_atoms[preAtomNum].direc == 1) {    //둘이 부딪히면 둘다 죽은거 처리하고 계산
                                g_totalEnergy += (g_atoms[i].energy + g_atoms[preAtomNum].energy);
                                g_atomTable[r][c] = 0;
                                g_atoms[i].dieFlag = g_atoms[preAtomNum].dieFlag = 1;
                            }
                        }
                        g_atoms[i].row -= 1;
                    }
                } else if(g_atoms[i].direc == 1) { //아래
                    r = g_atoms[i].row + 1;
                    c = g_atoms[i].col;
                    //원래 위치는 0으로 저장
                    g_atomTable[g_atoms[i].row][g_atoms[i].col] = 0;
                    if(r > 2000) {
                        g_atoms[i].dieFlag = 1;
                    } else {
                        if(g_atomTable[r][c] != 0) {
                            preAtomNum = g_atomTable[r][c];
                            if(g_atoms[preAtomNum].direc == 0) {
                                g_totalEnergy += (g_atoms[i].energy + g_atoms[preAtomNum].energy);
                                g_atomTable[r][c] = 0;
                                g_atoms[i].dieFlag = g_atoms[preAtomNum].dieFlag = 1;
                            }
                        }
                        g_atoms[i].row += 1;
                    }
                } else if(g_atoms[i].direc == 2) { //왼
                    r = g_atoms[i].row;
                    c = g_atoms[i].col - 1;
                    //원래 위치는 0으로 저장
                    g_atomTable[g_atoms[i].row][g_atoms[i].col] = 0;
                    if(c < 0) {
                        g_atoms[i].dieFlag = 1;
                    } else {
                        if(g_atomTable[r][c] != 0) {
                            preAtomNum = g_atomTable[r][c];
                            if(g_atoms[preAtomNum].direc == 3) {
                                g_totalEnergy += (g_atoms[i].energy + g_atoms[preAtomNum].energy);
                                g_atomTable[r][c] = 0;
                                g_atoms[i].dieFlag = g_atoms[preAtomNum].dieFlag = 1;
                            }
                        }
                        g_atoms[i].col -= 1;
                    }
                } else {    //오
                    r = g_atoms[i].row;
                    c = g_atoms[i].col + 1;
                    //원래 위치는 0으로 저장
                    g_atomTable[g_atoms[i].row][g_atoms[i].col] = 0;
                    if(c > 2000) {
                        g_atoms[i].dieFlag = 1;
                    } else {
                        if(g_atomTable[r][c] != 0) {
                             preAtomNum = g_atomTable[r][c];
                             if(g_atoms[preAtomNum].direc == 2) {
                                 g_totalEnergy += (g_atoms[i].energy + g_atoms[preAtomNum].energy);
                                 g_atomTable[r][c] = 0;
                                 g_atoms[i].dieFlag = g_atoms[preAtomNum].dieFlag = 1;
                             }
                         }
                        g_atoms[i].col += 1;
                    }
                } //오른
            }//end 살아있는 원자들만
        }
        //end 1
        
        for(i=1; i<=4; i++) {
            printf("%d %d %d\n", g_atoms[i].row, g_atoms[i].col, g_atoms[i].dieFlag);
        }
        printf("\n");
        //2. timeCnt시간에 죽는 원자들 확인
        for(i=1; i<=g_N; i++) {
            if(g_atoms[i].dieFlag == 0) {
                r = g_atoms[i].row;
                c = g_atoms[i].col;
                if(g_atomTable[r][c] == 0) {    //빈칸
                    g_atomTable[r][c] = i;
                } else { //부딪칠 경우
                    preAtomNum = g_atomTable[r][c];
                    dieAtoms.push(preAtomNum);
                    //현재 원자만 죽은거 계산 + 에너지 계산
                    g_totalEnergy += g_atoms[i].energy;
                    g_atoms[i].dieFlag = 1;
                }
            } //dieFlag == 0
        }
        //end 2

        //2. 추가적으로 죽은거로 저장해야할 원자들 처리
        while(!dieAtoms.empty()) {
            preAtomNum = dieAtoms.front();
            dieAtoms.pop();
            if(g_atoms[preAtomNum].dieFlag == 0) {  //처리하지 않은 원자에 대해서만
                r = g_atoms[preAtomNum].row;
                c = g_atoms[preAtomNum].col;
                g_atomTable[r][c] = 0;
                g_atoms[preAtomNum].dieFlag = 1;
                g_totalEnergy += g_atoms[preAtomNum].energy;
            }
        }
        //end 2
        for(i=1; i<=4; i++) {
            printf("%d %d %d\n", g_atoms[i].row, g_atoms[i].col, g_atoms[i].dieFlag);
        }
        printf("\n");
        //3. 반복
        timeCnt += 1;
    }//end while(timeCnt < 1002)
}

int main(void) {
    int T, t;
    int x, y, energy, direc;
    int i, j;
    
    scanf("%d", &T);
    
    for(t=1; t<=T; t++) {
        //원자 정보 입력받기
        scanf("%d", &g_N);
        for(i=1; i<=g_N; i++) {
            scanf("%d %d %d %d", &x, &y, &direc, &energy);
            g_atoms[i].row = 1000 - y;
            g_atoms[i].col = 1000 + x;
            g_atoms[i].direc = direc;
            g_atoms[i].energy = energy;
            g_atoms[i].dieFlag = 0;
            g_atomTable[1000-y][1000+x] = i;    //원자 번호 저장
        }
        //시뮬레이션 실행
        simul();
        //정답출력
        printf("#%d %d\n", t, g_totalEnergy);
        //초기화
        g_totalEnergy = 0;
        for(i=0; i<2100; i++) {
            for(j=0; j<2100; j++) {
                g_atomTable[i][j] = 0;
            }
        }
    }
    
    return 0;
}
