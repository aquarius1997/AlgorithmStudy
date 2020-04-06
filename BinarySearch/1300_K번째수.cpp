//
//  1300_K번째수.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/04/04.
//  Copyright © 2020 송혜경. All rights reserved.
//

#include <cstdio>
using namespace std;

int g_N = 0;
int g_K = 0;

/// <#Description#>
/// @param small 찾고자하는 K번째 숫자보다 무조건 작은 숫자를 가리킨다
/// @param big 찾고자하는 K번째 숫자보다 무조건 큰 숫자를 가리킨다
long bin_search(long small, long big) {
    long mid = 0;
    long midNum = 0;
    long number = 0;
    long cnt = 0;
    int i, j;
    
    //small에 해당하는 숫자부터 카운팅하기
    if(small + 1 == big) {
        //small에 해당하는 수
        number = (small * small);

        //small보다 큰 숫자 하나씩 개수 알아내기
        while(1) {
            number += 1;
            for(i=1; i<=g_N; i++) {
                for(j=1; j<=g_N; j++) {
                    if(i*j <= number) { cnt++; }
                    else { break;}
                }
            }
            if(g_K <= cnt) {
                break;
            }
        }
        return number;
    } else {
        mid = (small + big) / 2;
        midNum = (mid * mid);
        
        //midNum보다 같거나 작은 숫자들의 개수를 센다
        for(i=1; i<=g_N; i++) {
            for(j=1; j<=g_N; j++) {
                if(i*j <= midNum) { cnt++; }
                else { break; }
            }
        }
        //mid에 해당하는 수가 찾고자 하는 숫자이면
        if(cnt == g_K) {
            return midNum;
        } else if(cnt < g_K) {  //mid 에 해당하는 수가 찾고자 하는 숫자보다 작으면
            return bin_search(mid, big);
        } else {    //mid에 해당하는 수가 찾고자 하는 숫자보다 크면
            return bin_search(small, mid);
        }
    }
}

int main(void) {
    long kNum = 0;
    
    scanf("%d %d", &g_N, &g_K);
    
    kNum = bin_search(0, g_N+1);
    
    printf("%ld", kNum);
    
    return 0;
}
