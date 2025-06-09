#pragma once
#include <vector>
#include <iostream>

class Matrix {
    int rows, cols;
    std::vector<std::vector<int>> mat;
public:
    Matrix(int r = 8, int c = 8) : rows(r), cols(c), mat(r, std::vector<int>(c, 0)) {}
    int& elem(int x, int y) { return mat[y][x]; }
    int Rows() const { return rows; }
    int Cols() const { return cols; }
    void print(const std::string& str = "Matrix") {
        std::cout << str << std::endl;
        for (const auto& row : mat) {
            for (int v : row) std::cout << v << " ";
            std::cout << std::endl;
        }
    }
};
