// **
//  PGS_카펫.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/19.
//  Copyright © 2019 송혜경. All rights reserved.
//  출처로 원래 문제에 edge에만 brown을 칠한다는 얘기가 있어서 그거 기반으로 풂

#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int red) {
    vector<int> answer;
    int r, c;
    int temp;
    int sum;
    
    sum = brown + red;
    
    c = r = 3;  //초기 높이를 3으로 설정한다
    while(1) {
        if(sum % c == 0) {  //나눠 떨어질 경우에만
            r = sum / c;    //가로길이를 구한다
            
            temp = (r*c) - ((r-2)*(c-2));
            if(temp == brown) {
                break;
            }
        }
        c += 1;
    }
    
    answer.push_back(r);
    answer.push_back(c);
    
    return answer;
}
