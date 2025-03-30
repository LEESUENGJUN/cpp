/*4.8절의 4x4 퍼즐 게임을 다음과 같이 확장하라.
그림 퍼즐 기능: 퍼즐 조각에 숫자가 아니라 문자가 출력되도록 해 보라.*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_DIM = 5;
int DIM;
int map[MAX_DIM][MAX_DIM];
int initialMap[MAX_DIM][MAX_DIM];
int x, y;
int moveCount = 0;
clock_t startTime;

struct Move {
    int fromX, fromY, toX, toY;
};
vector<Move> moveHistory;

const string asciiArt[16][7] = {
    {"       ", "       ", "       ", "       ", "       ", "       ", "       "},
    {" _____ ", "/  __ \\", "| /  \\\\", "| |    ", "| \\__/\\", " \\____/", "       "},
    {" _____ ", "/  _  \\", "| | | |", "| | | |", "| |_| |", "\\_____/", "       "},
    {" _____ ", "/  ___|", "| |    ", "| |    ", "| |___ ", "\\____/", "       "},
    {" _____ ", "|  __ \\", "| |  \\\\", "| | __ ", "| |_\\ \\", " \\____/", "       "},
    {" _____ ", "|  ___|", "| |___ ", "|  ___|", "| |___ ", "\\_____|", "       "},
    {" _____ ", "|  ___|", "| |_   ", "|  _|  ", "| |___ ", "\\_____|", "       "},
    {" _____ ", "|  __  ", "| |_/ /", "|    / ", "| |\\ \\", "\\_| \\_|", "       "},
    {" _____ ", "|  ___|", "| |_  |", "|  _| |", "| |___|", "\\_____/ ", "       "},
    {" _____ ", "|  ___|", "| |_  |", "|  _| |", "| |___|", "\\_____/ ", "       "},
    {" _____ ", "| |__  ", "|  _ \\", "| | | |", "| |_| |", "\\_____/ ", "       "},
    {" _____ ", "| |  \\", "| |__/ /", "|  __/ ", "| |___ ", "\\____/ ", "       "},
    {" _____ ", "|  __| ", "| |__  ", "|  __| ", "| |___ ", "\\____/ ", "       "},
    {" _____ ", "|  __  ", "| |  \\", "| |__/ ", "|  __/ ", "\\____/ ", "       "},
    {" _____ ", "|  _  ", "| | | ", "| |_| ", "|  __/ ", "\\____/ ", "       "},
    {"       ", "       ", "       ", "       ", "       ", "       ", "       "}
};

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
    } else if (ch == 's' || ch == 'S') return 'S';
    return 0;
}

void draw() {
    system("clear");
    for (int i = 0; i < DIM; i++) {
        for (int line = 0; line < 7; line++) {
            for (int j = 0; j < DIM; j++) {
                int val = map[i][j];
                cout << asciiArt[val % 16][line];
            }
            cout << endl;
        }
    }
    cout << "-----------------------------\n";
    double seconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("이동 횟수: %d\t소요 시간: %.1f초\n", moveCount, seconds);
}

void saveGame(const string& filename) {
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "[오류] 게임 저장 실패\n";
        return;
    }
    out.write((char*)&DIM, sizeof(DIM));
    out.write((char*)map, sizeof(map));
    out.write((char*)&x, sizeof(x));
    out.write((char*)&y, sizeof(y));
    out.write((char*)&moveCount, sizeof(moveCount));
    clock_t now = clock();
    out.write((char*)&now, sizeof(now));
    out.close();
    cout << "[안내] 게임이 save.dat에 저장되었습니다.\n";
}

bool loadGame(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return false;
    clock_t savedTime;
    in.read((char*)&DIM, sizeof(DIM));
    in.read((char*)map, sizeof(map));
    in.read((char*)&x, sizeof(x));
    in.read((char*)&y, sizeof(y));
    in.read((char*)&moveCount, sizeof(moveCount));
    in.read((char*)&savedTime, sizeof(savedTime));
    in.close();
    startTime = clock() - savedTime;
    return true;
}

void selectSize() {
    cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
    cin >> DIM;
    if (DIM < 3 || DIM > 5) {
        cout << "잘못된 입력입니다. 기본값 4x4로 설정합니다.\n";
        DIM = 4;
    }
}

void initMap() {
    int num = 1;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            map[i][j] = num++;
    map[DIM - 1][DIM - 1] = 0;
    x = y = DIM - 1;
}

void moveTile(char dir, bool record = true) {
    int nx = x, ny = y, fromX = x, fromY = y;
    if (dir == 'U') ny++;
    else if (dir == 'D') ny--;
    else if (dir == 'L') nx++;
    else if (dir == 'R') nx--;
    else if (dir == 'S') {
        saveGame("save.dat");
        exit(0);
    }
    if (nx < 0 || nx >= DIM || ny < 0 || ny >= DIM) return;
    if (record) moveHistory.push_back({fromX, fromY, nx, ny});
    swap(map[y][x], map[ny][nx]);
    x = nx; y = ny; moveCount++;
}

bool isSolved() {
    int val = 1;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            if (i == DIM - 1 && j == DIM - 1) {
                if (map[i][j] != 0) return false;
            } else {
                if (map[i][j] != val++) return false;
            }
        }
    return true;
}

void shuffle(int count) {
    const char dir[4] = {'U', 'D', 'L', 'R'};
    for (int i = 0; i < count; i++) {
        moveTile(dir[rand() % 4], false);
        draw();
        usleep(20000);
    }
    memcpy(initialMap, map, sizeof(map));
    moveHistory.clear();
    moveCount = 0;
}

void replay() {
    memcpy(map, initialMap, sizeof(map));
    draw();
    usleep(500000);
    for (const auto& m : moveHistory) {
        swap(map[m.fromY][m.fromX], map[m.toY][m.toX]);
        x = m.toX; y = m.toY;
        draw();
        usleep(300000);
    }
}

int main() {
    srand(time(NULL));
    cout << "저장된 게임을 불러오시겠습니까? (y/n): ";
    char ch; cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        if (!loadGame("save.dat")) {
            cout << "불러오기 실패. 새 게임 시작.\n";
            selectSize(); initMap(); shuffle(rand() % 91 + 10);
        }
    } else {
        selectSize(); initMap(); shuffle(rand() % 91 + 10);
    }

    draw();
    while (true) {
        int key = getArrowKey();
        moveTile(key);
        draw();
        if (isSolved()) {
            cout << "🎉 퍼즐을 완성하셨습니다! 축하합니다! 🎉\n";
            break;
        }
    }

    char enter;
    cout << "\n이동 경로를 재생하겠습니까? (엔터): ";
    cin.ignore();
    cin.get(enter);
    replay();
    return 0;
}
