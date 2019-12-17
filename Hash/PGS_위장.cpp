//
//  PGS_위장.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/08.
//  Copyright © 2019 송혜경. All rights reserved.
//


#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct HashBucket {
    string kindOf;  //옷 종류
    int arr[31];
    int idx = 0;    //arr의 idx 의미
}HashBucket;

HashBucket hb[31];
int hashIdx = 0;



int solution(vector<vector<string>> clothes) {
    int answer = 1;
    int flag = 0;
    int i, j;
    
    // 모든 의상들을 HashTable에 정리해서 저장
    for(i=0; i<clothes.size(); i++) {
        flag = 0;   //새로운 옷 종류인지 확인하기 위한 플래그
        //같은 의상 종류가 이전에도 있었는지 먼저 확인하기
        for(j=0; j<hashIdx; j++) {
            //같은 의상 종류가 이전에도 있을 경우 해당 버켓에 새로운 옷이 있음을 저장한다
            if((hb[j].kindOf).compare(clothes[i][1]) == 0) {
                flag = 1;   //이미 있는 옷 종류임
                hb[j].arr[(hb[j].idx)] = 1; //새로운 옷을 1로 저장
                hb[j].idx += 1;
                
                break;
            }
        }
        //같은 의상 종류가 이전에 없었으면 새로운 의상 종류임을 나타내고 옷을 저장한다
        if(flag == 0) {
            //새로운 의상 종류를 hb 옷 종류에 저장
            hb[hashIdx].kindOf = clothes[i][1];
            //새로운 옷을 버켓에저장
            hb[hashIdx].arr[(hb[hashIdx].idx)] = 1;
            hb[hashIdx].idx += 1;
            hashIdx += 1;
        }
    }   // end for(모든 의상들을 HashTable에 정리해서 저장)
    
    // ** 모자 2개, 신발 3개, 윗옷 1개 이런식이면
    // 모자 하나를 입거나 안입거나 (2+1 = 3)
    // 신발 하나를 신거나 안신거나 (3+1 = 4)
    // 윗옷을 입거나 안입거나 (1+1 = 2)
    // 위의 경우를 모두 곱하고 모두 안입을 경우는 제외하기 때문에 빼준다 (3*4*2 - 1)
    //조합수구하기
    for(i=0; i<hashIdx; i++) {
        answer = answer * (hb[i].idx + 1);
    }
    
    answer = answer -1;

    
    return answer;
}



int main(void) {
    vector<vector<string>> clothes;
    vector<string> v1;
    vector<string> v2;
    vector<string> v3;
    vector<string> v4;
    vector<string> v5;

    
    v1.push_back("yellow");
    v1.push_back("up");
    
    v2.push_back("red");
    v2.push_back("down");
    
    v3.push_back("blue");
    v3.push_back("up");
    
    v4.push_back("black");
    v4.push_back("shoes");
    
    v5.push_back("white");
    v5.push_back("up");
    
    clothes.push_back(v1);
    clothes.push_back(v2);
    clothes.push_back(v3);
    clothes.push_back(v4);
    clothes.push_back(v5);
    
    printf("%d", solution(clothes));
    
    return 0;
}
