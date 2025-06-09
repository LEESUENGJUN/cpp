#pragma once
#include "Monster.h"
#include <cstdlib>

// 다양한 몬스터 예시
class Zombie : public Monster {
public:
    Zombie(const std::string& n = "Zombie", char i = 'Z', int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int** map, int maxx, int maxy) override {
        x = rand() % maxx;
        y = rand() % maxy;
        eat(map, maxx, maxy);
    }
};

class Vampire : public Monster {
public:
    Vampire(const std::string& n = "Vampire", char i = 'V', int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        if (dir == 0) x = (x + 1) % maxx;
        else if (dir == 1) x = (x - 1 + maxx) % maxx;
        else if (dir == 2) y = (y + 1) % maxy;
        else y = (y - 1 + maxy) % maxy;
        eat(map, maxx, maxy);
    }
};
