// Monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>
#include "Canvas.h"

class Monster {
    std::string name, icon;
    int x, y;
    int nItem;
    int nEnergy;        // 현재 에너지
public:
    static int count;  // 몬스터 수 집계

    // 초기 에너지를 100으로 고정
    Monster(const std::string& n, const std::string& i, int px, int py)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {
        ++count;
    }
    ~Monster();  // Monster.cpp에 정의

    void clip(int maxx, int maxy);
    void eat(int** map);
    void move(int** map, int maxx, int maxy);
    void draw(Canvas& canvas);
    void print() const;
    static void printCount();
    int getEnergy() const { return nEnergy; }
};

#endif // MONSTER_H
