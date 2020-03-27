//
//  16235_나무재테크.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/26.
//  Copyright © 2020 송혜경. All rights reserved.
// 2h30min. *****

#include <cstdio>
using namespace std;

int N, M, K;
int tree[12][12][100000] = {0,};
int treeIdx[12][12] = {0, };
int ground[12][12] = {0, };
int A[12][12] = {0,};

/// 사계절 수행한다
void four_seasons(void) {
    int newTree[12][12] = {0, };    //새로 생기는 나무의 수를 저장
    int idx, newIdx;
    int newNum = 0;
    int sum = 0;    //여름에 추가될 양분
    int i, j, k;
    
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            sum = 0;
            newIdx = -1;
            idx = treeIdx[i][j];
            for(k=0; k<idx; k++) {
                if(tree[i][j][k] <= ground[i][j]) {  //살아있는 나무면서 양분을 섭취할 수 있으면
                    ground[i][j] -= tree[i][j][k];  //양분섭취
                    tree[i][j][k] += 1; //나이 +1
                } else {    //살아있는데 양분섭취 못하면 죽음
                    sum += (tree[i][j][k] / 2);   //여름에 추가될 양분 누적하고
                    if(newIdx == -1) {  //새로운 인덱스
                        newIdx = k;
                    }
                }
            }
            //새로운 인덱스로 저장 (죽은것들 제외)
            if(newIdx != -1) {
                treeIdx[i][j] = newIdx;
            }
            //여름
            ground[i][j] += sum;
        }
    }
    
    //가을
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            for(k=0; k<treeIdx[i][j]; k++) {
                if(tree[i][j][k] % 5 == 0) {
                    newTree[i-1][j-1] += 1;
                    newTree[i-1][j] += 1;
                    newTree[i-1][j+1] += 1;
                    newTree[i][j-1] += 1;
                    newTree[i][j+1] += 1;
                    newTree[i+1][j-1] += 1;
                    newTree[i+1][j] += 1;
                    newTree[i+1][j+1] += 1;
                }
            }
        }
    }
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            if(newTree[i][j] > 0) { //새로생긴 나무들이 있으면 수만큼 원래 트리 배열 앞에 추가
                idx = treeIdx[i][j];
                newNum = newTree[i][j]; //새로 생긴 수
                for(k=idx-1; k>=0; k--) {
                    tree[i][j][k+newNum] = tree[i][j][k];
                }
                for(k=0; k<newNum; k++) {   //새로 생긴 나무들
                    tree[i][j][k] = 1;
                }
                treeIdx[i][j] += newNum;    //트리 개수(인덱스) 갱신
            }
        }
    }
    //겨울
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            ground[i][j] += A[i][j];
        }
    }
}

int main(void) {
    int x, y, z;
    int idx;
    int cnt = 0;
    int i, j;
    
    scanf("%d %d %d", &N, &M, &K);
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            scanf("%d", &A[i][j]);
            ground[i][j] = 5;   //초기 영양분 저장
        }
    }
    for(i=0; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        idx = treeIdx[x][y];
        tree[x][y][idx] = z;
        treeIdx[x][y] += 1;
    }
    //K년
    for(i=0; i<K; i++) {
        four_seasons();
    }
    //살은 나무 개수
    for(i=1; i<=N; i++) {
        for(j=1; j<=N; j++) {
            cnt += treeIdx[i][j];
        }
    }
    
    printf("%d", cnt);
    
    return 0;
}
