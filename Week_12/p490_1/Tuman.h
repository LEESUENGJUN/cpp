#pragma once
#include "Human.h"

class Tuman : public Human {
public:
    // 역할 구분용 (좌=0, 우=1)
    int role; // 0=좌, 1=우

    // role 추가된 생성자
    Tuman(const std::string& n, const std::string& i, int x, int y, int r)
        : Human(n, i, x, y), role(r) {}

    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        int nx = x, ny = y;
        if (role == 0) {
            // 좌: WASD만 인식
            if (ch == 'w' || ch == 'W') ny--;
            else if (ch == 's' || ch == 'S') ny++;
            else if (ch == 'a' || ch == 'A') nx--;
            else if (ch == 'd' || ch == 'D') nx++;
            else return;
        } else {
            // 우: 키패드 8,4,5,6만 인식
            if (ch == '8') ny--;
            else if (ch == '5') ny++;
            else if (ch == '4') nx--;
            else if (ch == '6') nx++;
            else return;
        }
        if (nx < 0 || nx >= maxx || ny < 0 || ny >= maxy) return;
        x = nx; y = ny;
        clip(maxx, maxy);
        eat(map);
    }
};
