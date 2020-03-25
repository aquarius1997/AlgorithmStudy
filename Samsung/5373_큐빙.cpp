//
//  5373_큐빙.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/23.
//  Copyright © 2020 송혜경. All rights reserved.
// 이거 뭔가 넘 코드가 긺... 영 찝찝함.,. 더 간단하게 풀 방법이 있을텐데 우선 나중에 수정하는걸로 패스

#include <cstdio>
using namespace std;

char back[3][3]; char left[3][3]; char up[3][3]; char right[3][3]; char front[3][3]; char down[3][3];
int tempTable[3][3];

void up_roate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = front[0][i]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = up[i][j];
        }
    }
    if(dir == 1) {  //시계방향
        for(int i=0; i<3; i++) { front[0][i] = right[2-i][0]; }
        for(int i=0; i<3; i++) { right[i][0] = back[2][i]; }
        for(int i=0; i<3; i++) { back[2][i] = left[2-i][2]; }
        for(int i=0; i<3; i++) { left[i][2] = temp[i]; }
        
        for(int i=0; i<3; i++) { up[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { up[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { up[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { up[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { front[0][i] = left[i][2]; }
        for(int i=0; i<3; i++) { left[i][2] = back[2][2-i]; }
        for(int i=0; i<3; i++) { back[2][i] = right[i][0]; }
        for(int i=0; i<3; i++) { right[i][0] = temp[2-i]; }
        
        for(int i=0; i<3; i++) { up[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { up[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { up[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { up[i][0] = tempTable[0][2-i]; }
    }
}

void back_rotate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = up[0][i]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = back[i][j];
        }
    }
    if(dir == 1) {
        for(int i=0; i<3; i++) { up[0][i] = right[0][i]; }
        for(int i=0; i<3; i++) { right[0][i] = down[2][2-i]; }
        for(int i=0; i<3; i++) { down[2][i] = left[0][2-i]; }
        for(int i=0; i<3; i++) { left[0][i] = temp[i]; }
        
        for(int i=0; i<3; i++) { back[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { back[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { back[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { back[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { up[0][i] = left[0][i]; }
        for(int i=0; i<3; i++) { left[0][i] = down[2][2-i]; }
        for(int i=0; i<3; i++) { down[2][i] = right[0][2-i]; }
        for(int i=0; i<3; i++) { right[0][i] = temp[i]; }
        
        for(int i=0; i<3; i++) { back[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { back[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { back[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { back[i][0] = tempTable[0][2-i]; }
    }
}

void left_rotate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = down[i][0]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = left[i][j];
        }
    }
    if(dir == 1) {
        for(int i=0; i<3; i++) { down[i][0] = front[i][0]; }
        for(int i=0; i<3; i++) { front[i][0] = up[i][0]; }
        for(int i=0; i<3; i++) { up[i][0] = back[i][0]; }
        for(int i=0; i<3; i++) { back[i][0] = temp[i]; }
        
        for(int i=0; i<3; i++) { left[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { left[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { left[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { left[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { down[i][0] = back[i][0]; }
        for(int i=0; i<3; i++) { back[i][0] = up[i][0]; }
        for(int i=0; i<3; i++) { up[i][0] = front[i][0]; }
        for(int i=0; i<3; i++) { front[i][0] = temp[i]; }
        
        for(int i=0; i<3; i++) { left[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { left[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { left[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { left[i][0] = tempTable[0][2-i]; }
    }
}

void right_rotate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = down[i][2]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = right[i][j];
        }
    }
    if(dir == 1) {
        for(int i=0; i<3; i++) { down[i][2] = back[i][2]; }
        for(int i=0; i<3; i++) { back[i][2] = up[i][2]; }
        for(int i=0; i<3; i++) { up[i][2] = front[i][2]; }
        for(int i=0; i<3; i++) { front[i][2] = temp[i]; }
        
        for(int i=0; i<3; i++) { right[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { right[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { right[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { right[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { down[i][2] = front[i][2]; }
        for(int i=0; i<3; i++) { front[i][2] = up[i][2]; }
        for(int i=0; i<3; i++) { up[i][2] = back[i][2];}
        for(int i=0; i<3; i++) { back[i][2] = temp[i]; }
        
        for(int i=0; i<3; i++) { right[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { right[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { right[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { right[i][0] = tempTable[0][2-i]; }
    }
}

void front_rotate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = up[2][i]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = front[i][j];
        }
    }
    if(dir == 1) {
        for(int i=0; i<3; i++) { up[2][i] = left[2][i]; }
        for(int i=0; i<3; i++) { left[2][i] = down[0][2-i];}
        for(int i=0; i<3; i++) { down[0][i] = right[2][2-i]; }
        for(int i=0; i<3; i++) { right[2][i] = temp[i]; }
        
        for(int i=0; i<3; i++) { front[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { front[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { front[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { front[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { up[2][i] = right[2][i]; }
        for(int i=0; i<3; i++) { right[2][i] = down[0][2-i];}
        for(int i=0; i<3; i++) { down[0][i] = left[2][2-i]; }
        for(int i=0; i<3; i++) { left[2][i] = temp[i]; }
        
        for(int i=0; i<3; i++) { front[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { front[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { front[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { front[i][0] = tempTable[0][2-i]; }
    }
}

void down_rotate(int dir) {
    char temp[3];
    for(int i=0; i<3; i++) { temp[i] = front[2][i]; }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            tempTable[i][j] = down[i][j];
        }
    }
    if(dir == 1) {
        for(int i=0; i<3; i++) { front[2][i] = left[i][0]; }
        for(int i=0; i<3; i++) { left[i][0] = back[0][2-i];}
        for(int i=0; i<3; i++) { back[0][i] = right[i][2]; }
        for(int i=0; i<3; i++) { right[i][2] = temp[2-i]; }
        
        for(int i=0; i<3; i++) { down[0][i] = tempTable[2-i][0]; }
        for(int i=0; i<3; i++) { down[i][0] = tempTable[2][i]; }
        for(int i=0; i<3; i++) { down[2][i] = tempTable[2-i][2]; }
        for(int i=0; i<3; i++) { down[i][2] = tempTable[0][i]; }
    } else {
        for(int i=0; i<3; i++) { front[2][i] = right[2-i][2]; }
        for(int i=0; i<3; i++) { right[i][2] = back[0][i]; }
        for(int i=0; i<3; i++) { back[0][i] = left[2-i][0]; }
        for(int i=0; i<3; i++) { left[i][0] = temp[i]; }
        
        for(int i=0; i<3; i++) { down[0][i] = tempTable[i][2]; }
        for(int i=0; i<3; i++) { down[i][2] = tempTable[2][2-i]; }
        for(int i=0; i<3; i++) { down[2][i] = tempTable[i][0]; }
        for(int i=0; i<3; i++) { down[i][0] = tempTable[0][2-i]; }
    }
}

int main(void) {
    int T, t, N;
    int direction;
    char str[3];
    
    scanf("%d", &T);
    for(t=1; t<=T; t++) {
        scanf("%d", &N);
        
         //초기화
         for(int i=0; i<3; i++) {
             for(int j=0; j<3; j++) {
                 up[i][j] = 'w';
                 down[i][j] = 'y';
                 front[i][j] = 'r';
                 back[i][j] = 'o';
                 left[i][j] = 'g';
                 right[i][j] = 'b';
             }
        }
        
        for(int i=0; i<N; i++) {
            scanf("%s", str);
            if(str[1] == '+') { direction = 1; } else { direction = 0; }
            if(str[0] == 'U') { up_roate(direction);}
            else if(str[0] == 'D') { down_rotate(direction);}
            else if(str[0] == 'F') { front_rotate(direction);}
            else if(str[0] == 'B') { back_rotate(direction);}
            else if(str[0] == 'L') { left_rotate(direction);}
            else {right_rotate(direction);}
        }
    
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                printf("%c", up[i][j]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
