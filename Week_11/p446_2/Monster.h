#pragma once
#include <iostream>
#include <string>
#include "Canvas.h"

class Monster {
protected:
    std::string name, icon;
    int x, y, nItem;
    void clip(int maxx, int maxy);
    void eat(int** map);
public:
    Monster(std::string n = "나괴물", std::string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}

    virtual ~Monster() {}
    virtual void move(int** map, int maxx, int maxy);
    void draw(Canvas& canvas);
    void print();
};

// 기본 강시 클래스
class Jiangshi : public Monster {
protected:
    bool bHori;
public:
    Jiangshi(std::string n = "강시", std::string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}

    virtual void move(int** map, int maxx, int maxy);
};

// 스몸비 - 대각선
class Smombi : public Monster {
public:
    Smombi(std::string n = "스몸비", std::string i = "▽", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}

    void move(int** map, int maxx, int maxy) override;
};

// 수퍼 강시
class Siangshi : public Jiangshi {
    int moveCount;
    int threshold;
public:
    Siangshi(std::string n = "상시", std::string i = "↕", int x = 0, int y = 0, bool bH = true, int th = 20)
        : Jiangshi(n, i, x, y, bH), moveCount(0), threshold(th) {}

    void move(int** map, int maxx, int maxy) override;
};

// 장산범 - 두 칸 점프
class Jangsanbeom : public Monster {
public:
    Jangsanbeom(std::string n = "장산범", std::string i = "※", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}

    void move(int** map, int maxx, int maxy) override;
};
