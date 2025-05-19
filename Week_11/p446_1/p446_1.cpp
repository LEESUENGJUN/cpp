// p446_1.cpp
#include "p446_1.h"

// Point 클래스 정의
Point::Point(int xx, int yy) : x(xx), y(yy) {}

void Point::draw() {
    cout << x << " , " << y << " 에 점을 그려라.\n";
}

// Rectangle 클래스 정의
Rectangle::Rectangle(int xx, int yy, int w, int h)
    : Point(xx, yy), width(w), height(h) {}

void Rectangle::draw() {
    cout << x << "," << y << "에 가로 " << width
         << " 세로 " << height << "인 사각형을 그려라\n";
}

// main 함수
int main() {
    Rectangle r(2, 3, 100, 200);
    r.draw();  // 예시 출력: 2,3에 가로 100 세로 200인 사각형을 그려라
    return 0;
}
