#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include "Monster.h"
using namespace std;

// Canvas 클래스: 게임 화면 관리
#define MAXLINES 100
class Canvas {
    string line[MAXLINES]; // 화면 라인
    int xMax, yMax;       // 화면 크기
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' '); // 각 칸은 2바이트 문자
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            line[y].replace(x * 2, 2, val);
    }
    void clear(string val = "□") {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char* title = "<My Canvas>") {
        system("clear"); // 리눅스용 화면 지우기
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                cout << line[y].substr(x * 2, 2);
                if (x < xMax - 1) cout << " "; // 칸 사이 공백 추가
            }
            cout << endl;
        }
        cout << endl;
    }
};

// MonsterWorld 클래스: 게임 관리
class MonsterWorld {
    Canvas canvas;
    Monster* monsters[100];
    int nMonsters;
    int xMax, yMax;
    int xFood, yFood;
public:
    MonsterWorld(int w, int h) : canvas(w, h), nMonsters(0), xMax(w), yMax(h) {
        xFood = 3; // 현재 출력: 아이템 at (3,3)
        yFood = 3;
    }
    void add(Monster m) {
        if (nMonsters < 100) {
            monsters[nMonsters++] = new Monster(m);
        }
    }
    void play(int maxSteps, int foodSteps) {
        int step = 0;
        int foodTimer = 0;
        char input;
        while (step++ < maxSteps) {
            canvas.clear();
            canvas.draw(xFood, yFood, "@@");
            // 사용자 입력 처리
            cout << "WASD로 붕붕이를 이동, Q로 종료: ";
            cin >> input;
            if (input == 'q' || input == 'Q') break;
            // 붕붕이 이동 (첫 번째 몬스터)
            int dx = 0, dy = 0;
            if (input == 'w' || input == 'W') dy = -1;
            else if (input == 's' || input == 'S') dy = 1;
            else if (input == 'a' || input == 'A') dx = -1;
            else if (input == 'd' || input == 'D') dx = 1;
            monsters[0]->move(dx, dy, xMax, yMax);
            // 나머지 몬스터는 자동 이동
            for (int i = 1; i < nMonsters; i++) {
                monsters[i]->move(xMax, yMax);
            }
            // 아이템 먹기 및 갱신
            for (int i = 0; i < nMonsters; i++) {
                if (monsters[i]->eat(xFood, yFood)) {
                    xFood = rand() % xMax;
                    yFood = rand() % yMax;
                    foodTimer = 0;
                }
                monsters[i]->draw(canvas);
            }
            canvas.print("Monster World");
            for (int i = 0; i < nMonsters; i++) {
                monsters[i]->print();
            }
            if (++foodTimer >= foodSteps) {
                xFood = rand() % xMax;
                yFood = rand() % yMax;
                foodTimer = 0;
            }
        }
        // 게임 종료 후 최종 상태 출력
        cout << "\n게임 종료\n";
        for (int i = 0; i < nMonsters; i++) {
            cout << monsters[i]->getName() << " " << monsters[i]->getEnergy() << endl;
        }
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMonsters; i++) {
            delete monsters[i];
        }
    }
};

// Monster::move (자동): 랜덤 이동
void Monster::move(int xMax, int yMax) {
    int dx = rand() % 3 - 1; // -1, 0, 1
    int dy = rand() % 3 - 1; // -1, 0, 1
    x = max(0, min(xMax - 1, x + dx));
    y = max(0, min(yMax - 1, y + dy));
}

// Monster::move (사용자 제어): 방향 입력으로 이동
void Monster::move(int dx, int dy, int xMax, int yMax) {
    x = max(0, min(xMax - 1, x + dx));
    y = max(0, min(yMax - 1, y + dy));
}

// (3) Monster::eat - 조건 (3): 아이템 먹으면 에너지 +8, 못 먹으면 -1, 최소 0
bool Monster::eat(int xFood, int yFood) {
    if (x == xFood && y == yFood) {
        nEnergy += 8; // 아이템 먹음
        return true;
    }
    nEnergy = max(0, nEnergy - 1); // 못 먹음, 최소 0
    return false;
}

// (4) Monster::print - 조건 (4): 이름, 위치, 에너지 출력
void Monster::print() const {
    cout << name << ": " << x << " " << y << " Energy: " << nEnergy << endl;
}

// Monster::draw: 캔버스에 그리기
void Monster::draw(Canvas& canvas) const {
    canvas.draw(x, y, icon);
}

// (3) main 함수 - 조건 (3): 몬스터 생성 및 게임 실행
int main() {
    srand((unsigned int)time(NULL));
    int w = 20, h = 10; // 캔버스 크기: 20x10

    MonsterWorld game(w, h);
    // (2) 몬스터 생성 - 조건 (2): 현재 출력 위치로 초기화
    game.add(Monster("붕붕이", "♠", 0, 1));   // 현재 출력: (0,1)
    game.add(Monster("사냥꾼", "★", 0, 9));   // 현재 출력: (0,9)
    game.add(Monster("도둑새", "♥", 19, 1));  // 현재 출력: (19,1)
    game.add(Monster("토끼", "♣", 19, 9));   // 현재 출력: (19,9)
    
    // (3) 게임 실행 - 조건 (3): 에너지 변화 및 출력 테스트
    game.play(100, 10);
    return 0;
}