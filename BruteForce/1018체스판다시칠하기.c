//
//  1018체스판다시칠하기.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/27.
//  Copyright © 2019 송혜경. All rights reserved.
// **

#include <stdio.h>
int minCnt = 3000;  //색칠해야하는 최소 개수

/* 8*8의 형태로 색칠해야하는 수를 세서 최소값(minCnt)을 update한다
 row, col : 검증을 시작할 판의 행, 열 정보
 */
void howMany(int T[52][52], int row, int col) {
    int i, j, k;
    int flag = 1;   //1 : 행의 처음은 까만색, -1 : 행의 처음은 흰색
    int colFlag = 1;    //열 안에서 까만색 흰색 번갈아 저장하기 위한 변수
    int cnt = 0;
    
    //8 * 8 형태 안에서 확인
    //T[row][col] <- B 일 경우
    for(k=0; k<2; k++) {
        for(i=0; i<8; i++) {
            if(flag == 1) { //깜장으로 시작
                colFlag = 1;
                for(j=0; j<8; j++) {
                    if(colFlag == 1) {  //까만색이어야함
                        if(T[row+i][col+j] != 1) {  //깜장으로 시작안하면
                            cnt++;
                        }
                    } else {    //하얀색이어야함
                        if(T[row+i][col+j] != 2) {  //하얀색이 아니면
                            cnt++;
                        }
                    }
                    colFlag *= -1;
                }
            } else {
                colFlag = -1;
                for(j=0; j<8; j++) {
                    if(colFlag == 1) {  //까만색이어야함
                        if(T[row+i][col+j] != 1) {  //깜장으로 시작안하면
                            cnt++;
                        }
                    } else {    //하얀색이어야함
                        if(T[row+i][col+j] != 2) {  //하얀색이 아니면
                            cnt++;
                        }
                    }
                    colFlag *= -1;
                }
            }
            
            flag *= -1;
        }
        
        
        flag = -1;  //하얀색으로 시작하는 경우 구할려고
        if(minCnt > cnt) {  //최소 카운트인지 확인해서 업데이트하고
            minCnt = cnt;
        }
        cnt = 0;    // 초기화
    }

}


int main(void) {
    int M, N;   //입력으로 받는 판의 행, 열 크기
    int T[52][52] = {0, };  //까만색은 1, 하얀색은 2
    char color[52];
    int i, j;
    
    scanf("%d %d", &M, &N); //판의 크기를 입력받는다
    
    for(i=0; i<M; i++) {    //판의 정보를 입력받는다
        scanf("%s", color);
        for(j=0; j<N; j++) {
            if(color[j] == 'B') {
                T[i][j] = 1;
            } else {
                T[i][j] = 2;
            }
        }
    }   //end 판의 정보 입력받기
    

    for(i=0; i<=M-8; i++) {
        for(j=0; j<=N-8; j++) {
            howMany(T, i, j);
        }
    }
    
    printf("%d", minCnt);
    
    return 0;
    
}
