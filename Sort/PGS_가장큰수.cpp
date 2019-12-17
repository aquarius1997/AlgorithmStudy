//
//  PGS_가장큰수.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/20.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

int temp[100002][2] = {0, };
int arr[100002][2] = {0, };

void merge_f(vector<int> numbers, int s1, int e1, int s2, int e2) {
    int p, q;
    int idx = 0;
    int i;
    
    p = s1; q = s2;
    
    while(p <= e1 && q <= e2) {
        if(arr[p][1] > arr[q][1]) {
            temp[idx][0] = arr[p][0];
            temp[idx++][1] = arr[p][1];
            p++;
        }else if(arr[p][1] < arr[q][1]){
            temp[idx][0] = arr[q][0];
            temp[idx++][1] = arr[q][1];
            q++;
        }else { //동일할 경우
            //자리수가 더 작은게 먼저 저장
            if(numbers[(arr[p][0])] < numbers[(arr[q][0])]) {
                temp[idx][0] = arr[p][0];
                temp[idx++][1] = arr[p][1];
                p++;
            }else {
                temp[idx][0] = arr[q][0];
                temp[idx++][1] = arr[q][1];
                q++;
            }
        }
    }
    
    if(p > e1) {
        for(i=q; i<=e2; i++) {
            temp[idx][0]= arr[i][0];
            temp[idx++][1] = arr[i][1];
        }
    }
    
    if(q > e2) {
        for(i=p; i<=e1; i++) {
            temp[idx][0] = arr[i][0];
            temp[idx++][1] = arr[i][1];
        }
    }
    
    for(i=0; i<idx; i++) {
        arr[s1+i][0] = temp[i][0];
        arr[s1+i][1] = temp[i][1];
    }
    
}

void merge_sort(vector<int> numbers, int start, int end) {
    int mid;
    
    if(start < end) {
        mid = (start+end) / 2;
        
        merge_sort(numbers, start, mid);
        merge_sort(numbers,mid+1, end);
        merge_f(numbers, start, mid, mid+1, end);
    }
}

string solution(vector<int> numbers) {
    string answer = "";
    int maxn = 0;
    int d;
    int i;
    
    //가장 큰 수를 찾아서 자리수를 알아낸다
    for(i=0; i<numbers.size(); i++) {
        if(numbers[i] > maxn) {
            maxn = numbers[i];
        }
    }
    
    for(d=100000; d>=1; d=d/10) {
        if(maxn >= d) {
            break;
        }
    }
    
    //가장 큰 수와 자리수를 동일하게 만들어 temp배열에 저장한다
    for(i=0; i<numbers.size(); i++) {

        arr[i][0] = i;  //원래 값의 인덱스 번호 저장
        arr[i][1] = numbers[i];
        if(numbers[i] == 0) {
            continue;
        }
        while(arr[i][1] < d) {
            arr[i][1] *= 10;
        }
        
    }

    //내림차순정렬
    merge_sort(numbers, 0, numbers.size()-1);

    //정렬결과 붙인다
    for(i=0; i<numbers.size(); i++) {
        
        string s = to_string(numbers[(arr[i][0])]);
        
        answer.append(s);
    }
    
    
    return answer;
}


int main(void) {
    vector<int> numbers;
    
    
    numbers.push_back(3);
    numbers.push_back(30);
    numbers.push_back(34);
    numbers.push_back(9);
    numbers.push_back(0);

    
    return 0;
}
