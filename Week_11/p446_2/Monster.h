#pragma once
#include <iostream>
#include <string>
#include "Canvas.h"

class Monster {
protected:
    std::string name, icon;
    int x, y, nEnergy;
    void clip(int maxx, int maxy);
public:
    Monster(std::string n = "나괴물", std::string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nEnergy(16) {}
    virtual ~Monster() {}
    virtual void move(int** map, int maxx, int maxy);
    virtual void eat(int** map);
    void draw(Canvas& canvas);
    void print();
    bool isAlive() const { return nEnergy > 0; }
    const std::string& getName() const { return name; }
};

class Zombie : public Monster {
public:
    Zombie(std::string n = "좀비", std::string i = "§", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    void move(int** map, int maxx, int maxy) override;
};

class Vampire : public Monster {
public:
    Vampire(std::string n = "뱀파이어", std::string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    void move(int** map, int maxx, int maxy) override;
};

class KGhost : public Monster {
public:
    KGhost(std::string n = "도깨비", std::string i = "♥", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    void move(int** map, int maxx, int maxy) override;
    void eat(int** map) override;
};

class Jiangshi : public Monster {
protected:
    bool bHori;
public:
    Jiangshi(std::string n = "강시", std::string i = "↔", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    void move(int** map, int maxx, int maxy) override;
};

class Smombi : public Zombie {
public:
    Smombi(std::string n = "스몸비", std::string i = "▽", int x = 0, int y = 0)
        : Zombie(n, i, x, y) {}
    void move(int** map, int maxx, int maxy) override;
};

class Siangshi : public Jiangshi {
    int moveCount, threshold;
public:
    Siangshi(std::string n = "상시", std::string i = "↕", int x = 0, int y = 0, bool bH = true, int th = 20)
        : Jiangshi(n, i, x, y, bH), moveCount(0), threshold(th) {}
    void move(int** map, int maxx, int maxy) override;
};

class Kumiho : public KGhost {
public:
    Kumiho(std::string n = "구미호", std::string i = "🦊", int x = 0, int y = 0)
        : KGhost(n, i, x, y) {}
    void eat(int** map) override;
};
