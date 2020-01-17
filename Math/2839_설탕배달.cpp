//
//  2839_설탕배달.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/01/11.
//  Copyright © 2020 송혜경. All rights reserved.
//  *

#include <cstdio>

using namespace std;
const int INFI = 10000;

int main(void) {
    int N;
    int remain;
    int minN = INFI;
    int a, b;   //a : 3kg 설탕봉지의 개수, b : 5kg 설탕봉지의 개수
    
    scanf("%d", &N);
    
    for(a=0; a<=N/3; a++) { //3kg 설탕봉지가 a개 있을 경우
        remain = N - (3 * a);   //남은 설탕의 양
        
        if(remain % 5 == 0) {   //남은 설탕은 5kg로 나눠떨어지게 가져갈 수 있으면
            b = remain/5;   //5kg설탕봉지의 수
            if(a+b < minN) {    //최소 설탕 봉지수면 업데이트
                minN = a+b;
            }
        }
    }
    
    if(INFI == minN) {  //정확하게 N킬로그램을 만들 수 없는 경우
        minN = -1;
    }
    
    printf("%d", minN);
    
    return 0;
}
