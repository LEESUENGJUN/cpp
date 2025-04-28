#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// 클래스: Canvas
class Canvas {
    string line[100];
    int xMax, yMax;
public:
    // 생성자
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, ' ');
    }

    // 함수: draw
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            line[y].replace(x * 2, 2, val);
    }

    // 함수: clear
    void clear(string val = "■") { // 검은 네모 기본값 설정
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }

    // 함수: print
    void print(const char* title = "<My Canvas>") {
        system("clear");
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                cout << line[y].substr(x * 2, 2);
                if (x < xMax - 1) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

// 클래스: Monster
class Monster {
    string name;
    string icon;
    int x, y;
    int nEnergy; // (문제 1) 몬스터 에너지 속성 추가

public:
    // 생성자
    // (문제 2) 에너지를 100으로 초기화
    Monster(const string& n, const string& i, int x_, int y_)
        : name(n), icon(i), x(x_), y(y_), nEnergy(100) {}

    // 함수: 자동 이동
    void move(int xMax, int yMax) {
        int dx, dy;
        do {
            dx = rand() % 3 - 1;
            dy = rand() % 3 - 1;
        } while (dx == 0 && dy == 0);

        x = max(0, min(xMax - 1, x + dx));
        y = max(0, min(yMax - 1, y + dy));
    }

    // 함수: 사용자 이동
    void move(int dx, int dy, int xMax, int yMax) {
        x = max(0, min(xMax - 1, x + dx));
        y = max(0, min(yMax - 1, y + dy));
    }

    // 함수: 아이템 먹기
    // (문제 3) 아이템 먹으면 에너지 +8, 못 먹으면 -1
    bool eat(int xFood, int yFood) {
        if (x == xFood && y == yFood) {
            nEnergy += 8;
            return true;
        }
        nEnergy = max(0, nEnergy - 1);
        return false;
    }

    // 함수: 정보 출력
    // (문제 4) 이름, 위치, 에너지 출력
    void print() const {
        cout << name << ": (" << x << ", " << y << "), 에너지: " << nEnergy << endl;
    }

    // 함수: 캔버스에 그리기
    void draw(Canvas& canvas) const {
        canvas.draw(x, y, icon);
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getEnergy() const { return nEnergy; }
    string getName() const { return name; }
};

// 클래스: MonsterWorld
class MonsterWorld {
    Canvas canvas;
    Monster* monsters[100];
    int nMonsters;
    int xMax, yMax;
    int xFood, yFood;

public:
    // 생성자
    MonsterWorld(int w, int h) : canvas(w, h), nMonsters(0), xMax(w), yMax(h) {
        xFood = 3;
        yFood = 3;
    }

    // 소멸자
    ~MonsterWorld() {
        for (int i = 0; i < nMonsters; i++) {
            delete monsters[i];
        }
    }

    // 함수: 몬스터 추가
    void add(const Monster& m) {
        if (nMonsters < 100) {
            monsters[nMonsters++] = new Monster(m);
        }
    }

    // 함수: 게임 플레이
    void play(int maxSteps, int foodSteps) {
        int step = 0;
        int foodTimer = 0;
        char input;

        while (step++ < maxSteps) {
            canvas.clear();
            canvas.draw(xFood, yFood, "@@");

            cout << "WASD로 붕붕이를 이동, Q로 종료: ";
            cin >> input;
            if (input == 'q' || input == 'Q') break;

            int dx = 0, dy = 0;
            if (input == 'w' || input == 'W') dy = -1;
            else if (input == 's' || input == 'S') dy = 1;
            else if (input == 'a' || input == 'A') dx = -1;
            else if (input == 'd' || input == 'D') dx = 1;

            monsters[0]->move(dx, dy, xMax, yMax);

            for (int i = 1; i < nMonsters; i++) {
                monsters[i]->move(xMax, yMax);
            }

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

        cout << "\n게임 종료\n";
        for (int i = 0; i < nMonsters; i++) {
            cout << monsters[i]->getName() << " " << monsters[i]->getEnergy() << endl;
        }
    }
};

#endif
