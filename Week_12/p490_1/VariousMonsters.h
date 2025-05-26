#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie(const std::string& n = "Zombie", const std::string& i = "Z ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() override { std::cout << " Zombie\n"; }
};

class Vampire : public Monster {
public:
    Vampire(const std::string& n = "Vampire", const std::string& i = "V ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() override { std::cout << " Vampire\n"; }
    void move(int** map, int maxx, int maxy) override {
        int dir = std::rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;
        clip(maxx, maxy);
        eat(map);
    }
};

class KGhost : public Monster {
public:
    KGhost(const std::string& n = "KGhost", const std::string& i = "K ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() override { std::cout << " KGhost\n"; }
    void move(int** map, int maxx, int maxy) override {
        x = std::rand() % maxx;
        y = std::rand() % maxy;
        clip(maxx, maxy);
        eat(map);
    }
};

class Jiangshi : public Monster {
    bool bHori;
public:
    Jiangshi(const std::string& n = "Jiangshi", const std::string& i = "J ", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() override { std::cout << " Jiangshi\n"; }
    void move(int** map, int maxx, int maxy) override {
        int dir = std::rand() % 2;
        int jump = std::rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};
