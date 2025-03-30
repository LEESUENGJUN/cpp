/*4.8절의 4x4 퍼즐 게임을 다음과 같이 확장하라.
 (1) 퍼즐 맵의 크기 확장: 게임을 3x3과 5x5로 확장하라. */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

const int MAX_DIM = 5;
int DIM;                    // 사용자 선택 크기
int map[MAX_DIM][MAX_DIM]; // 퍼즐 맵
int x, y;                   // 빈칸 좌표
int moveCount = 0;
clock_t startTime;

// 크기 선택
void selectSize() {
    cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
    cin >> DIM;
    if (DIM < 3 || DIM > 5) {
        cout << "잘못된 입력입니다. 기본값 4x4로 설정합니다.\n";
        DIM = 4;
    }
}

// 퍼즐 초기화
void initMap() {
    int num = 1;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            map[i][j] = num++;
        }
    }
    map[DIM - 1][DIM - 1] = 0; // 빈칸
    x = y = DIM - 1;
}

// 퍼즐 맵 출력
void draw() {
    system("clear");
    cout << "\tFifteen Puzzle\n";
    cout << "--------------------\n";
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (map[i][j] == 0)
                printf("   ");
            else
                printf("%3d", map[i][j]);
        }
        cout << endl;
    }
    cout << "--------------------\n";
    double seconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("\n\t이동 횟수: %d\n", moveCount);
    printf("\t소요 시간: %.1f\n\n", seconds);
}

// 블록 이동
void moveTile(char dir) {
    int nx = x, ny = y;

    if (dir == 'U') ny++;
    else if (dir == 'D') ny--;
    else if (dir == 'L') nx++;
    else if (dir == 'R') nx--;

    if (nx < 0 || nx >= DIM || ny < 0 || ny >= DIM) return;

    swap(map[y][x], map[ny][nx]);
    x = nx; y = ny;
    moveCount++;
}

// 퍼즐 완성 여부 확인
bool isSolved() {
    int val = 1;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (i == DIM - 1 && j == DIM - 1) {
                if (map[i][j] != 0) return false;
            } else {
                if (map[i][j] != val++) return false;
            }
        }
    }
    return true;
}

// 퍼즐 섞기
void shuffle(int count) {
    const char directions[4] = {'U', 'D', 'L', 'R'};
    for (int i = 0; i < count; i++) {
        moveTile(directions[rand() % 4]);
        draw();
        usleep(30000); // 섞이는 모습 보여주기 (0.03초 대기)
    }
    moveCount = 0;
}

// 키 입력 처리
int getKey() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int getArrowKey() {
    int ch = getKey();
    if (ch == 27 && getKey() == 91) {
        switch (getKey()) {
            case 65: return 'U'; // ↑
            case 66: return 'D'; // ↓
            case 67: return 'R'; // →
            case 68: return 'L'; // ←
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    selectSize();
    initMap();

    int shuffleCount = rand() % 91 + 10; // 10~100 회 랜덤 섞기
    shuffle(shuffleCount);

    startTime = clock();
    draw();

    while (true) {
        int key = getArrowKey();
        moveTile(key);
        draw();

        if (isSolved()) {
            cout << " 퍼즐을 완성하셨습니다! 축하합니다! \n";
            break;
        }
    }

    return 0;
}
