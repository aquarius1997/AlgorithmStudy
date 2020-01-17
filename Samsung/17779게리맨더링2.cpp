//
//  게리맨더링2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/10/30.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <stdio.h>

typedef struct NodeType {
    int r;
    int c;
}NodeType;

NodeType nodes[4];  //사각형 꼭짓점 정보 저장
int T[25][25] = {0, };  //구역 정보를 저장하는 테이블
int P[25][25] = {0, };  //사람의 수를 저장하는 테이블
int N;
int mini = 987987987;

void getMin() {
    int visited[25][25] = {0, };
    int minSum = 987987987;
    int maxSum = 0;
    int sum;
    int i, j;
        
    //첫번째 선거구의 합을 구한다
    sum = 0;

    for(i=0; i<nodes[1].r; i++) {
        for(j=0; j<N; j++) {
            if(T[i][j] == 0) {
                sum += P[i][j];
                visited[i][j] = 1;
            }else if(T[i][j] == 1) {
                sum += P[i][j];
                visited[i][j] = 1;
                break;
            }else {
                break;
            }
        }
    }
    
    if(sum > maxSum) {
        maxSum = sum;
    }
    if(sum < minSum) {
        minSum = sum;
    }
    
    //end 첫번째 선거구 합 구하기
    
    //두번째 선거구의 합을 구한다
    sum = 0;
    
    for(i=nodes[1].r; i<N; i++) {
        for(j=0; j<N; j++) {
            if(T[i][j] == 2 || T[i][j] == 0) {
                sum += P[i][j];
                visited[i][j] = 1;
            }else {
                break;
            }
        }
    }
    
    if(sum > maxSum) {
        maxSum = sum;
    }
    if(sum < minSum) {
        minSum = sum;
    }
    
    //end 두번째 선거구 합 구하기
    
    //세번째 선거구의 합을 구한다
    sum = 0;
    
    for(i=nodes[3].r+1; i<N; i++) {
        for(j=N-1; j>=0; j--) {
            if(T[i][j] == 0) {
                sum += P[i][j];
                visited[i][j] = 1;
            }else if(T[i][j] == 3) {
                sum += P[i][j];
                visited[i][j] = 1;
                break;
            }else {
                break;
            }
        }
    }
    
    if(sum > maxSum) {
        maxSum = sum;
    }
    if(sum < minSum) {
        minSum = sum;
    }
    
    //end 세번째 선거구 합 구하기
    
    //네번째 선거구의 합을 구한다
    sum = 0;
    
    for(i=0; i<=nodes[3].r; i++) {
        for(j=N-1; j>=0; j--) {
            if(T[i][j] == 0) {
                sum += P[i][j];
                visited[i][j] = 1;
            }else if(T[i][j] == 4) {
                sum += P[i][j];
                visited[i][j] = 1;
            }else {
                break;
            }
        }
    }
    
    if(sum > maxSum) {
        maxSum = sum;
    }
    if(sum < minSum) {
        minSum = sum;
    }
    

    //end 네번째 선거구 합 구하기
    
    //다섯번째 선거구의 합을 구한다
    sum = 0;
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if(visited[i][j] == 0) {
                sum += P[i][j];
            }
        }
    }
    
    if(sum > maxSum) {
        maxSum = sum;
    }
    if(sum < minSum) {
        minSum = sum;
    }
    
    //end 다섯번째 선거구 합 구하기
    
    if(maxSum - minSum < mini) {
        mini = maxSum - minSum;
    }
}


//rr : 왼쪽 대각선으로 내려갈 때 직사각형의 한 변의 길이, cc : 오른쪽 대각선으로 내려갈 때 직사각형 한 변의 길이
void dfs(int row, int col, int rr, int cc, int round) {
    int i, j;
    

    if(round == 1) {    //왼쪽 대각선으로 내려간다
        nodes[0].r = row;   nodes[0].c = col;
        T[row][col] = 5;
        
        for(i=1; i<N; i++) {
            if(row+i < N && col-i >=0) {
                dfs(row+i, col-i, i, cc, round+1);
            }
        }
        
        T[row][col] = 0;
    }   //end 왼쪽 대각선으로 내려간다
    else if(round == 2) {   //오른쪽 대삭선으로 내려간다
        nodes[1].r = row;   nodes[1].c = col;
        T[row][col] = 5;
        
        for(i=1; i<N; i++) {
            if(row+i < N && col+i < N) {
                dfs(row+i, col+i, rr, i, round+1);
            }
        }
        
        T[row][col] = 0;

    }   //end 오른쪽 대각선으로 내려간다
    else if(round == 3) {   //오른쪽 대각선으로 rr만큼 올라간다
        nodes[2].r = row;   nodes[2].c = col;
        T[row][col] = 5;
        
        if(row-rr >= 0 && col+rr < N) {
            dfs(row-rr, col+rr, rr, cc, round+1);
        }
        
        T[row][col] = 0;

    }   //end 오른쪽 대각선으로 rr만큼 올라간다
    else if(round == 4) {   //왼쪽 대각선으로 cc만큼 올라간다
        nodes[3].r = row;   nodes[3].c = col;
        T[row][col] = 5;
        
        if(row-rr >=0 && col-cc >= 0) {
            dfs(row-cc, col-cc, rr, cc, round+1);
        }
        
        T[row][col] = 0;

    }else { //사각형이 만들어졌으면
        
        //구역을 좀 더 자세히 나누는 과정을 수행
        for(i=nodes[0].r-1; i>=0; i--) {
            T[i][(nodes[0].c)] = 1;
        }
        for(i=nodes[1].c-1; i>=0; i--) {
            T[(nodes[1].r)][i] = 2;
        }
        for(i=nodes[2].r+1; i<N; i++) {
            T[i][(nodes[2].c)] = 3;
        }
        for(i=nodes[3].c+1; i<N; i++) {
            T[(nodes[3].r)][i] = 4;
        }
        
        for(i=1; i<rr; i++) {
            T[row+i][col-i] = 5;
        }
        row = row + rr; col = col - rr;
        for(i=1; i<cc; i++) {
            T[row+i][col+i] = 5;
        }
        row = row + cc; col = col + cc;
        for(i=1; i<rr; i++) {
            T[row-i][col+i] = 5;
        }
        row = row - rr;   col = col + rr;
        for(i=1; i<cc; i++) {
            T[row-i][col-i] = 5;
        }
        row = row - cc;   col = col - cc;
        
        //end 구역을 좀 더 자세히 나누기
        
        //각 선거구당 인원수의 합을 구하는 함수 호출
        getMin();
        
        
        // T 테이블 초기화
        for(i=nodes[0].r-1; i>=0; i--) {
            T[i][(nodes[0].c)] = 0;
        }
        for(i=nodes[1].c-1; i>=0; i--) {
            T[(nodes[1].r)][i] = 0;
        }
        for(i=nodes[2].r+1; i<N; i++) {
            T[i][(nodes[2].c)] = 0;
        }
        for(i=nodes[3].c+1; i<N; i++) {
            T[(nodes[3].r)][i] = 0;
        }
        
        for(i=1; i<rr; i++) {
            T[row+i][col-i] = 0;
        }
        row = row + rr; col = col-rr;
        for(i=1; i<cc; i++) {
            T[row+i][col+i] = 0;
        }
        row = row + cc; col = col+cc;
        for(i=1; i<rr; i++) {
            T[row-i][col+i] = 0;
        }
        row = row-rr;   col = col+rr;
        for(i=1; i<cc; i++) {
            T[row-i][col-i] = 0;
        }
        row = row-cc;   col = col-cc;
        //end T테이블 초기화
        
        
    }   //end 사각형이 만들어 졌으면
    
}


int main(void) {
    int i, j;
    
    scanf("%d", &N);
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            dfs(i, j, 0, 0, 1);
        }
    }
    
    printf("%d", mini);
    
    return 0;
}
