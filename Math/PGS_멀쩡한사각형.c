#include <stdio.h>

//기울기가 45보다 크면 중간지점부터 높이를 -1씩하며 그에 해당하는 w를 구한다(tan) 이를 바탕으로 계싼
//기우릭가 45보다 작으면 중간지점 길이를 -1씩하며 그에 해당하는 높이를 구한다. 이를 바탕으로 계산

long long solution(int w,int h)
{
    long long answer = 0;
    int flag1, flag2;   //w가 정수가 아닐경우 flag1 = 1, h가 정수가 아닐경우 flag2 = 1
    double w2, h2;  //정수가 아니게 될때 w 와 h값을 저장
    int cnt;
    
    flag1 = flag2 = cnt = 0;
    
    //종료조건은 루프 안에서 따로 설정
    while(1) {
        
        //w 와 h를 2로 나누기 전에 나눴을 때 소수가 되는지 확인한다
        if(w%2 != 0 && flag1 == 0) {
            flag1 = 1;
            w2 = (double)w;
        }
        if(h%2 != 0 && flag2 == 0) {
            flag2 = 1;
            h2 = (double)h;
        }
        
        //둘다 2로 나눴을 때 소수일 경우
        if(flag1 == 1 && flag2 == 1) {
            //첫번째 루프일 경우 *2 생략
            if(cnt == 0) {
                answer += 1;
            }else {
                answer += (1*2);
            }
            w2 /= 2;
            h2 /= 2;
            
            //종료조건
            if(!(w2 > 1 || h2 > 1)) {
                break;
            }
        }else if(flag1 == 1) {  //w만 2로 나눴을 때 소수일 경우
            if(cnt == 0) {  //첫번째 루프일 경우 *2 생략
                answer += 2;
            }else {
                answer += (2*2);
            }
            w2 /= 2;
            h /= 2;
            
            if(!(w2 > 1 || h > 1)) {    //종료조건
                break;
            }
        }else if(flag2 == 1) {  //h만 2로 나눴을 때 소수일 경우
            if(cnt == 0) {
                answer += 2;
            }else {
                answer += (2*2);
            }
            w /= 2;
            h2 /= 2;
            
            if(!(w > 1 || h2 > 1)) {    //종료조건
                break;
            }
        }else { //둘다 2로 나눠도 자연수일경우
            w /= 2;
            h /= 2;
            
            if(!(w > 1 || h > 1)) { //종료조건
                break;
            }
        }
        
        cnt++;
        
    }   //end while
    
    return answer;
}

int main(void) {
    int w, h;
    
    while(1) {
        scanf("%d %d", &w, &h);
        
        if(w == 0) {
            break;
        }
        
        printf("%lld\n", solution(w, h));
        
    }
    
    return 0;
}
