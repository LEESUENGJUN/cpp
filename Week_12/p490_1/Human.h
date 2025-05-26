#pragma once
#include "Monster.h"
#include "Canvas.h"

class Human : public Monster {
public:
    using Monster::Monster;
    void move(int** map, int maxx, int maxy) override {
        if (!kbhit()) return;
        unsigned char ch = getche();
        int nx = x, ny = y;
        if (ch == 'w' || ch == 'W') ny--;
        else if (ch == 's' || ch == 'S') ny++;
        else if (ch == 'a' || ch == 'A') nx--;
        else if (ch == 'd' || ch == 'D') nx++;
        else if (ch == 27 && kbhit()) {
            getch();
            unsigned char dir = getch();
            if (dir == 'A') ny--;
            else if (dir == 'B') ny++;
            else if (dir == 'D') nx--;
            else if (dir == 'C') nx++;
            else return;
        } else return;
        if (nx < 0 || nx >= maxx || ny < 0 || ny >= maxy) return;
        x = nx; y = ny;
        clip(maxx, maxy);
        eat(map);
    }
};
