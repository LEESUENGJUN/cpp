#pragma once
#include <iostream>
#include <string>
#include "Canvas.h"

class Monster {
protected:
    std::string name;
    std::string icon;
    int x, y;
    int nItem;
    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
        }
    }
public:
    Monster(const std::string& n="Monster", const std::string& i="* ", int px=0, int py=0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}
    virtual ~Monster() { std::cout << name << icon << " destroyed\n"; }
    void draw(Canvas& canvas) { canvas.draw(x, y, icon); }
    virtual void move(int** map, int maxx, int maxy) {
        int dir = std::rand() % 8;
        switch (dir) {
            case 0: y--; break;
            case 1: x++; y--; break;
            case 2: x++; break;
            case 3: x++; y++; break;
            case 4: y++; break;
            case 5: x--; y++; break;
            case 6: x--; break;
            case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }
    void print() const { std::cout << name << icon << ":" << nItem << std::endl; }
};
