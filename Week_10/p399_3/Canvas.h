// Canvas.h
#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <iostream>
using namespace std;

const int MAXLINES = 100;

class Canvas {
    string line[MAXLINES];
    int xMax, yMax;
public:
    // 생성자: 기본적으로 '.'로 빈칸을 채움
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        clear('.');
    }

    // 특정 위치에 아이콘을 그림
    void draw(int x, int y, const string &val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            line[y].replace(x * 2, val.size(), val);
        }
    }

    // 모든 칸을 지정된 문자로 채움 (기본: '.')
    void clear(char fillChar = '.') {
        for (int y = 0; y < yMax; y++) {
            line[y] = string(xMax * 2, fillChar);
        }
    }

    // 화면에 출력
    void print(const char *title = "<My Canvas>") {
        cout << title << "\n";
        for (int y = 0; y < yMax; y++) {
            cout << line[y] << "\n";
        }
    }
};

#endif // CANVAS_H
