#include "p248_4.h"
#include <cstdlib>
#include <ctime>
#include <string>

// 최대 크기 기준 정적 배열 선언
static int MineMapLabel[40][80];       // 지뢰 위치 및 숫자
static bool MineMapMask[40][80];        // 셀 열림 여부
static bool MineMapFlag[40][80];       // 깃발 표시 여부

int nx, ny;            // 사용자 입력 맵 크기
int totalMine;         // 지뢰 총 개수

// 맵 배열 접근 함수
int& label(int y, int x) { return MineMapLabel[y][x]; }
bool& mask(int y, int x) { return MineMapMask[y][x]; }
bool& flag(int y, int x) { return MineMapFlag[y][x]; }

// 지뢰 맵 초기화 (무작위 지뢰 배치 + 숫자 계산)
void init(int mineCount) {
    srand((unsigned int)time(0));
    for (int y = 0; y < 40; y++)
        for (int x = 0; x < 80; x++) {
            MineMapLabel[y][x] = 0;
            MineMapMask[y][x] = false;
            MineMapFlag[y][x] = false;
        }

    totalMine = mineCount;
    int placed = 0;
    while (placed < mineCount) {
        int x = rand() % nx;
        int y = rand() % ny;
        if (label(y, x) != -1) {
            label(y, x) = -1;
            placed++;
        }
    }

    // 각 셀 주변 지뢰 개수 계산
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(y, x) != -1) {
                int count = 0;
                for (int dy = -1; dy <= 1; dy++)
                    for (int dx = -1; dx <= 1; dx++) {
                        int yy = y + dy, xx = x + dx;
                        if (xx >= 0 && yy >= 0 && xx < nx && yy < ny && label(yy, xx) == -1)
                            count++;
                    }
                label(y, x) = count;
            }
}

// 셀 열기 (0이면 주변 재귀 열기)
bool openCell(int y, int x) {
    if (x < 0 || y < 0 || x >= nx || y >= ny) return false;
    if (mask(y, x) || flag(y, x)) return false;

    mask(y, x) = true;
    if (label(y, x) == 0) {
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                if (!(dy == 0 && dx == 0))
                    openCell(y + dy, x + dx);
    }

    return label(y, x) == -1;  // 지뢰면 true
}

// 맵 출력 (열/행 좌표 포함)
void printMap() {
    cout << "\n    ";
    for (int x = 0; x < nx; x++) cout << (x % 10) << " ";
    cout << "\n";

    for (int y = 0; y < ny; y++) {
        cout << (y % 10) << " | ";
        for (int x = 0; x < nx; x++) {
            if (flag(y, x)) cout << "P ";
            else if (!mask(y, x)) cout << "# ";
            else if (label(y, x) == -1) cout << "* ";
            else cout << label(y, x) << " ";
        }
        cout << "\n";
    }

    // 깃발 개수 표시
    int fCount = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (flag(y, x)) fCount++;
    cout << "현재 깃발 수: " << fCount << " / 전체 지뢰: " << totalMine << "\n";
}

// 게임 종료 조건 확인
int isGameClear() {
    int closed = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (!mask(y, x)) closed++;

    if (closed == totalMine) return 1;  // 클리어
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(y, x) && label(y, x) == -1)
                return -1;  // 지뢰 열림
    return 0;  // 진행 중
}

// 사용자 입력 ("열 행" 또는 "p 열 행")
bool getInput(bool& isFlag, int& x, int& y) {
    string line;
    cout << "입력 예: 20 10  또는  p 20 10\n";
    cout << "입력 --> ";
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

// 메인 게임 루프
int main() {
    cout << "=== 지뢰찾기 게임 시작 ===\n";

    // 맵 크기 입력
    cout << "가로 크기 입력 (1~80): ";
    cin >> nx;
    cout << "세로 크기 입력 (1~40): ";
    cin >> ny;

    // 지뢰 개수 입력
    int mines;
    cout << "지뢰 개수 입력: ";
    cin >> mines;
    cin.ignore(); // 개행 버퍼 제거

    init(mines);      // 초기화
    printMap();       // 맵 출력

    while (true) {
        bool isFlag;
        int x, y;

        if (!getInput(isFlag, x, y)) continue;

        if (x < 0 || y < 0 || x >= nx || y >= ny) {
            cout << "잘못된 좌표입니다.\n";
            continue;
        }

        if (isFlag) {
            flag(y, x) = !flag(y, x);  // 깃발 토글
        } else {
            if (openCell(y, x)) {      // 셀 열기
                printMap();
                cout << "지뢰가 폭발하였습니다! 게임 오버.\n";
                break;
            }
        }

        printMap();  // 상태 출력

        int result = isGameClear();
        if (result == 1) {
            cout << "모든 지뢰를 피했습니다! 게임 클리어!\n";
            break;
        }
    }

    return 0;
}
