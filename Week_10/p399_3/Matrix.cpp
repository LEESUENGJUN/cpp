#include "Matrix.h"
#include <cstdlib>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    mat = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        mat[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
            mat[i][j] = rand() % 2; // 0 또는 1로 초기화
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i)
        delete[] mat[i];
    delete[] mat;
}

int& Matrix::elem(int x, int y) {
    return mat[y][x]; // row-major 방식
}