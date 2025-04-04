// p248_4.h - 지뢰찾기 헤더 파일
// 상수 정의, 전역 변수 선언, 함수 프로토타입 정의

#pragma once
#include <iostream>
using namespace std;

// 상수 정의
#define MAX_X 80
#define MAX_Y 40
#define OPEN 1
#define FLAG 2

// 전역 변수 선언
extern int map[MAX_Y][MAX_X];         // 지뢰 맵
extern bool openMask[MAX_Y][MAX_X];   // 셀 열림 상태
extern bool flagMask[MAX_Y][MAX_X];   // 깃발 여부
extern int nx, ny;                    // 가로, 세로 크기
extern int totalMine;                 // 전체 지뢰 수

// 참조형 접근 함수
int& label(int y, int x);
bool& mask(int y, int x);

// 함수 프로토타입
void init(int mineCount = 10);
void printMap();
bool getInput(bool& isFlag, int& x, int& y);
bool openCell(int y, int x);
int getAroundMines(int y, int x);
int countFlags();
int isGameClear();
