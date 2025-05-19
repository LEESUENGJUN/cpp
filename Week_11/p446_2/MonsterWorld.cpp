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
    if (countItems() == 0) return true;
    bool anyAlive = false;
    for (int i = 0; i < nMon; ++i) {
        if (pMon[i]->isAlive()) { anyAlive = true; break; }
    }
    return !anyAlive;
}

int MonsterWorld::countItems() {
    int sum = 0;
    for(int y = 0; y < yMax; y++)
        for(int x = 0; x < xMax; x++)
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
        for (int i = 0; i < nMon; i++) {
            if (pMon[i]->isAlive())
                pMon[i]->move(world.Data(), xMax, yMax);
        }
        print();
        usleep(wait *4000);
        int idx = 0;
        for (int i = 0; i < nMon; i++) {
            if (pMon[i]->isAlive()) {
                pMon[idx++] = pMon[i];
            } else {
                cout << pMon[i]->getName() << "이(가) 굶어 죽었습니다." << endl;
                delete pMon[i];
            }
        }
        nMon = idx;
        if (nMon == 0) {
            cout << "모든 몬스터가 죽었습니다. 게임 종료!" << endl;
            break;
        }
    }
}
