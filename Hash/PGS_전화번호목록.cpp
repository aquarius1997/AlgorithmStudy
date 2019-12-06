//
//  PGS_전화번호목록.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/06.
//  Copyright © 2019 송혜경. All rights reserved.
//
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

typedef struct HashBucket {
    string arr[100];
    int idx;
    
    void init(void) {
        idx = 0;
    }
}HashBucket;

bool solution(vector<string> phone_book) {
    HashBucket hb[10];
    bool answer = true;
    int num, hIdx;
    int flag = 0;
    int i, j, k;
    
    //해시버켓들 초기화
    for(i=0; i<10; i++) {
        hb[i].init();
    }
    
    //첫번째 전화번호는 insert
    num = phone_book[0][0] - '0';
    hIdx = hb[num].idx;
    hb[num].arr[hIdx] = phone_book[0];
    hb[num].idx += 1;
        
    
    for(i=1; i<phone_book.size(); i++) {
        
        //다른 번호를 접두사로 가지고 있는지 확인한다
        num = phone_book[i][0] - '0';
        for(j=0; j<hb[num].idx; j++) {
            int strLen = (hb[num].arr[j]).length();
            k = 0;
            while(1) {
                //비교할 두 문자열의 길이를 초과하지 않을때까지 반복
                if(k >= strLen || k >= phone_book[i].length()) {    //접두사로 가지고 있을 경우
                    answer = false;
                    flag = 1;   //어떤 번호가 다른 번호의 접두어인 경우가 있을 경우를 표시
                    break;
                } else {
                    if(hb[num].arr[j][k] != phone_book[i][k]) { //접두사로 가지고 있지 않으면
                        break;
                    } else {
                        k++;
                    }
                }
            }
            
            if(flag == 1) {
                break;
            }
            
        }   //end for
        
        hIdx = hb[num].idx;
        hb[num].arr[hIdx] = phone_book[i];
        hb[num].idx += 1;
        
        if(flag == 1) {
            break;
        }
        
    }
    
    return answer;
}

int main(void) {
    vector<string> phone_book;
    
    phone_book.push_back("23");
    phone_book.push_back("123");
    phone_book.push_back("12345");
    
    printf("%d", solution(phone_book));
    
    return 0;
}
