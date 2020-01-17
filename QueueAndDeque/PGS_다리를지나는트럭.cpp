//
//  PGS_다리를지나는트럭.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/08.
//  Copyright © 2019 송혜경. All rights reserved.
//

/*
 !! 큐에 삽입하는 값은 모두 index임을 유의
 초기화 : idx = 0, t = 1,
 1. 시간을 +1씩하면서 아래 과정을 진행
    1) (t==1)이면 첫번째 트럭(idx == 0) 을 우선 삽입, idx + 1, t를 1증가
    2) (t > 1) 이면
        1) 큐에 들어있는 값들에 대하여 remain시간 -1
        2) 만일 front의 remain시간이 0이면
            1) pop한다
            +) 큐가 비었으면서 idx가 (마지막 트럭+1)이었을 경우 종료한다
        3) (idx <= 마지막트럭)이면 -> 현재 idx에 해당하는 트럭을 다리에 놓을 수 있는지 확인한 후 놓을 수 있으면 큐에 삽입, idx+1
        3) t를 1 증가시킨다
 */


#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<int> Queue;   queue<int> TempQueue;
    int remain[10002] = {0, };  //각 트럭들에 대한 남은 시간
    int answer = 0; int truck;
    int idx= 0;
    int len = truck_weights.size(); //truck_weights의 마지막인덱스+1
    int weightSum = 0;
    int i;
    
    //시간 1로 초기화
    answer = 1;
    //각 트럭의 remain시간 초기화
    for(i=0; i<len; i++) {
        remain[i] = bridge_length;
    }
    
    while(1) {
        if(answer == 1) {  //1초일때에는 첫번째 트럭을 큐에 삽입한다
            Queue.push(idx);
            weightSum += truck_weights[idx];
            idx += 1;
        }   //end 1초일 경우
        else { //1초 이상일 경우
            //큐에 들어있는 값들에 대하여 remain시간을 -1한다
            while(!Queue.empty()) {
                truck = Queue.front();  Queue.pop();
                remain[truck] -= 1;
                TempQueue.push(truck);
            }
            while(!TempQueue.empty()) {
                truck = TempQueue.front();  TempQueue.pop();
                Queue.push(truck);
            }
            
            //큐의 선단에 있는 트럭의 remain시간이 0이면 pop한다
            truck = Queue.front();
            if(remain[truck] <= 0) {
                Queue.pop();
                weightSum -= truck_weights[truck];
                
                //종료 조건 실행
                if(Queue.empty() && idx == len) {
                    break;
                }
            }
            
            //현재 인덱스에 해당하는 트럭을 다리에 놓을 수 있는지 확인한후 push
            if(idx < len) {
                if(weightSum + truck_weights[idx] <= weight) {
                    Queue.push(idx);
                    weightSum += truck_weights[idx];
                    idx += 1;
                }
            }
        }   //end 1초이상일 경우
        
        //시간 증가
        answer += 1;
    }   //end while
    
    return answer;
}

int main(void) {
    vector<int> truck_weights;
    
    truck_weights.push_back(7);
    truck_weights.push_back(4);
    truck_weights.push_back(5);
    truck_weights.push_back(6);
    
    printf("%d ", solution(2, 10, truck_weights));
    
    return 0;
}
