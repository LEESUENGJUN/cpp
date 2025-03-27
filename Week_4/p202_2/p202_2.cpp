#include <iostream>
#include <cstdlib>
#include <ctime>
#include "p202_2.h"
/* 5x5 크기의 체커 보드와 관련된 다음 프로그램을 작성하라. 
(1) 5x5 크기의 2차원 배열에 0과 1을 임의로 채우는 함수를 구현하라. 
(2) 체커 보드를 보기 좋게 화면에 출력하는 함수를 구현하라. 
(3) 가로나 세로 또는 대각선이 모두 0이거나 1인 부분을 찾아 화면으로 출력하는 함수 를 구현하라. 
*/
using namespace std;

// (1) 랜덤한 체커 보드 생성하는 함수
void randomMap(int map[SIZE][SIZE]) {
    srand(time(0)); //매번 다른 난수를 생성
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = rand() % 2; // 0 또는 1 랜덤 할당
        }
    }
}

// (2) 체커 보드를 보기 좋게 화면에 출력하는 함수
void printMap(int map[SIZE][SIZE]) {
    cout << "체커 보드:" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

// (3) 가로나 세로 또는 대각선이 모두 0이거나 1인 부분을 찾아 출력하는 함수
void checkMap(int map[SIZE][SIZE]) {
    bool found = false;

    // 가로 검사
    for (int i = 0; i < SIZE; i++) {
        bool allZero = true, allOne = true;
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] != 0) allZero = false;
            if (map[i][j] != 1) allOne = false;
        }
        if (allZero || allOne) {
            cout << "가로줄 " << i + 1 << "이(가) 동일한 값: " << map[i][0] << endl;
            found = true;
        }
    }

    // 세로 검사
    for (int j = 0; j < SIZE; j++) {
        bool allZero = true, allOne = true;
        for (int i = 0; i < SIZE; i++) {
            if (map[i][j] != 0) allZero = false;
            if (map[i][j] != 1) allOne = false;
        }
        if (allZero || allOne) {
            cout << "세로줄 " << j + 1 << "이(가) 동일한 값: " << map[0][j] << endl;
            found = true;
        }
    }

    // 대각선 검사 (왼쪽 위 -> 오른쪽 아래)
    bool allZero = true, allOne = true;
    for (int i = 0; i < SIZE; i++) {
        if (map[i][i] != 0) allZero = false;
        if (map[i][i] != 1) allOne = false;
    }
    if (allZero || allOne) {
        cout << "대각선 (왼쪽 위 -> 오른쪽 아래) 동일한 값: " << map[0][0] << endl;
        found = true;
    }

    // 대각선 검사 (오른쪽 위 -> 왼쪽 아래)
    allZero = true, allOne = true;
    for (int i = 0; i < SIZE; i++) {
        if (map[i][SIZE - 1 - i] != 0) allZero = false;
        if (map[i][SIZE - 1 - i] != 1) allOne = false;
    }
    if (allZero || allOne) {
        cout << "대각선 (오른쪽 위 -> 왼쪽 아래) 동일한 값: " << map[0][SIZE - 1] << endl;
        found = true;
    }

    if (!found) {
        cout << "일치하는 행, 열 또는 대각선이 없습니다." << endl;
    }
}

int main() { //main()에서 함수들을 호출
    int map[SIZE][SIZE];

    randomMap(map); // (1) 5x5 배열을 랜덤하게 채움
    printMap(map);  // (2) 배열 출력
    checkMap(map);  // (3) 같은 숫자로 채워진 행, 열, 대각선 검사

    return 0;
}
