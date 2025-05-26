#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Matrix {
    int rows, cols;
    int** mat;
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(nullptr) {
        if (rows > 0 && cols > 0) {
            mat = new int*[rows];
            for (int i = 0; i < rows; i++)
                mat[i] = new int[cols];
        }
    }
    ~Matrix() {
        if (mat) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }
    int& elem(int x, int y) { return mat[y][x]; }
    int** Data() { return mat; }
    int Rows() const { return rows; }
    int Cols() const { return cols; }
};
