#pragma once
#include "Human.h"

class Tuman : public Human {
public:
    Tuman(const std::string& n, const std::string& i, int x, int y)
        : Human(n, i, x, y) {}
    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        int nx = x, ny = y;
        if (ch == 'w' || ch == 'W') ny--;
        else if (ch == 's' || ch == 'S') ny++;
        else if (ch == 'a' || ch == 'A') nx--;
        else if (ch == 'd' || ch == 'D') nx++;
        else if (ch == 27 && kbhit()) {
            unsigned char bracket = getch(); // '[' (91)
            if (bracket != '[') return;
            unsigned char dir = getch();
            if (dir == 'A') ny--;      // ↑
            else if (dir == 'B') ny++; // ↓
            else if (dir == 'C') nx++; // →
            else if (dir == 'D') nx--; // ←
            else return;
        } else return;
        if (nx < 0 || nx >= maxx || ny < 0 || ny >= maxy) return;
        x = nx; y = ny;
        clip(maxx, maxy);
        eat(map);
    }
};
