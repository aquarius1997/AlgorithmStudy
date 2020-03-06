//
//  11286_절댓값힙.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2020/03/02.
//  Copyright © 2020 송혜경. All rights reserved.
//  ***

#include <stdio.h>
#define ABS(a)  ((a < 0) ? (a*(-1)) : (a))

int main(void) {
    int plusHeap[100002];
    int minusHeap[100002];
    int plusIdx = 0;    //마지막 요소를 가리킨다
    int minusIdx = 0;
    int parent, nextIdx;
    int popMinus, popPlus;
    int N, oper, temp;
    int i, j;
        
    scanf("%d", &N);

    for(i=0; i<N; i++) {
        scanf("%d", &oper);

        if(oper < 0) {  //마이너스 힙에 추가
            minusIdx++;
            minusHeap[minusIdx] = oper;
            //부모로올라가면서 정렬
            for(j=minusIdx; j>1; j=j/2) {
                parent = j/2;
                if(minusHeap[parent] == minusHeap[j]) {
                    break;
                } else if(minusHeap[parent] > minusHeap[j]) {
                    break;
                } else {
                    temp = minusHeap[parent];
                    minusHeap[parent] = minusHeap[j];
                    minusHeap[j] = temp;
                }
            }
        }
        else if(oper > 0) {  //플러스힙에 추가
            plusIdx++;
            plusHeap[plusIdx] = oper;
            for(j=plusIdx; j>1; j=j/2) {
                parent = j/2;
                if(plusHeap[parent] == plusHeap[j]) {
                    break;
                } else if(plusHeap[parent] < plusHeap[j]) {
                    break;
                } else {
                    temp = plusHeap[parent];
                    plusHeap[parent] = plusHeap[j];
                    plusHeap[j] = temp;
                }
            }
        }
        else {  //힙에서 값 비교해서 빼내기
            popMinus = popPlus = 0; //빼내야하는걸 1로 만들기
            if(plusIdx + minusIdx == 0) {
                printf("0\n");
            } else {
                if(plusIdx == 0) {
                    popMinus = 1;
                } else if(minusIdx == 0) {
                    popPlus = 1;
                } else {
                    if((minusHeap[1]*(-1)) < plusHeap[1]) {   //마이너스힙 절댓값이 더 작으면
                        popMinus = 1;
                    } else if((minusHeap[1]*(-1)) > plusHeap[1]) {
                        popPlus = 1;
                    } else {    //같으면
                        popMinus = 1;
                    }
                }
                
                if(popMinus == 1) {
                    printf("%d\n", minusHeap[1]);
                    minusHeap[1] = minusHeap[minusIdx];
                    minusIdx--;
                    for(j=1; j<minusIdx;) {
                        if(j*2+1 <= minusIdx) { //오른쪽, 왼쪽 자식 모두 있으면
                            if(minusHeap[j*2] < minusHeap[j*2+1]) { //왼쪽자식이 더 작으면
                                nextIdx = j*2+1;    //오른쪽 자식 선택
                            } else {
                                nextIdx = j*2;
                            }
                        } else if(j*2 <= minusIdx) {    //왼쪽 자식만 있으면
                            nextIdx = j*2;
                        } else {    //둘다없으면
                            break;
                        }
                        if(minusHeap[j] < minusHeap[nextIdx]) {//자식노드와 자리 바꿔야하면
                            temp = minusHeap[nextIdx];
                            minusHeap[nextIdx] = minusHeap[j];
                            minusHeap[j] = temp;
                            j = nextIdx;
                        } else {
                            break;
                        }
                    }
                }
                if(popPlus == 1) {
                    printf("%d\n", plusHeap[1]);
                    plusHeap[1] = plusHeap[plusIdx];
                    plusIdx--;
                    for(j=1; j<plusIdx;) {
                        if(j*2+1 <= plusIdx) {  //왼,오자식 모두있으면
                            if(plusHeap[j*2] < plusHeap[j*2+1]) {   //왼쪽자식이 더 작으면
                                nextIdx = j*2;
                            } else {
                                nextIdx = j*2+1;
                            }
                        } else if(j*2 <= plusIdx) {    //왼쪽만잇으면
                            nextIdx = j*2;
                        } else {    //둘다없으면
                            break;
                        }
                        if(plusHeap[j] > plusHeap[nextIdx]) {
                            temp = plusHeap[nextIdx];
                            plusHeap[nextIdx] = plusHeap[j];
                            plusHeap[j] = temp;
                            j = nextIdx;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }


    return 0;
}
