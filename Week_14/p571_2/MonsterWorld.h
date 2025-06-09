#pragma once
#include "Monster.h"
#include "Canvas.h"
#include <vector>
#include <memory>

class MonsterWorld {
    int width, height;
    std::vector<std::vector<int>> map;
    std::vector<std::shared_ptr<Monster>> monsters;
    Canvas canvas;

public:
    MonsterWorld(int w = 8, int h = 8)
        : width(w), height(h), map(h, std::vector<int>(w, 1)), canvas(w, h) {}

    void add(std::shared_ptr<Monster> m) {
        monsters.push_back(m);
    }

    void play(int steps = 20) {
        for (int t = 0; t < steps; ++t) {
            canvas.clear();
            for (auto& m : monsters) {
                m->move(toPtrMap(), width, height);
                m->draw(canvas);
            }
            canvas.print("Monster World");
        }
    }

    int** toPtrMap() {
        int** arr = new int*[height];
        for (int i = 0; i < height; ++i)
            arr[i] = map[i].data();
        return arr;
    }

    void print() {
        for (auto& m : monsters) m->print();
    }
};
