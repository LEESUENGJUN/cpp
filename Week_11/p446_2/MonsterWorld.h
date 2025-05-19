#pragma once
#include "Matrix.h"
#include "Canvas.h"
#include "Monster.h"
#define MAXMONS 100

class MonsterWorld {
    Matrix world;
    Canvas canvas;
    Monster* pMon[MAXMONS];
    int xMax, yMax, nMon, nMove;
    int& Map(int x, int y);
    bool isDone();
    int countItems();
    void print();
public:
    MonsterWorld(int w, int h);
    void add(Monster* pm);
    void play(int maxwalk, int wait);
};
