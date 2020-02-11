//
//  PGS_숫자야구.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/31.
//  Copyright © 2020 송혜경. All rights reserved.
//  ****
/*
 문제 조건 "각자 서로 다른 1~9까지 3자리 임의의 숫자를 정한 뒤" 를 잘 이해 못해서 112 와 같이 중복되는 숫자는 고려하지 않음을 몰라 삽질함
 */

#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> baseball) {
    int numbers[1000][2] = {0, };  int numIdx = 0;
    int strikes, balls, num;
    int numStr, numB;
    int answer = 0;
    int i, j;
    
    //numbers배열에 111 ~ 999를 초기화
    for(i=111; i<=999; i++) {
        numbers[numIdx++][0] = i;
    }
    
    for(i=0; i<baseball.size(); i++) {
        //숫자와 스트라이크수, 볼 수를 알아낸다
        num = baseball[i][0];
        strikes = baseball[i][1];
        balls = baseball[i][2];
        
        
        //numbers배열에 저장되어있는 숫자들에 대하여 만족하지 않으면 [idx][1] 에 -1을 저장
        for(j=0; j<numIdx; j++) {
            numStr = numB = 0;
            
            if(num / 100 == numbers[j][0] / 100) {
                numStr++;
            } else if(num / 100 == (numbers[j][0] % 100) / 10) {
                numB++;
            } else if(num / 100 == numbers[j][0] % 10) {
                numB++;
            } else{}
            
            if((num % 100) / 10 == (numbers[j][0] % 100) / 10) {
                numStr++;
            } else if((num % 100) / 10 == numbers[j][0] / 100) {
                numB++;
            } else if((num % 100) / 10 == numbers[j][0] % 10) {
                numB++;
            } else {}
            
            if(num % 10 == numbers[j][0] % 10) {
                numStr++;
            } else if(num % 10 == numbers[j][0] / 100) {
                numB++;
            } else if(num % 10 == (numbers[j][0] % 100) / 10) {
                numB++;
            } else{}
            
            if(numStr != strikes || numB != balls) {
                numbers[j][1] = -1;
            }
            
            
        }
    }
    
    for(i=0; i<numIdx; i++) {
        if(((((numbers[i][0]) % 100) / 10) == 0) || ((numbers[i][0] % 10) == 0) ) {
            continue;
        }
        if((numbers[i][0] / 100 == (numbers[i][0] % 100) / 10) || (numbers[i][0] / 100 == numbers[i][0] % 10)) {
            continue;
        }
        if((numbers[i][0] % 100) / 10 == numbers[i][0] % 10) {
            continue;
        }
        if(numbers[i][1] != -1) {
            answer++;
        }
    }
    
    return answer;
}

