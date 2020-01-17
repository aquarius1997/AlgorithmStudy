//
//  PGS_카카오프렌즈컬러링북.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/14.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <vector>
#include <queue>

using namespace std;

int visited[102][102] = {0, };
int M, N;
int maxCnt = 0; //가장 큰 영역의 개수를 저장

//입력으로 들어온 r행 c열에 대하여 bfs 탐색을 수행한다
void bfs_func(int r, int c, vector<vector<int>> picture) {
    int row, col;
    queue<int> Queue;
    int element = picture[r][c];    //입력으로 들어온 r행 c열의 색상
    int cnt = 0;    // 구역의 크기를 저장
    
    
    //파라미터로 들어온 행,열 정보에 대하여 방문처리 + 큐에 삽입
    visited[r][c] = 1;
    Queue.push(r);
    Queue.push(c);
    cnt++;
    
    while(!Queue.empty()) { //큐가 빌때까지 반복
        
        row = Queue.front();    Queue.pop();
        col = Queue.front();    Queue.pop();
        
        //상하좌우 탐색 (방문안한 동일한 인접 색상에 대하여 방문처리하며 큐에 삽입한다)
        if(row-1 >= 0) {
            if(picture[row-1][col] == element && visited[row-1][col] == 0) {
                visited[row-1][col] = 1;
                Queue.push(row-1);  Queue.push(col);
                cnt++;
            }
        }
        if(row+1 < M) {
            if(picture[row+1][col] == element && visited[row+1][col] == 0) {
                visited[row+1][col] = 1;
                Queue.push(row+1);  Queue.push(col);
                cnt++;
            }
        }
        if(col-1 >= 0) {
            if(picture[row][col-1] == element && visited[row][col-1] == 0) {
                visited[row][col-1] = 1;
                Queue.push(row);    Queue.push(col-1);
                cnt++;
            }
        }
        if(col+1 < N) {
            if(picture[row][col+1] == element && visited[row][col+1] == 0) {
                visited[row][col+1] = 1;
                Queue.push(row);    Queue.push(col+1);
                cnt++;
            }
        }
        
    }   //end while
    
    //가장 넓은 구역을 업데이트한다
    if(cnt > maxCnt) {
        maxCnt = cnt;
    }
    
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    vector<int> answer(2);
    
    int i, j;
    
    
    //전역변수 초기화
    M = m;
    N = n;
    
    for(i=0; i<m; i++) {
        for(j=0; j<n; j++) {
            visited[i][j] = 0;
        }
    }
    
    maxCnt = 0;

    //컬러링 북의 구역 개수를 알아낸다
    for(i=0; i<m; i++) {
        for(j=0; j<n; j++) {
            if(picture[i][j] != 0 && visited[i][j] == 0) {
                bfs_func(i, j, picture);
                number_of_area++;
            }
        }
    }
    
    max_size_of_one_area = maxCnt;
    
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}

