// p446_1.h
#ifndef P446_1_H
#define P446_1_H

#include <iostream>
using namespace std;

class Point {
protected:
    int x, y;

public:
    Point(int xx, int yy);
    virtual void draw();
};

class Rectangle : public Point {
    int width, height;

public:
    Rectangle(int xx, int yy, int w, int h);
    void draw() override;
};

#endif
