#pragma once
class Matrix {
    int rows, cols;
    int** mat;
public:
    Matrix(int r=0, int c=0);
    ~Matrix();
    int& elem(int x, int y);
    int Rows() const;
    int Cols() const;
    int** Data();
    void print(const char* str="Mat");
    void setRand(int val=100);
};
