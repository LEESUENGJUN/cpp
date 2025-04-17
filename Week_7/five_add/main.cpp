#include "Complex.h"

int main() {
    Complex a(1, 2), b(3, 4), c;

    // [1] 일반 함수 (void 참조 전달)
    add1(a, b, c);
    c.show("1. 일반 함수 (void 참조 전달)");

    // [2] 일반 함수 (return 값 전달)
    c = add2(a, b);
    c.show("2. 일반 함수 (return 값 전달)");

    // [3] 멤버 함수 (void 참조 전달)
    c.add3(a, b);
    c.show("3. 멤버 함수 (void 참조 전달)");

    // [4] 멤버 함수 (return 참조 전달)
    c = a.add4(b);
    c.show("4. 멤버 함수 (return 참조 전달)");

    // [5] 연산자 오버로딩
    c = a + b;
    c.show("5. 연산자 오버로딩");

    return 0;
}
