#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

Matrix::Matrix(int r, int c): rows(r), cols(c) {
    mat = new int*[rows];
    for(int i=0; i<rows; i++)
        mat[i] = new int[cols]{};
}

Matrix::~Matrix() {
    for(int i=0; i<rows; i++)
        delete[] mat[i];
    delete[] mat;
}

int& Matrix::elem(int x, int y) {
    return mat[y][x];
}

int Matrix::Rows() const { return rows; }
int Matrix::Cols() const { return cols; }
int** Matrix::Data() { return mat; }

void Matrix::setRand(int val) {
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            mat[i][j] = rand()%2;
}

void Matrix::print(const char* str) {
    cout << str << " [" << rows << "x" << cols << "]" << endl;
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++)
            cout << setw(2) << mat[i][j];
        cout << endl;
    }
}
