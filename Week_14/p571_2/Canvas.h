#pragma once
#include <vector>
#include <string>
#include <iostream>

class Canvas {
    int width, height;
    std::vector<std::string> buffer;
public:
    Canvas(int w = 16, int h = 8) : width(w), height(h), buffer(h, std::string(w, ' ')) {}
    void clear(char fill = ' ') {
        for (auto& row : buffer) row.assign(width, fill);
    }
    void draw(int x, int y, char ch) {
        if (x >= 0 && x < width && y >= 0 && y < height) buffer[y][x] = ch;
    }
    void print(const std::string& title = "<Canvas>") const {
        std::cout << title << std::endl;
        for (const auto& row : buffer) std::cout << row << std::endl;
    }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
