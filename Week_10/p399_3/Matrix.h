#ifndef MATRIX_H
#define MATRIX_H

#define DIM 16

class Matrix {
    int rows, cols;
    int** mat;

public:
    Matrix(int r = DIM, int c = DIM);
    ~Matrix();
    int& elem(int x, int y);
    int** Data() { return mat; }
};

#endif