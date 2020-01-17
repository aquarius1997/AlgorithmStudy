//
//  PGS_단체사진찍기.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/25.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

int visited[8]; //{A, C, F, J, M, N, R, T} 순으로 방문 여부 설정
int line[8];    //line에 저장되는 값은 프렌즈 별 [{A, C, F, J, M, N, R, T} -> {0, 1, 2, 3, 4, 5, 6, 7}] 로 대응한다. 즉, line[1] <-2 일 경우 두번째(인덱스는 0부터 시작하므로)서있는 프렌즈는 C(콘)이다.
int tempAnswer = 0;

//cnt : 이미 줄을 세운 프렌즈의 수
void dfs_f(int idx, int cnt, int n, int intData[102][4]) {
    int f1, f2, dist;   //f1 : 제시한 프렌즈의 인덱스, f2 : 상대 프렌즈의 인덱스
    int flag = 0;
    int i, j;
    
    if(cnt == 8) {  //8명의 프렌즈를 모두 줄 세웠으면 모든 조건을 만족하는지 확인한다
        for(i=0; i<n; i++) {
            flag = 0;   //조건에 적합하지 않게 줄을 세웠을 경우 1로 저장
            //현재 줄을 세워놓은 상태에서, 조건에 명시되어있는 제시한 프렌즈와 상대 프렌즈가 어디에 서있는지 알아낸다
            for(j=0; j<8; j++) {
                if(line[j] == intData[i][0]) {  //제시한 프렌즈의 인덱스를 알아낸다
                    f1 = j;
                }
                if(line[j] == intData[i][1]) {  //상대 프렌즈의 인덱스를 알아낸다
                    f2 = j;
                }
            }
            
            //줄에 둘사이에 몇명의 프렌즈가 있는지 알아낸다(간격 알아내기)
            if(f1 > f2) {
                dist = f1-f2-1;
            } else {
                dist = f2-f1-1;
            }
            
            //조건에 맞는지 확인한다
            if(intData[i][3] == 0) {    //간격에 대한 조건이 '='일 때
                if(dist != intData[i][2]) {
                    flag = 1;
                }
            } else if(intData[i][3] == 1) { //간격에 대한 조건이 '<'일 때
                if(dist >= intData[i][2]) {
                    flag = 1;
                }
            } else {    //간격에 대한 조건이 '>'일 때
                if(dist <= intData[i][2]) {
                    flag = 1;
                }
            }
            
            if(flag == 1) { //조건에 맞지 않을 경우 이후의 조건에 대해서 확인할 필요 없이 종료하면된다
                break;
            }
        }
        
        if(i == n && flag == 0) {   //모든 조건을 만족했을 경우
            tempAnswer += 1;
        }
        
        return;
    } else {
        for(i=0; i<8; i++) {    //줄 안세운 프렌즈 찾아서 dfs 재귀호춣
            if(visited[i] == 0) {
                visited[i] = 1;
                line[idx] = i;  //방금 줄을 세운 프렌즈의 정보를 저장한다 (ex. idx=0, i=0 일 경우 가장 첫번째에 세운 프렌즈는 A(어피치)임.)
                dfs_f(idx+1, cnt+1, n, intData);
                visited[i] = 0;
            }
        }
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;
    //intData : data에 대한 조건 정보를 integer형태로 변환해서 저장 (프렌즈에 대한 정보는 line배열에 저장하는 프렌즈 정보와 동일)
    //intData[i][0] = 제시한 프렌즈 정보, intData[i][1] = 상대 프렌즈 정보, intData[i][2] = 둘의 간격, intData[i][3] = {0(=), 1(<), 2(>)}
    //만일 intData[0][0] = 1, intData[0][1] = 2, intData[0][2] = 3, intData[0][3] = 0 -> 첫번째 조건의, 조건을 제시한 프렌즈는 C(콘)이고, 상대 프렌즈는 F(프로도)이며, 둘의 간격은 3이다
    int intData[102][4] = {0, };
    int i;
    
    //초기화
    for(i=0; i<8; i++) {
        visited[i] = 0;
        line[i] = 0;
    }
    tempAnswer = 0;
    
    //data에 저장된 조건들을 intData에 변환해서 저장
    for(i=0; i<n; i++) {    //data로 입력받은 조건들에 대해 검증
        char tempF = data[i].at(0); //제시한 프렌즈
        char tempF2 = data[i].at(2);    //상대 프렌즈
        
        if(tempF == 'A') {  //제시한 프렌즈에 해당하는 값을 알아낸다
            intData[i][0] = 0;
        } else if(tempF == 'C') {
            intData[i][0] = 1;
        } else if(tempF == 'F') {
            intData[i][0] = 2;
        } else if(tempF == 'J') {
            intData[i][0] = 3;
        } else if(tempF == 'M') {
            intData[i][0] = 4;
        } else if(tempF == 'N') {
            intData[i][0] = 5;
        } else if(tempF == 'R') {
            intData[i][0] = 6;
        } else {
            intData[i][0] = 7;
        }
        
        if(tempF2 == 'A') {  //상대 프렌즈에 해당하는 값을 알아낸다
            intData[i][1] = 0;
        } else if(tempF2 == 'C') {
            intData[i][1] = 1;
        } else if(tempF2 == 'F') {
            intData[i][1] = 2;
        } else if(tempF2 == 'J') {
            intData[i][1] = 3;
        } else if(tempF2 == 'M') {
            intData[i][1] = 4;
        } else if(tempF2 == 'N') {
            intData[i][1] = 5;
        } else if(tempF2 == 'R') {
            intData[i][1] = 6;
        } else {
            intData[i][1] = 7;
        }
        
        char charDist = data[i].at(4);
        intData[i][2] = charDist - '0'; //문자를 숫자로 변환해서 간격 저장
        
        if(data[i].at(3) == '=') {
            intData[i][3] = 0;
        } else if(data[i].at(3) == '<') {
            intData[i][3] = 1;
        } else {
            intData[i][3] = 2;
        }
    }
    
    dfs_f(0, 0, n, intData);
    
    answer = tempAnswer;
    
    return answer;
}

