//
//  PGS_조이스틱.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/20.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

int solution(string name) {
    int answer = 0;
    int up, down;
    int left, right;
    int idx, flag, minIdx, mini;
    int visited[22] = {0, };    //visited[i] = 0 : i번째의 값을 아직 변경안함. visited[i] = 1 : i번째 값을 변경함
    int i;
    
    for(i=0; i<name.length(); i++) {
        //값을 변경시키지 않아도 될 요소들은 visited[i]를 1 처리한다
        if(name[i] == 'A') {
            visited[i] = 1;
        }
    }
    
    //첫번째 요소부터 시작
    idx = 0;
    while(1) {
        //아직 바꿀 요소가 있는지 점검
        flag = 0;
        minIdx = mini = 99;
        
        //고칠 요소가 있을경우 왼쪽,오른쪽의 최소 이동 카운트와 해당 인덱스를 찾는다
        for(i=0; i<name.length(); i++) {
            if(visited[i] == 0) {
                flag = 1;
                
                //왼쪽이동과 오른쪽 이동중 더 작은값을 선택한다
                if(i < idx) {
                    left = idx - i;
                    right = name.length() - idx + i;
                }else {
                    left = name.length() - i + idx;
                    right = i - idx;
                }
                
                
                if(left < right) {
                    //최소 이동 인덱스 찾기
                    if(left < mini) {
                        minIdx = i;
                        mini = left;
                    }
                }else {
                    if(right < mini) {
                        minIdx = i;
                        mini = right;
                    }
                }
                
                
            }   //end if(visited[i] == 0)
            
        }   //end for
        
        
        if(flag == 1) { //아직 고치지 않은 글자가 있음
            answer += mini; //왼쪽, 오른쪽 이동중 가장 작은 이동을 더한다
            
            //위로 조작하는것과 아래로 조작하는 것 중 작은 값을 택한다
            up = name[minIdx] - 'A'; //위로 조작할 경우
            down = 26 - name[minIdx] + 'A';  //아래로 조작할 경우
            
            if(up < down) {
                answer += up;
            }else {
                answer += down;
            }
            
            //고친 값의 인덱스 변경
            idx = minIdx;
            visited[idx] = 1;
            
        }else { //글자 모두 고치면
            break;
        }
    }
    
    
    return answer;
}


int main(void) {
    printf("%d", 'B'-'A');
    
    return 0;
}
