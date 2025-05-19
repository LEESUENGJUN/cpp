#pragma once
#include <string>
#include <iostream>
using namespace std;
#define MAXLINES 100

class Canvas {
    string line[MAXLINES];
    int xMax, yMax;
public:
    Canvas(int nx=10, int ny=10): xMax(nx), yMax(ny) {
        for(int y=0; y<yMax; y++)
            line[y] = string(xMax*2, ' ');
    }
    void draw(int x, int y, string val) {
        if(x>=0 && y>=0 && x<xMax && y<yMax)
            line[y].replace(x*2, 2, val);
    }
    void clear(string val=" ") {
        for(int y=0; y<yMax; y++)
            line[y] = string(xMax*2, val[0]);
    }
    void print(const char* title="<My Canvas>") {
        cout << "\n=== " << title << " ===" << endl;
        for(int y=0; y<yMax; y++)
            cout << line[y] << endl;
    }
};
