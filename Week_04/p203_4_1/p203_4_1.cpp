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
/* 게임 시작 시 퍼즐 크기를 사용자에게 입력받습니다.
   3, 4, 5 중 선택 가능하고, 잘못된 값은 기본값 4로 설정됩니다.”*/
void selectSize() {
    cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
    cin >> DIM;
    if (DIM < 3 || DIM > 5) {
        cout << "잘못된 입력입니다. 기본값 4x4로 설정합니다.\n";
        DIM = 4;
    }
}

// 퍼즐 초기화
/*  입력한 크기를 바탕으로 퍼즐 배열을 1부터 순차적으로 채우고, 마지막을 빈칸 0으로 설정합니다.
    빈칸의 좌표는 x, y로 저장해 이동에 사용됩니다.*/
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
/*시스템 clear로 화면을 지우고, 배열을 보드처럼 출력합니다.
하단에는 현재 이동 횟수와 경과 시간이 함께 표시됩니다.*/
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

/*사용자가 입력한 방향에 따라 빈칸(0)과 숫자 타일을 맞바꿔 이동시키는 역할을 합니다.
방향에 따라 좌표를 조절하고, swap()으로 두 값을 교체합니다.*/
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

/* 퍼즐이 완성되었는지 판단하는 로직입니다.
1부터 차례대로 값이 정렬되어 있어야 하며, 마지막 칸은 0이어야 합니다.
퍼즐 상태를 순회하며 정답 순서와 일치하는지 확인합니다.*/
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

/* 퍼즐을 무작위로 섞기 위해 moveTile()을 여러 번 호출합니다.
   usleep()을 이용해 섞이는 과정이 눈에 보이도록 연출합니다. */
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
/*  전체 게임의 흐름을 담당하는 메인 함수입니다.
    먼저 퍼즐 크기를 입력 받고
    맵을 초기화한 뒤
    랜덤하게 섞고
    방향키 입력을 받아 게임을 반복하며
    퍼즐이 완성되면 종료합니다.*/
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
