#pragma once
#include <iostream>
using namespace std;

// 상수 정의
#define MAX_X 80
#define MAX_Y 40

// 전역 변수 선언
extern int map[MAX_Y][MAX_X];
extern bool openMask[MAX_Y][MAX_X];
extern bool flagMask[MAX_Y][MAX_X];
extern int nx, ny;
extern int totalMine;

// 함수 선언
int& label(int y, int x);
bool& mask(int y, int x);
void init(int mineCount = 10);
int getAroundMines(int y, int x);
bool openCell(int y, int x);
int countFlags();
void printMap();
bool getInput(bool& isFlag, int& x, int& y);
int isGameClear();
