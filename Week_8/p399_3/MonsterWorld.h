// MonsterWorld.h
#ifndef MONSTERWORLD_H
#define MONSTERWORLD_H

#include <unistd.h>   // usleep
#include <iostream>
#include "Monster.h"
#include "Matrix.h"
#include "Canvas.h"

static const int MAXMONS = 10;  // 최대 몬스터 수

class MonsterWorld {
    Matrix world;
    Monster* pMon[MAXMONS];
    int xMax, yMax, nMon, nMove;
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }
    bool isDone();
    int countItems();
    void print();

public:
    MonsterWorld(int w, int h);
    ~MonsterWorld();
    void add(Monster* pm);
    void checkStarvation();
    void play(int maxwalk, int wait);
};

#endif // MONSTERWORLD_H
