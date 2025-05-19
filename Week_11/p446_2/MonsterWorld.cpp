#include "MonsterWorld.h"
#include <iostream>
#include <unistd.h>
using namespace std;

MonsterWorld::MonsterWorld(int w, int h)
    : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
    world.setRand();
}

int& MonsterWorld::Map(int x, int y) {
    return world.elem(x, y);
}

bool MonsterWorld::isDone() {
    return countItems() == 0;
}

int MonsterWorld::countItems() {
    int sum = 0;
    for (int y = 0; y < yMax; y++)
        for (int x = 0; x < xMax; x++)
            sum += Map(x, y);
    return sum;
}

void MonsterWorld::add(Monster* pm) {
    if (nMon < MAXMONS)
        pMon[nMon++] = pm;
}

void MonsterWorld::print() {
    canvas.clear();
    for (int i = 0; i < nMon; i++)
        pMon[i]->draw(canvas);
    canvas.print("Monster World");
    world.print("Map Items");
    for (int i = 0; i < nMon; i++)
        pMon[i]->print();
}

void MonsterWorld::play(int maxwalk, int wait) {
    for (nMove = 0; nMove < maxwalk; nMove++) {
        if (isDone()) break;
        for (int i = 0; i < nMon; i++)
            pMon[i]->move(world.Data(), xMax, yMax);
        print();
        usleep(wait * 5000); // milliseconds
    }
}
