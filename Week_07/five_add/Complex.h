#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex {
    double real, imag;
//역할: Complex 클래스 객체를 초기화합니다.
//기본값: r, i 모두 기본값 0.0을 가집니다. (인자 없이 호출 가능)
//초기화 리스트(: real(r), imag(i)) 사용:
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    void show(const char* label) {
        cout << label << " = " << real << " + " << imag << "i" << endl;
    }

    // [1] 일반 함수 (void 참조 전달)
    friend void add1(Complex& a, Complex& b, Complex& c) {
        c.real = a.real + b.real;
        c.imag = a.imag + b.imag;
    }

    // [2] 일반 함수 (return 값 전달)
    friend Complex add2(Complex a, Complex b) {
        return Complex(a.real + b.real, a.imag + b.imag);
    }

    // [3] 멤버 함수 (void 참조 전달)
    void add3(Complex& a, Complex& b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
    }

    // [4] 멤버 함수 (return 참조 전달)
    Complex add4(Complex& b) {
        return Complex(real + b.real, imag + b.imag);
    }

    // [5] 연산자 오버로딩
    Complex operator+(Complex& b) {
        return Complex(real + b.real, imag + b.imag);
    }
};

#endif
