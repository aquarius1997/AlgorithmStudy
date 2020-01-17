//
//  7568덩치.c
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/12/27.
//  Copyright © 2019 송혜경. All rights reserved.
// *

#include <stdio.h>

int main(void) {
    int wt[52][2] = {0, };  //몸무게와 키를 저장하는 배열이다. wt[0][0] : 0번째사람의 몸무게, wt[0][1] : 0번째 사람의 키
    int result[52] = {0, }; //등수를 저장하는 배열
    int N, weight, tall;
    int cnt = 0;
    int i, idx;
    
    scanf("%d", &N);    //사람 수 입력받는다
    
    for(i=0; i<N; i++) {    //사람들의 몸무게와 키를 입력으로 받아 wt배열에 저장한다
        scanf("%d %d", &weight, &tall);
        wt[i][0] = weight;
        wt[i][1] = tall;
    }
    
    for(idx=0; idx<N; idx++) {  //idx : 등수를 구할려는 사람의 인덱스
        cnt = 0;    //등수 초기화
        for(i=0; i<N; i++) {    //자기 자신보다 덩치가 큰 사람들의 수를 알아낸다
            if(idx != i) {  //자기 자신은 제외해야 하므로
                if((wt[idx][0] < wt[i][0]) && (wt[idx][1] < wt[i][1])) {    //덩치가 더 큰 사람이 있을 경우 카운팅
                    cnt++;
                }
            }
        }   //end for(i)
        
        //등수를 저장한다
        result[idx] = cnt + 1;
    }   //end for(idx)
    
    for(i=0; i<N; i++) {
        printf("%d ", result[i]);
    }
    
    return 0;
}
