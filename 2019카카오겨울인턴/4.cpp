//;.효율성 0점 맞음, 정확성만 100

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long arr[200002] = {0, };
int idx = 0;

int bn_search(long long num, int start, int end) {
    int mid;

    if(start > end) {
        return -1;
    }else if(start == end) {
        if(arr[start] == num) {
            return start;
        }else {
            return -1;
        }
    }else {
        mid = (start + end) / 2;
        if(arr[mid] == num) {
            return mid;
        }else if(arr[mid] > num) {
            return bn_search(num, start, mid-1);
        }else {
            return bn_search(num, mid+1, end);
        }
    }
}


vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    int i;
    long long j;
    int from, to;
    int isNull, isNull2;
    int flag = 0;

    for(i=0; i<room_number.size(); i++) {
        if(i == 0) {
            answer.push_back(room_number[i]);
            arr[idx++] = room_number[i];
        }else {
            //들어가고자 하는 방이 비어있는지 확인
            isNull = bn_search(room_number[i], 0, idx-1);
            if(isNull == -1) {  //비어있을 경우
                answer.push_back(room_number[i]);
                arr[idx++] = room_number[i];
                if(arr[idx-2] > arr[idx-1]) {
                    sort(arr, arr+idx);
                }
            }else { //비어있지 않을 경우
                long long min;

                flag = 0;

                for(j=isNull; j<idx-1; j++) {
                    if(arr[j+1] - arr[j] > 1) {
                        min = arr[j] + 1;
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0) {
                    min = arr[idx-1] + 1;
                }

                answer.push_back(min);
                arr[idx++] = min;
                if(arr[idx-2] > arr[idx-1]) {
                    sort(arr, arr+idx);
                }


            }
        }
    }

    return answer;
}
