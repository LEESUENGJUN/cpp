#ifndef P202_2_H
#define P202_2_H

const int SIZE = 5;

// 랜덤한 체커 보드 생성하는 함수
void randomMap(int map[SIZE][SIZE]);

// 체커 보드를 화면에 출력하는 함수
void printMap(int map[SIZE][SIZE]);

//  같은 숫자로 이루어진 행, 열, 대각선 출력하는 함수
void checkMap(int map[SIZE][SIZE]);

#endif // P202_2_H
