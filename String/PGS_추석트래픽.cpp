//
//  추석트래픽.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/10/30.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <cstdio>
#include <string>
#include <vector>

using namespace std;



int solution(vector<string> lines) {
    int answer = 0;
    int counting = 0;
    int arr[2002][2] = {0, };       //arr[i][0] : 시작시간, arr[i][1] : 종료시간
    int hh, mm, ss, ms, T;
    int idx = 0;
    int i, j;
    
    //파람으로 들어온 벡터에 대하여 모두 수행
    for(i=0; i<lines.size(); i++) {
        //입력으로 들어온 시간을 ms로 변환함
        
        hh = mm = ss = ms = T = 0;
        
        //hour -> ms
        hh += (lines[i][11] - '0') * 10;
        hh += (lines[i][12] - '0');
        ms += (hh * 60 * 60 * 1000);
        
        //minute -> ms
        mm += (lines[i][14] - '0') * 10;
        mm += (lines[i][15] - '0');
        ms += (mm * 60 * 1000);
        
        //second -> ms
        ss += (lines[i][17] - '0') * 10;
        ss += (lines[i][18] - '0');
        ms += (ss * 1000);
        
        ms += (lines[i][20] - '0') * 100;
        ms += (lines[i][21] - '0') * 10;
        ms += (lines[i][22] - '0');

        //처리시간 구하기
        T += (lines[i][24] - '0') * 1000;
        if(lines[i][25] == '.') {
            T += (lines[i][26] - '0') * 100;
            if(lines[i][27] != 's') {
               T += (lines[i][27] - '0') * 10;
                if(lines[i][28] != 's') {
                    T += (lines[i][28] - '0');
                }
            }
        }
        
        //종료시간 저장
        arr[idx][1] = ms;
        //시작시간 저장
        arr[idx][0] = (ms - T + 1);
        //인덱스 증가
        idx += 1;
        
    }   //end for
    
    
    for(i=0; i<idx; i++) {
        //하나의 명령어 실행 시간동안에 대하여
        for(int k=arr[i][0]; k<=arr[i][1]; k++) {
            counting = 0;
            
            //1초동안 동시에 실행되고 있는 명령어들의 총 개수를 센다
            for(j=0; j<idx; j++) {
                if(k <= arr[j][1] && k+1000 > arr[j][0]) {
                    counting += 1;
                }
            }
            
            if(counting > answer) {
                answer = counting;
            }
        }
    }
    
    return answer;
}

int main(void) {
    vector <string> lines;
    
    lines.push_back("2016-09-15 00:00:00.000 3s");
    
    printf("%d\n", solution(lines));
    
    return 0;
    
}
