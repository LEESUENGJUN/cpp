#pragma once
#include <string>
#include <iostream>

class Monster {
protected:
    std::string name;
    char icon;
    int x, y;
    int nItem;

public:
    Monster(const std::string& n = "Monster", char i = 'M', int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}
    virtual ~Monster() {}

    virtual void move(int** map, int maxx, int maxy) {
        // 기본 몬스터 랜덤 이동 (샘플)
        x = (x + 1) % maxx;
        y = (y + 1) % maxy;
        eat(map, maxx, maxy);
    }

    void eat(int** map, int maxx, int maxy) {
        if (x >= 0 && x < maxx && y >= 0 && y < maxy && map[y][x] > 0) {
            map[y][x] = 0;
            nItem++;
        }
    }

    void draw(class Canvas& canvas) {
        canvas.draw(x, y, icon);
    }

    void print() {
        std::cout << name << "(" << icon << "): " << nItem << std::endl;
    }

    int getItem() const { return nItem; }
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const { return name; }
};
