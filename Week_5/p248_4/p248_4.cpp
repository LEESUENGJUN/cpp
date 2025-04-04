// p248_4.cpp - 지뢰찾기 기능 구현

#include "p248_4.h"
#include <cstdlib>
#include <ctime>

// 전역 변수 정의
int map[MAX_Y][MAX_X];
bool openMask[MAX_Y][MAX_X];
bool flagMask[MAX_Y][MAX_X];
int nx, ny;
int totalMine;

// [문제 1] 참조형 접근 함수
int& label(int y, int x) { return map[y][x]; }
bool& mask(int y, int x) { return openMask[y][x]; }

// [문제 2] 셀 열기 함수 (0이면 주변 재귀적으로 열림)
bool openCell(int y, int x) {
    if (x < 0 || y < 0 || x >= nx || y >= ny) return false;
    if (mask(y, x) || flagMask[y][x]) return false;

    mask(y, x) = true;
    if (label(y, x) == 0) {
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                if (!(dy == 0 && dx == 0))
                    openCell(y + dy, x + dx);
    }

    return label(y, x) == -1; // true이면 지뢰 칸 열림
}

// [문제 3] 현재 깃발 개수 계산
int countFlags() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (flagMask[y][x]) count++;
    return count;
}

// [문제 3] 맵 출력 (행/열 숫자 포함)
void printMap() {
    cout << "\n   ";
    for (int x = 0; x < nx; x++) cout << (x % 10) << " ";
    cout << endl;

    for (int y = 0; y < ny; y++) {
        cout << (y % 10) << "  ";
        for (int x = 0; x < nx; x++) {
            if (flagMask[y][x]) cout << "P ";
            else if (!mask(y, x)) cout << "# ";
            else if (label(y, x) == -1) cout << "* ";
            else cout << label(y, x) << " ";
        }
        cout << endl;
    }

    cout << "현재 깃발 수: " << countFlags() << " / 전체 지뢰: " << totalMine << "\n";
}

// [문제 2] 주변 지뢰 개수 계산
int getAroundMines(int y, int x) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++) {
            int nyy = y + dy, nxx = x + dx;
            if (nxx >= 0 && nyy >= 0 && nxx < nx && nyy < ny && map[nyy][nxx] == -1)
                count++;
        }
    return count;
}

// [문제 2] 초기화 함수: 지뢰 무작위 매설 + 숫자 계산
void init(int mineCount) {
    srand((unsigned int)time(0));

    for (int y = 0; y < MAX_Y; y++)
        for (int x = 0; x < MAX_X; x++) {
            map[y][x] = 0;
            openMask[y][x] = false;
            flagMask[y][x] = false;
        }

    totalMine = mineCount;
    int placed = 0;
    while (placed < mineCount) {
        int x = rand() % nx;
        int y = rand() % ny;
        if (map[y][x] != -1) {
            map[y][x] = -1;
            placed++;
        }
    }

    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (map[y][x] != -1)
                map[y][x] = getAroundMines(y, x);
}

// [문제 4] 사용자 입력 처리 ("p x y" 또는 "x y")
bool getInput(bool& isFlag, int& x, int& y) {
    string line;
    cout << "입력 (예: 5 3 또는 p 5 3): ";
    getline(cin, line);

    if (line.empty()) return false;

    if (line[0] == 'p' || line[0] == 'P') {
        isFlag = true;
        sscanf(line.c_str() + 1, "%d %d", &x, &y);
    } else {
        isFlag = false;
        sscanf(line.c_str(), "%d %d", &x, &y);
    }
    return true;
}

// 게임 종료 조건 검사
int isGameClear() {
    int closed = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (!mask(y, x)) closed++;

    if (closed == totalMine) return 1;  // 성공
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(y, x) && label(y, x) == -1)
                return -1; // 지뢰 열림
    return 0; // 진행 중
}
