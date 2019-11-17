//100점
//  2.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/09.
//  Copyright © 2019 송혜경. All rights reserved.


#include <string>
#include <vector>

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    int cnt[100002] = {0, };    //카운팅 배열
    int T[100002] = {0, };  //요소에 해당하는 인덱스를 담는다
    int idx = 0;
    int i, j;
    int k;

    for(i=0; i<s.length(); i++) {
        if(s[i] == '{' || s[i] == '}' || s[i] == ',') {
            continue;
        }else {
            k = 1;
            
            int num = s[i] - '0';
            
            while(s[i+k] != '{' && s[i+k] != '}' && s[i+k] != ',') {
                num *= 10;
                num += (s[i+k] - '0');
                k++;
            }
            
            if(cnt[(num)] == 0) {
                T[idx++] = num;
            }
            
            cnt[num]++;
            
            i = (i + k);
        }
    }
    
    for(j=idx; j>0; j--) {
        for(i=0; i<idx; i++) {
            if(cnt[(T[i])] == j) {
                answer.push_back(T[i]);
            }
        }
    }
    

    return answer;
}

int main(void) {
    string s ="{{2},{2,1},{2,1,3},{2,1,3,4}}";
    vector<int> v;
    
    v =solution(s);
    for(int i=0; i<v.size(); i++) {
        printf("%d ", v[i]);
    }
    return 0;
}

