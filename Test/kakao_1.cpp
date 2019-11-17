//100점


#include <string>
#include <vector>
#define MAXN    32

typedef struct StackType {
    int top;
    int arr[1005];
}StackType;

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int T[MAXN][MAXN] = {0, };
    StackType s;
    int num;
    int i, j;
    
    //스택 초기화
    s.top = -1;
    
    //board를 테이블T에 초기화
    for(i=1; i<=board[0].size(); i++) {
        for(j=1; j<=board[0].size(); j++) {
            T[i][j] = board[i-1][j-1];
        }
    }
    

    
    for(i=0; i<moves.size(); i++) {
        num = moves[i];
        
        //num열에 대하여 가장 위의 행 요소 확인
        for(j=1; j<=board[0].size(); j++) {
            if(T[j][num] > 0) {
                //스택에 푸시하기 전에 현재 넣을 요소가 스택의 탑 요소랑 같으면 2개 터짐
                if(s.top > -1) {
                    if(T[j][num] == s.arr[(s.top)]) {
                        //스택 탑 pop
                        s.top = s.top - 1;
                        answer += 2;
                        T[j][num] = 0;
                        break;
                    }
                }
                //같지 않을 경우 스택에 푸시
                s.arr[++(s.top)] = T[j][num];
                T[j][num] = 0;
                break;
            }
        }
    }

    
    return answer;
}



