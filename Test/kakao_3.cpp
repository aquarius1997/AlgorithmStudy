//100점
//  3.cpp
//  AlgorithmGit
//
//  Created by 송혜경 on 2019/11/09.
//  Copyright © 2019 송혜경. All rights reserved.
//

#include <string>
#include <vector>

using namespace std;

int matched[10] = {0, };
int visited[10] = {0, };
int result[10000][10];  int r_idx = 0;
int fin;
int answer_t = 0;

//초기 param : idx = 0, cnt = 0
void dfs(vector<string> user_id, vector<string> banned_id, int idx,int cnt) {
    int i, j, k;
    int flag = 0;

    //종료
    if(cnt == fin) {
        flag = 0;
        
        if(r_idx == 0) {
            for(i=0; i<10; i++) {
                result[r_idx][i] = visited[i];
            }
            r_idx++;
            
            answer_t += 1;
            
        }else {
            for(i=0; i<r_idx; i++) {
                for(j=0; j<10; j++) {
                    if(visited[j] != result[i][j]) {
                        flag = 1;   break;
                    }
                }
                if(j == 10) {
                    flag = 0;   break;
                }
            }
            
            if(flag == 1) {
                
                for(i=0; i<10; i++) {
                    result[r_idx][i] = visited[i];
                }
                r_idx++;
                answer_t += 1;
            }
        }
        

        return;
    }
    
    //idx에 해당하는 제재 아이디에 대하여 실행
    for(j=0; j<user_id.size(); j++) {
        
        if(visited[j] == 0) {
            //제재 아이디에 해당하는 유저 아이디에 대하여만 검사
            if(matched[j] == 1 && (banned_id[idx].length() == user_id[j].length())) {
                flag = 0;
                for(k=0; k<banned_id[idx].length(); k++) {
                    if(banned_id[idx][k] == '*') {
                        continue;
                    }else {
                        if(banned_id[idx][k] != user_id[j][k]) {
                            flag = 1;   break;
                        }
                    }
                }
                
                //제재 아이디 목록에 해당하면
                if(flag == 0) {
                    //방문함을 표시하고 DFS
                    visited[j] = 1;
                    dfs(user_id, banned_id, idx+1, cnt+1);
                    visited[j] = 0;
                }
                
                
            }   //end if(matched[j] == 1 && (banned_id[i].length() == user_id[j].length()))
            
        }   // end if(visited[j] == 0)
    }
    
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    int flag = 0;
    int i, j, k;
    
    //banned_id에 매칭되는 인덱스들을 알아낸다
    for(i=0; i<banned_id.size(); i++) {
        for(j=0; j<user_id.size(); j++) {
            
            //이미 매칭 표시한 유저 아이디는 확인 필요  없음.
            if(matched[j] == 1) {
                continue;
            }

            //매칭되는지 확인하기 위한 flag
            flag = 0;
            
            if(user_id[j].length() == banned_id[i].length()) {
                for(k=0; k<user_id[j].length(); k++) {
                    if(banned_id[i][k] == '*') {
                        continue;
                    }else {
                        //매칭되지 않을 경우
                        if(banned_id[i][k] != user_id[j][k]) {
                            flag = 1;   break;
                        }
                    }
                }
                
                //해당 아이디 인덱스에 대하여 매칭됨을 표시
                if(flag == 0) {
                    matched[j] = 1;
                }
                
            }

        }
    }   //end banned_id에 매칭되는 인덱스들을 알아낸다
    
    fin = banned_id.size();
    


    dfs(user_id, banned_id, 0, 0);
    
    answer = answer_t;
    
    return answer;
}

int main(void) {
    vector<string> user_id;
    vector<string> banned_id;
    
    user_id.push_back("frodo");
    user_id.push_back("fradi");
    user_id.push_back("crodo");
    user_id.push_back("abc123");
    user_id.push_back("frodoc");
    
    banned_id.push_back("fr*d*");
    banned_id.push_back("*rodo");
    banned_id.push_back("******");
    banned_id.push_back("******");

    
    int num = solution(user_id, banned_id);
    
    printf("%d\n", num);

    for(int i=0; i<10; i++) {
        if(matched[i] == 1) {
            printf("%d ", i);
        }
    }
    
    return 0;
}
