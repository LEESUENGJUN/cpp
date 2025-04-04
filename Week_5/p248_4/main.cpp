// main.cpp - 지뢰찾기 메인 함수
// 사용자로부터 맵 크기, 지뢰 개수 입력받고 게임 루프 실행

#include "p248_4.h"

int main() {
    cout << "=== 지뢰찾기 게임 시작 ===\n";

    // [문제 1] 사용자로부터 맵 크기 입력
    cout << "가로 크기 입력 (1~80): ";
    cin >> nx;
    cout << "세로 크기 입력 (1~40): ";
    cin >> ny;

    // [문제 2] 사용자로부터 지뢰 개수 입력
    int mines;
    cout << "지뢰 개수 입력: ";
    cin >> mines;
    cin.ignore(); // 개행 버퍼 처리

    // 초기화
    init(mines);

    // 첫 맵 출력
    printMap();

    // 게임 루프 시작
    while (true) {
        bool isFlag;
        int x, y;

        // [문제 4] 사용자 입력 받기
        if (!getInput(isFlag, x, y)) continue;

        // 입력 좌표 범위 확인
        if (x < 0 || y < 0 || x >= nx || y >= ny) {
            cout << "잘못된 좌표입니다.\n";
            continue;
        }

        if (isFlag) {
            // 깃발 표시 또는 해제
            flagMask[y][x] = !flagMask[y][x];
        } else {
            // 셀 열기
            if (openCell(y, x)) {
                printMap();
                cout << " 지뢰를 열었습니다! 게임 오버.\n";
                break;
            }
        }

        printMap();

        // 게임 종료 조건 확인
        int result = isGameClear();
        if (result == 1) {
            cout << " 모든 지뢰를 피했습니다! 게임 클리어!\n";
            break;
        }
    }

    return 0;
}
