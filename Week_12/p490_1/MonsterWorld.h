#pragma once
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Canvas.h"
#include "Matrix.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Tuman.h"

#define MAXMONS 8

class MonsterWorld {
    Matrix world;
    int xMax, yMax;
    int nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int cnt = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) cnt++;
        return cnt;
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, ". ");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World ]");
        std::cerr << "전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << "남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
    }
public:
    MonsterWorld(int w, int h) : world(h, w), xMax(w), yMax(h), nMon(0), nMove(0), canvas(w, h) {
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }
    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }
    void add(Monster* m) {
        if (nMon < MAXMONS) pMon[nMon++] = m;
    }
    void play(int maxwalk, int waitMs) {
        print();
        std::cerr << "엔터 키를 누르면 시작..." << std::endl;
        std::cin.get();
        for (int step = 0; step < maxwalk; step++) {
            for (int i = 0; i < nMon - 2; i++)
                pMon[i]->move(world.Data(), xMax, yMax);
            if (kbhit()) {
                unsigned char ch = getche();
                if (ch == 27 && kbhit()) {
                    getch();
                    unsigned char dir = getch();
                    ((Tuman*)pMon[nMon - 1])->moveHuman(world.Data(), xMax, yMax, dir);
                } else {
                    ((Tuman*)pMon[nMon - 2])->moveHuman(world.Data(), xMax, yMax, ch);
                }
            }
            nMove++;
            print();
            if (isDone()) break;
            usleep(waitMs * 1000);
        }
    }
};
