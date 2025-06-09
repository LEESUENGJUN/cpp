#pragma once
#include "Monster.h"
#include <iostream>

class Human : public Monster {
public:
    Human(const std::string& n = "Player", char i = '@', int px = 0, int py = 0)
        : Monster(n, i, px, py) {}

    // 방향키 입력 (Enter로 방향을 입력받음)
    int getDirKey() {
        std::cout << "이동 방향(w/a/s/d): ";
        char ch;
        std::cin >> ch;
        if (ch == 'a') return 75; // Left
        if (ch == 'd') return 77; // Right
        if (ch == 'w') return 72; // Up
        if (ch == 's') return 80; // Down
        return 0;
    }

    void move(int** map, int maxx, int maxy) override {
        int ch = getDirKey();
        if (ch == 75) x--;
        else if (ch == 77) x++;
        else if (ch == 72) y--;
        else if (ch == 80) y++;
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
        eat(map, maxx, maxy);
    }
};
